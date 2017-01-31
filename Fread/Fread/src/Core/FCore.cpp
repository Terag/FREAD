/*
Boost Software License - Version 1.0 - August 17th, 2003
 * Modified by Victor Rouquette - January 2017

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
 */

/* 
 * File:   FCore.cpp
 * Author: guillem
 *
 * Created on 27 janvier 2017, 11:47
 */

#include "Core/FCore.hpp"

FCore::FCore( std::shared_ptr< FQueue< FMessages< FObjet > > > _pop_queue_parser, 
              std::shared_ptr< FQueue< FMessages< FObjet > > > _push_queue_parser,
              std::shared_ptr< FQueue< FMessages< std::pair<int,int> > > > _pop_queue_renderer,
              std::shared_ptr< FQueue< FMessages< FObjet > > > _push_queue_renderer):
              _m_pop_queue_parser(_pop_queue_parser),
              _m_push_queue_parser(_push_queue_parser),
              _m_pop_queue_renderer(_pop_queue_renderer),
              _m_push_queue_renderer(_push_queue_renderer)
                  
{ 
    _m_pop_queue_parser->setOtherCondition( std::make_shared<std::mutex>(m_message_parser_mutex),
                                            std::make_shared<std::condition_variable>(m_message_parser_cond) );
    m_containers_parser.setOtherCondition( std::make_shared<std::mutex>(m_message_parser_mutex),
                                           std::make_shared<std::condition_variable>(m_message_parser_cond) );
    m_occurrences_parser.setOtherCondition( std::make_shared<std::mutex>(m_message_parser_mutex),
                                            std::make_shared<std::condition_variable>(m_message_parser_cond) );
    
    _m_pop_queue_renderer->setOtherCondition( std::make_shared<std::mutex>(m_message_renderer_mutex),
                                              std::make_shared<std::condition_variable>(m_message_renderer_cond) );
    m_containers_renderer.setOtherCondition( std::make_shared<std::mutex>(m_message_renderer_mutex),
                                             std::make_shared<std::condition_variable>(m_message_renderer_cond) );
    m_occurrences_renderer.setOtherCondition( std::make_shared<std::mutex>(m_message_renderer_mutex),
                                              std::make_shared<std::condition_variable>(m_message_renderer_cond) );
   
    m_renderer_containers.setOtherCondition( std::make_shared<std::mutex>(m_containers_manager_mutex), 
                                             std::make_shared<std::condition_variable>(m_containers_manager_cond) );
    m_parser_containers.setOtherCondition( std::make_shared<std::mutex>(m_containers_manager_mutex), 
                                           std::make_shared<std::condition_variable>(m_containers_manager_cond) );
   
    m_renderer_occurrences.setOtherCondition( std::make_shared<std::mutex>(m_occurrences_manager_mutex), 
                                              std::make_shared<std::condition_variable>(m_occurrences_manager_cond) );
    m_parser_containers.setOtherCondition( std::make_shared<std::mutex>(m_occurrences_manager_mutex), 
                                           std::make_shared<std::condition_variable>(m_occurrences_manager_cond) );
    
}


/*
 * Thread that will manage  
 * the part of the memory 
 * containing the containers
 */
void FCore::thr_containers_manager(){
    //The container manager waits for messages from the parser or the renderer
    std::unique_lock<std::mutex> lock(m_containers_manager_mutex);
    m_containers_manager_cond.wait(lock, [this](){ 
                                                return !( m_parser_containers.empty() 
                                                          || m_renderer_containers.empty() );
                                           }
                                );
    lock.unlock();
    
    //any message received from the parser is added to the memory then sent to the parser
    if( !m_parser_containers.empty() ){
        FMessages<FObjet> msg( CONTAINER, m_parser_containers.try_pop()->getContent()  );
        
        /*
          The content is a shared_ptr<FContainer>
        */
        std::shared_ptr<FContainer> container_to_insert = std::static_pointer_cast< FContainer >( msg.getContent() );
        m_containers.insert( msg.getContent()->getId() , container_to_insert ) ;

        FMessages<FObjet> msg_send( CONTAINER, *(msg.getContent()) );
        m_containers_renderer.push( msg_send );
        
    }else if( !m_renderer_containers.empty() ){
        FMessages<std::pair<int,int>> msg = *( m_renderer_containers.try_pop() );
        //get the message
        
        // check if is in memory
        if( m_containers.contains(msg.getContent()->first)){ 
            //if is in memory
            std::shared_ptr<FContainer> to_send = m_containers[msg.getContent()->first];
            FMessages<FObjet> msg_send( CONTAINER, to_send );
            m_containers_renderer.push( msg_send );
        }else{ // not in memory
            //demands it to parser
            FMessages<FObjet> msg_send( CONTAINER, msg.getContent() );
            m_containers_parser.push( msg_send );
        }
    }
}

