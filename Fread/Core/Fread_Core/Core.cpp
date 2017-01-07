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
#include "structures.h"

Core::Core(threadsafe_list display2occurrences, threadsafe_list display2threads, threadsafe_list core2display, threadsafe_list parser2occurrences, threadsafe_list parser2threads, threadsafe_list core2parser):
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

void Core::thr_core(){
    std::thread threads_manager_(thr_threads_manager);
    thread_guard tm_g(threads_manager_);
    std::thread occurrences_manager_(thr_occurrences_manager);
    thread_guard om_g(occurrences_manager_);
    
    while(1){
        route_parser_messages();
        route_display_messages();
    }
    
}

void Core::thr_occurrences_manager(){
    s_display2occurrences display_message_received;
    s_parser2occurrences parser_message_received;
    while(1){
        //gets messages from display and parser
        if(!m_display2occurrences.empty()){
            display_message_received = m_display2occurrences.pop_back();
        }
        
        //checks if in memory
        if(display_message_received != NULL){
            
        }
        
        //if not in memory, sends to parser
        
        //puts message got from parser in memory and sends it
        
    }
}

void Core::thr_threads_manager(){
    s_display2threads display_message_received;
    s_parser2threads parser_message_received;
    while(1){
        //gets messages from dispay and parser
        
        //checks if in memory
        
        //if not in memory, sends to parser
        
        // puts messahe got from parser in memory and sends it
    }
}