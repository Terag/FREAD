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

FCore::FCore(){

}

FCore::FCore(   std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _pop_queue_parser, 
                std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _push_queue_parser,
                std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _pop_queue_render,
                std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _push_queue_render
             ):
              _m_pop_queue_parser(_pop_queue_parser),
              _m_push_queue_parser(_push_queue_parser),
              _m_pop_queue_render(_pop_queue_render),
              _m_push_queue_render(_push_queue_render),
              initdone(false)
              {

              }

FCore::~FCore(){

}






/*
 * TIMESTAMPS MANAGER
 * THIS THREAD WILL MANAGE THE TIMESTAMPS KEPT IN MEMORY
 */
void FCore::thr_timestamps_manager(){
    std::cout << "in thr_timestamps_manager" << std::endl;
    float beginTime;
    float endTime; 
    int containerId;
    std::std::vector<patternStruct> vector_to_send;
    bool hasSend = false;
    while(1){
    	/*
  		 * COMPUTING LOOP
  		 */

        if(!m_render_timestamps.empty()){
   	   	   /* 
         	* MESSAGE FROM RENDER
		 	*/
            std::shared_ptr<FMessages> msg_render =  *(m_render_timestamps.try_pop()) ;
            
            auto received = std::static_pointer_cast<patternStruct>(msg_render->getContent() ) ;
            if(hasSend){
                beginTime = received->tBegin;
            	endTime = received->tEnd;
            	containerId = received->contId;

				std::cout << "CORE >>> TIMESTAMPS RECEIVED FROM RENDER in container : " << containerId << ", beginning at : " << beginTime << " and ending at : " << endTime << std::endl;
	
				/* 
            	 * NONE OF THE TIMESTAMPS DEMANDED ARE IN MEMORY 
            	 */
				std::cout << "CORE >>> NONE OF THE DEMANDED TIMESTAMPS ARE IN MEMORY" << std::endl;
	        	_m_push_queue_parser->push( msg_render );
	        	std::cout << "CORE >>> send timestamps demand to parser" << std::endl;

	        	hasSend = false;

            }



        	/*
 			 * BEGIN
 			 * DEBUGGING MESSAGE
 			 * BEGIN
        	 *
	        std::cout << "CORE >>> CONTAINERS Size : " << m_containers.size() << std::endl;
	        if(m_containers.size() > 0){
	         	for(auto it = m_containers.getMap().begin(); it != m_containers.getMap().end(); ++it){
	          		std::cout << "CORE >>> M_CONTAINERS ID : " << it->second->getId() << std::endl;
	          		std::cout << "                    Size : " << it->second->getPatternList().size() << std::endl;
	          		std::cout << "                  Values : ";
	          		for(auto it2 = ( it->second->getPatternList() ).begin(); it2 != ( it->second->getPatternList() ).end(); ++it2 ){
	          	 		std::cout << "id : " << it2->id << " begin : " << it2->tBegin << "end : " << it2->tEnd; 
	          		}
	          			std::cout << std::endl;
	         	}
	        }
        	 *
 			 * END
 			 * DEBUGGING MESSAGE
 			 * END
        	 */

        } /* if(!m_render_timestamps.empty()) */


        if(!m_parser_timestamps.empty()){
   	       /*
         	* MESSAGE FROM PARSER
		 	*/
            std::shared_ptr<FMessages> msg_parser = *(m_parser_timestamps.try_pop() );

            auto received = std::static_pointer_cast<patternStruct >(msg_parser->getContent() );
            //std::cout << "CORE >>> TIMESTAMPS RECEIVED FROM PARSER in container : " << received->begin()->contId << ", beginning at : " << received->begin()->tBegin << std::endl;
            /*
            for(auto it = received->begin(); it != received->end(); ++it ){
            	 *
            	 * ADDING ALL PATTERN RECEIVED FROM PARSER TO CORRESPONDING CONTAINER
            	 *
            	m_containers.at( received->begin()->contId )->add_pattern( *it );
            }
            */

            if(received->contId == containerId){
            	if(vector_to_send.empty()){
            		if(received->tEnd > beginTime && received->tBegin < beginTime){
            			vector_to_send.push_back(received.get());
            		}
            	}
            	if(received->tBegin < endTime && received->tEnd > beginTime ){
            		vector_to_send.push_back(received.get());
            	}
            	if(received->tBegin > endTime){
            		auto content_send = std::static_pointer_cast<void>( vector_to_send );
            		FMessages msg_send(TIMESTAMP, content_send);
            		_m_push_queue_render->push( std::make_shared< FMessages >(msg_send) );
            		hasSend = true;

            	}
        	}
            //std::cout << "CORE >>> send timestamps in container : " << received->contId << ", beginning at : " << received->begin()->tBegin << ", and ending at : " << (--received->end())->tEnd << std::endl;


        	/*
 			 * BEGIN
 			 * DEBUGGING MESSAGE
 			 * BEGIN
        	 *
	        std::cout << "CORE >>> CONTAINERS Size : " << m_containers.size() << std::endl;
	        if(m_containers.size() > 0){
	         	for(auto it = m_containers.getMap().begin(); it != m_containers.getMap().end(); ++it){
	          		std::cout << "CORE >>> M_CONTAINERS ID : " << it->second->getId() << std::endl;
	          		std::cout << "                    Size : " << it->second->getPatternList().size() << std::endl;
	          		std::cout << "                  Values : ";
	          		for(auto it2 = ( it->second->getPatternList() ).begin(); it2 != ( it->second->getPatternList() ).end(); ++it2 ){
	          	 		std::cout << " | id : " << it2->id << " begin : " << it2->tBegin << ", end : " << it2->tEnd; 
	          		}
	          			std::cout << std::endl;
	         	}
	        }
        	 *
 			 * END
 			 * DEBUGGING MESSAGE
 			 * END
        	 */

            for(auto it = m_containers.getMap().begin(); it != m_containers.getMap().end(); ++it ){
           	   /*
			 	* SORTING TIMESTAMPS FOR EACH CONTAINERS
	         	*/ 	
	         	std::cout << "CORE >>> M_CONTAINERS ID : " << it->second->getId() << std::endl;
            	if(!it->second->getPatternList().empty()){
            		std::cout << "CORE >>> BEFORE SORT" << std::endl;
 					std::sort(it->second->getPatternList().begin() + 1,  it->second->getPatternList().end() /*[](patternStruct a, patternStruct b){ return (a.tBegin < b.tBegin && a.tEnd < b.tEnd); }*/ );

        		} /* if(!it->second->getPatternList().empty()) */

            } /* for(auto it = m_containers.getMap().begin(); it != m_occurrences.getMap().end(); ++it ) */


        } /* if(!m_parser_timestamps.empty()) */

    } /* while(1) */

}/* void FCore::thr_timestamps_manager() */