/*
 * Thread that will manage  
 * the part of the memory 
 * containing the occurrences
 */
void FCore::thr_occurrences_manager(){
    //The occurrences manager waits for messages from the parser or the renderer
    std::unique_lock<std::mutex> lock(m_occurrences_manager_mutex);
    m_occurrences_manager_cond.wait(lock, [this](){ 
                                                 return !( m_parser_occurrences.empty() 
                                                           || m_renderer_occurrences.empty() );
                                           }
                                );
    lock.unlock();
    
    //any message received from the parser is added to the memory then sent to the parser
    if( !m_parser_occurrences.empty() ){
        FMessages<FObjet> msg = *(m_parser_occurrences.try_pop());
        /*
          The content is a shared_ptr<FOccurrence>
        */
        std::pair<int, int> key = std::make_pair( std::static_pointer_cast< FOccurrence >(msg.getContent())->getPatternId(), 
                                                  std::static_pointer_cast< FOccurrence >msg.getContent()->getId() 
                                                );
        m_occurrences.insert( key, std::static_pointer_cast<FOccurrence>(msg.getContent()) );

        FMessages<FObjet> msg_send( OCCURRENCE, msg.getContent() );
        m_occurrences_renderer.push( msg_send );
        
    }else if( !m_renderer_occurrences.empty() ){
        FMessages<FObjet> msg = *(m_renderer_occurrences.try_pop());
        //get the messages
        
        // check if is in memory
        if( m_occurrences.contains( 
                                    *( std::static_pointer_cast< FOccurrence >
                                        (msg.getContent())
                                     )/*dereference*/ 
                                ) /*contain*/
          ){
            //if is in memory
            FMessages<FObjet> msg_send( OCCURRENCE, msg.getContent() );
            m_occurrences_renderer.push( msg_send );
        }else{ // not in memory
            //demands it to parser
            FMessages<FObjet> msg_send( OCCURRENCE, msg.getContent() );
            m_occurrences_parser.push( msg_send );
        }
    }
}

/*
 * Thread that will get messages from parser,
 * occurrences_manager and containers_manager
 * and redirect them depending on their header
 */ 
void FCore::thr_messages_handler_parser(){
        
    //The message handler waits for messages from the parser, the occurrences thread or the containers thread
    std::unique_lock<std::mutex> lock(m_message_parser_mutex);
    m_message_parser_cond.wait(lock, [this](){ 
                                            return !(_m_pop_queue_parser->empty() 
                                                     || m_occurrences_parser.empty() 
                                                     || m_containers_parser.empty());
                                           } 
                            );
    lock.unlock();

    if( !_m_pop_queue_parser->empty() ){ //Messages received from parser
        FMessages<FObjet> msg = *(_m_pop_queue_parser->try_pop());
        if(msg != NULL){
            switch(msg.getHeader() ){
                case(INITDONE):
                    awake = false;
                break;
                case(CONTAINER):
                    {
                    //send the container to the containers manager
                    FMessages<FObjet> msg_send(CONTAINER, msg.getContent() );
                    m_parser_containers.push(msg_send);
                    break;
                    }
                case(PATTERN):
                    {
                    //insert the pattern in m_patterns
                    m_patterns.insert( msg.getContent()->getId(), std::static_pointer_cast<FPattern>( msg.getContent() ) );
                    break;
                    }
                case(OCCURRENCE):
                    {
                    //send the occurrence to the occurrences manager
                    FMessages<FObjet> msg_send(OCCURRENCE, msg.getContent() );
                    m_parser_containers.push(msg_send);
                    break;
                    }
                default:
                    std::cout << "error : bad header" << std::endl;
                break;
            } 
        }
        
    }else if( !m_containers_parser.empty() ){ //Messages received from Containers thread
        FMessages<FObjet> msg = *(m_containers_parser.try_pop());
        if(msg != NULL){
            if(msg.getHeader() == CONTAINER){
                /*
                 TODO
                 */
                //it might need a conversion
                FMessages<FObjet> msg_send( CONTAINER, msg.getContent() );
                _m_push_queue_parser->push( msg_send );
            }else{
                std::cout << "error : bad header" << std::endl;
            }
        }
        
    }else if ( !m_occurrences_parser.empty() ){ // Messages received from Occurrences thread
        FMessages<FObjet> msg = *( m_containers_parser.try_pop() );
        if(msg != NULL){
            if(msg.getHeader() == OCCURRENCE){
                /*
                 TODO
                 */
                //it might need a conversion
                FMessages<FObjet> msg_send( OCCURRENCE, msg.getContent() );
                _m_push_queue_parser->push( msg_send );
            }else{
                std::cout << "error : bad header" << std::endl;
            }
        } 
    }
}

