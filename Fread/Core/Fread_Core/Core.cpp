/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Core.cpp
 * Author: guillem
 * 
 * Created on 17 décembre 2016, 15:26
 */

#include "Core.h"

Core::Core(std::shared_ptr< threadsafe_list<s_display2occurrences> > display2occurrences,
           std::shared_ptr< threadsafe_list<s_display2threads> > display2threads, 
           std::shared_ptr< threadsafe_list<s_core2display> > core2display, 
           std::shared_ptr< threadsafe_list<s_parser2occurrences> > parser2occurrences,
           std::shared_ptr< threadsafe_list<s_parser2threads> > parser2threads, 
           std::shared_ptr< threadsafe_list<s_core2parser> > core2parser):
        m_display2occurrences(display2occurrences),
        m_display2threads(display2threads),
        m_core2display(core2display),
        m_parser2occurrences(parser2occurrences),
        m_parser2threads(parser2threads),
        m_core2parser(core2parser)
{
}

Core::Core(const Core& orig) {
    
}

Core::~Core() {
    
}

void Core::thr_occurrences_manager(){
    s_display2occurrences display_message_received;
    s_parser2occurrences parser_message_received;
    while(1){
        //gets messages from display and parser
        if(!m_display2occurrences->empty()){
            display_message_received = m_display2occurrences->pop_back();
        }
        if( !m_parser2occurrences->empty() ){
            parser_message_received = m_parser2occurrences->pop_back();
        }
        
        if(display_message_received != NULL){
            //checks if in memory
            if(m_occurrences.contains(display_message_received.occ)){
                s_occurrences result = m_occurrences.at(display_message_received.occ);
                s_core2display message = {result, NULL};
                m_core2display->push_back(message);
            //if not in memory, sends to the parser    
            }else{
                s_occurrences result = m_occurrences.at(display_message_received.occ);
                s_core2parser message = {result};
                m_core2parser->push_back(message);
            }
        }
        
        //sends the message got from parser and puts it in memory
        if(parser_message_received != NULL){
            s_occurrences result = parser_message_received.occ;
            s_core2display message = {result, NULL};
            m_core2display->push_back(message);
            
            m_occurrences.insert(result.id, result);
        }
    }
}

void Core::thr_threads_manager(){
    s_display2threads display_message_received;
    s_parser2threads parser_message_received;
    while(1){
        //gets messages from display and parser
        if(!m_display2threads->empty()){
            display_message_received = m_display2threads->pop_back();
        }
        if( !m_parser2threads->empty() ){
            parser_message_received = m_parser2threads->pop_back();
        }
        
        //checks if in memory
        if(m_threads.contains(display_message_received.thr)){
            s_threads result = m_threads.at(display_message_received.thr);
            s_core2display message = {NULL, result};
            m_core2display->push_back(message);
        //if not in memory, sends to the parser    
        }else{
            s_threads result = m_threads.at(display_message_received.thr);
            
            s_core2parser message = {result};
            m_core2parser->push_back(message);
        }
        
        
        //sends the message got from parser and puts it in memory
            s_threads result = parser_message_received.thr;
            s_core2display message = {NULL, result};
            m_core2display->push_back(message);
            
            m_threads.insert(result.id, result);
        
    }
}

void  Core::check_memory(){
    if(m_occurrences.size() > MAX_SIZE){
        m_occurrences.erase( m_occurrences.begin() );
    }
    
    if(m_threads.size() > MAX_SIZE){
        m_threads.erase( m_threads.begin() );
        
    }
}

void Core::thr_core(){
    std::thread threads_manager_( thr_threads_manager() );
    thread_guard tm_g(threads_manager_);
    std::thread occurrences_manager_( thr_occurrences_manager() );
    thread_guard om_g(occurrences_manager_);
    
    while(1){
        check_memory();
    }  
}