/*
 * OCCURRENCES MANAGER
 * THIS THREAD WILL MANAGE THE OCCURRENCE KEPT IN MEMORY
 */
void FCore::thr_occurrences_manager(){
    std::cout << "in thr_occurrences_manager" << std::endl;
    while(1){
  		/*
  		 * COMPUTING LOOP
  		 */
    	//getting and processing messages from render
    	occurrences_from_render();
        
        //getting and processing messages from parser
        occurrences_from_parser();

    } /* while(1) */

} /* void FCore::thr_occurrences_manager() */





/*
 * OCCURRENCES MANAGER
 * THIS THREAD WILL COMPUTE THE MESSAGE FROM THE RENDER
 */
void FCore::occurrences_from_render(){

        if(!m_render_occurrences.empty()){
    	   /*
         	* MESSAGE FROM RENDER
		 	*/
            std::shared_ptr<FMessages> msg_render = *(m_render_occurrences.try_pop());

            auto received = *( std::static_pointer_cast< std::pair<int, int> >(msg_render->getContent() ) );
            std::cout << "CORE >>> OCCURRENCE RECEIVED FROM RENDER n° " << received.first << ":" << received.second << std::endl;

            if( m_occurrences.key_exists(received.first)){
   			   /* 
            	* THERE ARE OCCURRENCES FROM THE SAME PATTERN AS THE DEMANDED ONE IN MEMORY 
            	*/
            	if( contains_occurrence(received.first, received.second) ){
            	   /* 
            	 	* THE DEMANDED OCCURRENCE IS IN MEMORY 
            	    */
					std::cout << "CORE >>> IS IN MEMORY" << std::endl;
                	std::shared_ptr<FOccurrence> occurrence_send = find_occurrence(received.first, received.second );
                	auto content_send = std::static_pointer_cast<void>( occurrence_send );
                	FMessages msg_send(OCCURRENCE, content_send);
                	_m_push_queue_render->push( std::make_shared<FMessages>(msg_send) );
                	std::cout << "CORE >>> send occurrence " << occurrence_send->getPatternId() << ":" << occurrence_send->getId() << " to render from memory" << std::endl;
           
                }else{
                   /* 
            	 	* THE DEMANDED OCCURRENCE IS NOT IN MEMORY 
            	 	*/
					std::cout << "CORE >>> OCCURRENCE IS NOT IN MEMORY 1" << std::endl;            	
                	_m_push_queue_parser->push( msg_render );
                	std::cout << "CORE >>> send occurrence demand to parser" << std::endl;	
     
                } /* else if( contains_occurrence(received.first, received.second) ) */
      
            }else{ 
            	/* 
            	 * THE DEMANDED OCCURRENCE IS NOT IN MEMORY 
            	 */
				std::cout << "CORE >>> OCCURRENCE IS NOT IN MEMORY 2" << std::endl;            	
                _m_push_queue_parser->push( msg_render );
                std::cout << "CORE >>> send occurrence demand to parser" << std::endl;
     
            } /* else if( m_occurrences.key_exists(received.first)) */
    
        } /* if(!m_render_occurrences.empty()) */
}