/*
 * Thread which will get messages from renderer,
 * occurrences_manager and containers_manager
 * and redirect them depending on their header
 */
void FCore::thr_messages_handler_renderer(){
    //The message handler waits for messages from the renderer, the occurrences thread or the containers thread
    std::unique_lock<std::mutex> lock(m_message_renderer_mutex);
    m_message_renderer_cond.wait(lock, [this](){ 
                                            return !(_m_pop_queue_renderer->empty() 
                                                     || m_occurrences_renderer.empty() 
                                                     || m_containers_renderer.empty());
                                           } 
                            );
    lock.unlock();

    if( !_m_pop_queue_renderer->empty() ){ //Messages received from renderer
        std::shared_ptr< FMessages< std::pair<int,int> > > msg = _m_pop_queue_renderer->try_pop();
        if(msg != NULL){
            switch(msg->getHeader()){
                case(CONTAINER):
                    {
                    //send the container to the containers manager
                    FMessages< std::pair<int, int> > msg_send(CONTAINER, msg->getContent() );
                    m_renderer_containers.push(msg_send);
                    break;
                    }
                case(OCCURRENCE):
                    {
                    //send the occurrence to the occurrences manager
                    FMessages< std::pair<int,int> > msg_send(OCCURRENCE, msg->getContent() );
                    m_renderer_containers.push(msg_send);
                    break;
                    }
                default:
                    {
                    std::cout << "error : bad header" << std::endl;
                    break;
                    }
            } 
        }
        
    }else if( !m_containers_renderer.empty() ){ //Messages received from Containers thread
        std::shared_ptr< FMessages<FObjet> > msg = m_containers_renderer.try_pop();
        if(msg != NULL){
            if(msg->getHeader() == CONTAINER){
                //it might need a conversion
                FMessages<FObjet> msg_send( CONTAINER, msg->getContent() );
                _m_push_queue_renderer->push( msg_send );
            }else{
                std::cout << "error : bad header" << std::endl;
            }
        }
        
    }else if ( !m_occurrences_renderer.empty() ){ // Messages received from Occurrences thread
        std::shared_ptr< FMessages<FObjet> > msg = m_containers_renderer.try_pop();
        if(msg != NULL){
            if(msg->getHeader() == OCCURRENCE){
                /*
                 TODO
                 */
                //it might need a conversion
                FMessages<FObjet> msg_send( OCCURRENCE, msg->getContent() );
                _m_push_queue_renderer->push( msg_send );
            }else{
                std::cout << "error : bad header" << std::endl;
            }
        } 
    }
}


void  FCore::check_memory(){
    if(m_occurrences.size() > MAX_SIZE){
        auto it = m_occurrences.begin();
        while( !m_occurrences.erase( it ) ){
            ++it;
        }
    }
   
    if(m_containers.size() > MAX_SIZE){
        auto it = m_occurrences.begin();
        while( !m_occurrences.erase( it ) ){
            ++it;
        }   
    }
}

    
void FCore::thr_FCore(){
        
    std::thread message_handler_parser_( [this]{thr_messages_handler_parser();} );
    FThread_guard mhpp_g( message_handler_parser_ );
        
    std::thread container_manager_( [this]{thr_containers_manager();} );
    FThread_guard cm_g(container_manager_);
        
    std::thread occurrences_manager_( [this]{thr_occurrences_manager();} );
    FThread_guard om_g(occurrences_manager_);
        
    while(awake){
            
    } 
        
    std::thread message_handler_renderer_( [this]{thr_messages_handler_renderer();} );
    FThread_guard mhpr_g( message_handler_renderer_ );
    
    while(1){
        check_memory();
    } 
}
