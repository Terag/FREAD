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

Core::Core(threadsafe_vector display2core, threadsafe_vector parser2core):
        m_display2core(display2core),
        m_parser2core(parser2core)
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
    
}

void Core::thr_threads_manager(){
    
}

void Core::route_display_messages(){
    s_display2core message = m_display2core.pop_front();
    if(message != NULL){
        if(message.type == OCCURRENCE){
            
        }else if(message.type == THREAD){
            
        }
    }
}

void Core::route_parser_messages(){
    s_parser2core message = m_parser2core.pop_front(); 
    if( message != NULL ){
        if(message.type == OCCURRENCE){
            
        }else if(message.type == THREAD){
            
        }
    }
}