/*
 * OCCURRENCES MANAGER
 * THIS THREAD WILL COMPUTE THE MESSAGE FROM THE PARSER
 */
void FCore::occurrences_from_parser(){

    if(!m_parser_occurrences.empty()){
		/*
		 *
	     * MESSAGE FROM PARSER
		 *
		 */
        std::shared_ptr<FMessages> msg_parser = *(m_parser_occurrences.try_pop() );

        auto received = std::static_pointer_cast< FOccurrence >(msg_parser->getContent() ) ;
        std::cout << "CORE >>> OCCURRENCE RECEIVED FROM PARSER n°" << received->getPatternId() << ":" << received->getId() << std::endl;

        std::pair<int, int> key = std::make_pair( received->getPatternId(), received->getId() );

        if( m_occurrences.key_exists(key.first)){
         	/* 
         	 * 
         	 * THERE ARE STILL OCCURRENCES IN MEMORY FROM THE SAME PATTERN AS THE RECEIVED'S ONE 
			 *
         	 */
         	m_occurrences.at(key.first)->push_back( received );
   
	    }else{
	        /* 
	         * 
	         * THERE IS NO OTHER OCCURRENCES IN MEMORY FROM THE SAME PATTERN AS THE RECEIVED'S ONE
			 *
	         */
	         auto pair_to_insert = std::make_pair(key.first, std::make_shared< std::vector< std::shared_ptr<FOccurrence> > >() );
	         m_occurrences.insert( pair_to_insert ); 
	         m_occurrences.at(key.first)->push_back( received );
	  
	    } /* if( m_occurrences.key_exists(key.first)) */

	    std::cout << "CORE >>> send occurrence " << received->getPatternId() << ":" << received->getId() << " to render" << std::endl;
	    _m_push_queue_render->push(msg_parser);
	     
	    if(!m_occurrences.empty()){
		    /*
			 *
			 * SORTING OCCURRENCES FOR EACH PATTERN
			 *
		     */
			for(auto it = m_occurrences.getMap().begin(); it != m_occurrences.getMap().end(); ++it){
				std::sort(it->second->begin(), it->second->end(), []( std::shared_ptr<FOccurrence> occ1 , std::shared_ptr<FOccurrence> occ2 ){ return (occ1->getId() < occ2->getId() ); });    		
	   		} /* for(auto it = m_occurrences.getMap().begin(); it != m_occurrences.getMap().end(); ++it) */ 	
  
    	} /* if(!m_occurrences.empty()) */

    } /* if(!m_parser_occurrences.empty()) */
}





