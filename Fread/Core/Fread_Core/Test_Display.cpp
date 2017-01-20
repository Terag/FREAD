/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test_Display.cpp
 * Author: guillem
 * 
 * Created on 19 janvier 2017, 23:21
 */

#include "Test_Display.h"

Test_Display::Test_Display(std::shared_ptr< threadsafe_list<s_display2occurrences> > display2occurrences,
                std::shared_ptr< threadsafe_list<s_display2threads> > display2threads, 
                std::shared_ptr< threadsafe_list<s_core2display> > core2display):
                m_display2occurrences(display2occurrences),
                m_display2threads(display2threads),
                m_core2display(core2display)
{    
}

Test_Display::Test_Display(const Test_Display& orig) {
}

Test_Display::~Test_Display() {
}

void Test_Display::thr_test_display(){
    s_core2display core_message_received;
    while(1){
        //gets messages from display and parser
        if(!m_core2display->empty()){
            core_message_received = m_core2display->pop_back();
        }
        
        if(core_message_received != NULL){
            if(core_message_received.occ != NULL){
                int msg = core_message_received.occ.id;
                std::cout << "occurrences : " << msg << std::endl; 
            }else if(core_message_received.thr != NULL){
                int msg = core_message_received.thr.id;
                std::cout << "threads : " << msg << std::endl; 
            }
        }
    }
}

void Test_Display::thr_test_display_send(){
    int i = 1;
    while(i <= 10000){
        m_display2occurrences->push_back( s_occurrences{i} );
        m_display2threads->push_back( s_threads(i) );
        i++;
    }
}