/*
 * MESSAGE HANDLER PARSER
 * THIS THREAD TAKE MESSAGES FROM THE PARSER AND CHECK WHAT IT MUST WITH THEM
 */
void FCore::thr_messages_handler_parser(){
    std::cout << "in message_handler_parser" << std::endl;
    while(1){
        std::shared_ptr<FMessages> msg = *(_m_pop_queue_parser->wait_and_pop());
        if( msg.use_count() != 0 && msg != NULL){
            switch(msg->getHeader()){
                case(START):
                {
                    std::cout << "CORE >>> START MESSAGE RECEIVED FROM PARSER" << std::endl;
                    break;
                }
                case(INITDONE):
                {
                	std::cout << "CORE >>> INITDONE MESSAGE RECEIVED FROM PARSER" << std::endl;
                	initdone = true;
                	get_total_time();	
                    break;
                }
                case(CONTAINER):
                {
                    std::cout << "CORE >>> CONTAINER MESSAGE RECEIVED FROM PARSER" << std::endl;
                    std::shared_ptr<FContainer> received = std::static_pointer_cast<FContainer>(msg->getContent());
                    std::pair<int, std::shared_ptr<FContainer> > my_pair(received->getId() , received);
                    m_containers.insert( my_pair );
                    std::cout << "M_CONTAINERS SIZE IS NOW : " << m_containers.size() << std::endl;
                    break;
                }
                case(PATTERN):
                {
                    std::cout << "CORE >>> PATTERN MESSAGE RECEIVED FROM PARSER" << std::endl;
                    std::shared_ptr<FPattern> received = std::static_pointer_cast<FPattern>(msg->getContent());
                    std::pair<int, std::shared_ptr<FPattern> > my_pair(received->getId() , received);
                    m_patterns.insert( my_pair );
                    std::cout << "M_PATTERNS SIZE IS NOW : " << m_patterns.size() << std::endl;
                    break;
                }
                case(TIMESTAMP):
                {
                    std::cout << "CORE >>> TIMESTAMP MESSAGE RECEIVED FROM PARSER" << std::endl;
                    m_parser_timestamps.push( msg );
                    break;
                }
                case(OCCURRENCE):
                {
                    std::cout << "CORE >>> OCCURRENCE MESSAGE RECEIVED FROM PARSER" << std::endl;
                    m_parser_occurrences.push( msg );
                    break;
                }
                default:

                break;
            }
        }    
    }
}





/*
 * MESSAGE HANDLER RENDER
 * THIS THREAD TAKE MESSAGES FROM THE RENDER AND CHECK WHAT IT MUST WITH THEM
 */
void FCore::thr_messages_handler_render(){
    std::cout << "in thr_messages_handler_render" << std::endl;
    while(1){
        std::shared_ptr<FMessages> msg = *(_m_pop_queue_render->wait_and_pop());
        if( msg.use_count() != 0 && msg != NULL){
            switch(msg->getHeader()){
                case(START):
                {
                	std::cout << "CORE >>> START MESSAGE RECEIVED FROM RENDER" << std::endl;
                break;
                }
                case(INITDONE):
                {
                	std::cout << "CORE >>> INITDONE MESSAGE RECEIVED FROM RENDER" << std::endl;
                    break;
                }
                case(CONTAINER):
                {
                	std::cout << "CORE >>> CONTAINER MESSAGE RECEIVED FROM RENDER" << std::endl;

                    break;
                }
                case(PATTERN):
                {
                	std::cout << "CORE >>> PATTERN MESSAGE RECEIVED FROM RENDER" << std::endl;
                    
                    std::shared_ptr<int> pattern_received = std::static_pointer_cast<int>(msg->getContent());
                    std::shared_ptr<FPattern> pattern_to_send = m_patterns[ *(pattern_received) ];
                    auto content_send = std::static_pointer_cast<void>( pattern_to_send );
                	FMessages msg_send(PATTERN, content_send);
                	_m_push_queue_render->push( std::make_shared<FMessages>(msg_send) );
                	std::cout << "CORE >>> PATTERN MESSAGE RETURNED FROM RENDER" << std::endl;
                    
                    break;
                }
                case(TIMESTAMP):
                {
                	std::cout << "CORE >>> TIMESTAMP MESSAGE RECEIVED FROM RENDER" << std::endl;
                    m_render_timestamps.push( msg );
                    break;
                }
                case(OCCURRENCE):
                {
                	std::cout << "CORE >>> OCCURRENCE MESSAGE RECEIVED FROM RENDER" << std::endl;
                    m_render_occurrences.push( msg );
                    break;
                }
                case(LIST_ID):
                {
                	std::cout << "CORE >>> LIST_ID MESSAGE RECEIVED FROM RENDER" << std::endl;
                	if(initdone){
                	    std::vector<int> containers_id = get_containers_id();
                    	auto content_containers_send = std::static_pointer_cast<void>( std::make_shared<std::vector<int>>(containers_id) );
                    	FMessages msg_send_container( LIST_ID, content_containers_send );
                    	_m_push_queue_render->push( std::make_shared<FMessages>(msg_send_container) );	
                	}

                    break;
                }
                default:

                break;
            }
        }
    }   
}






void  FCore::thr_check_memory(){
    if(m_occurrences.size() > MAX_SIZE){
        !m_occurrences.erase();
    }
}




    
void FCore::thr_FCore(){
    
    std::cout << "start message_handler_parser_" << std::endl;
    std::thread message_handler_parser_( [this]{thr_messages_handler_parser();} );
    FThread_guard mhpp_g( message_handler_parser_ );

    std::cout << "start timestamps_manager_" << std::endl;
    std::thread timestamps_manager_( [this]{thr_timestamps_manager();} );
    FThread_guard tm_g(timestamps_manager_);

    std::cout << "start occurrences_manager_" << std::endl;
    std::thread occurrences_manager_( [this]{thr_occurrences_manager();} );
    FThread_guard om_g(occurrences_manager_);

    std::cout << "start message_handler_render_" << std::endl;
    std::thread message_handler_render_( [this]{thr_messages_handler_render();} );
    FThread_guard mhpr_g( message_handler_render_ );

    std::cout << "start check_memory_" << std::endl;
    std::thread check_memory_( [this]{thr_check_memory();} );
    FThread_guard mem_g( check_memory_ );

    std::cout << "SENDING START DONE" <<std::endl;
    std::shared_ptr<void> content_send;
    FMessages msg_send(START, content_send );
    _m_push_queue_parser->push( std::make_shared<FMessages>(msg_send) );
}





void core_thread(std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _pop_queue_parser, 
           std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _push_queue_parser,
           std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _pop_queue_render,
           std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _push_queue_render){

	FCore core(_pop_queue_parser, _push_queue_parser, _pop_queue_render, _push_queue_render);

    std::cout << "start FCore" << std::endl;

    core.thr_FCore();
}





float FCore::get_container_content(int id, float t1){
    bool isContinue = false;
    for(auto it = m_containers.at(id)->getPatternList().begin(); it != m_containers.at(id)->getPatternList().end(); ++it ){
        if( it->tBegin >= t1 ){
            auto it_tmp = it;
            ++it_tmp;
            if(it->tEnd <= it_tmp->tBegin + 0.01 || it->tEnd >= it_tmp->tBegin - 0.01){
                isContinue = true;
            }else{
                isContinue = false;
            }

            if(!isContinue){
                return it->tEnd;
            }
        }
    }

    return m_containers.at(id)->getPatternList().end()->tEnd;
}





bool FCore::is_container_full(int id, float t1, float t2){
    bool isContinue = false;
    for(auto it = m_containers.at(id)->getPatternList().begin(); it != m_containers.at(id)->getPatternList().end(); ++it ){
        if( it->tBegin >= t1 ){
            auto it_tmp = it;
            ++it_tmp;
            if(it->tEnd <= it_tmp->tBegin + 0.01 || it->tEnd >= it_tmp->tBegin - 0.01){
                isContinue = true;
            }else{
                isContinue = false;
            }

            if(isContinue && it->tEnd >t2 ){
                return true;
            }
        }

        if( it->tBegin > t1 && it->tEnd > t2 ){
            return false;
        }
    }

    return false;
}





patternStruct FCore::get_first_pattern(int contId, float beginTime){
	for(auto it = m_containers.at(contId)->getPatternList().begin(); it != m_containers.at(contId)->getPatternList().end(); ++it ){
		if( it->tEnd >= beginTime ){
			std::cout << "CORE >>> IN GET_FIRST_PATTERN in container : " << it->contId << ", beginning at : " << it->tBegin << " and ending at : " << it->tEnd << std::endl;
			return *it;
		}
	}
	patternStruct result = { -1, contId, beginTime, beginTime };
	return result ;
}




patternStruct FCore::get_next_pattern(patternStruct current_pattern ){
	int contId = current_pattern.contId;
	for(auto it = m_containers.at(contId)->getPatternList().begin(); it != m_containers.at(contId)->getPatternList().end(); ++it ){
		if( it->tBegin == current_pattern.tBegin ){
			return *(++it);
		}
	}
	patternStruct result = { -1, current_pattern.contId, ( --m_containers.at(contId)->getPatternList().end() )->tEnd, ( --m_containers.at(contId)->getPatternList().end() )->tEnd };
	return result ;
}





bool FCore::contains_occurrence(int idPattern, int idOccurrence){
	for(auto it = m_occurrences[idPattern]->begin(); it != m_occurrences[idPattern]->end(); ++it ){
		if( (*it)->getId() == idOccurrence){
			return true;
		}else if( (*it)->getId() > idOccurrence ){
			return false;
		}
	}
	return false;
}

std::shared_ptr<FOccurrence> FCore::find_occurrence(int idPattern, int idOccurrence){
	for(auto it = m_occurrences[idPattern]->begin(); it != m_occurrences[idPattern]->end(); ++it ){
		if( (*it)->getId() == idOccurrence){
			return (*it);
		}
	}	
	return NULL;
}

std::vector<int> FCore::get_containers_id(){
	std::vector<int> result;
	for(auto it = m_containers.getMap().begin() ; it != m_containers.getMap().end(); ++it){
		result.push_back( it->second->getId() );
	}
	return result;
}

std::vector<int> FCore::get_patterns_id(){
	std::vector<int> result;
	for(auto it = m_patterns.getMap().begin() ; it != m_patterns.getMap().end(); ++it){
		result.push_back( it->second->getId() );
	}
	return result;
}

void FCore::get_total_time(){
	float result = 0;
	for(auto it = m_containers.getMap().begin() ; it != m_containers.getMap().end(); ++it){
		if( it->second->getEndTime() > result )
			result = it->second->getEndTime() > result ;
	}

	std::cout << "absolute time = " << result << std::endl;

	auto end_time_send = std::static_pointer_cast<void>( std::make_shared<int>(result) );
    FMessages msg_send( START, end_time_send );
    _m_push_queue_render->push( std::make_shared<FMessages>(msg_send) );
}