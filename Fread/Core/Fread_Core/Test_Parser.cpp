/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test_Parser.cpp
 * Author: guillem
 * 
 * Created on 19 janvier 2017, 23:05
 */

#include "Test_Parser.h"

Test_Parser::Test_Parser(std::shared_ptr< threadsafe_list<s_parser2occurrences> > parser2occurrences,
                std::shared_ptr< threadsafe_list<s_parser2threads> > parser2threads, 
                std::shared_ptr< threadsafe_list<s_core2parser> > core2parser):
                m_parser2occurrences(parser2occurrences),
                m_parser2threads(parser2threads),
                m_core2parser(core2parser)
{
}

Test_Parser::Test_Parser(const Test_Parser& orig) {
}

Test_Parser::~Test_Parser() {
}

void Test_Parser::thr_test_parser(){
    s_core2parser core_message_received;
    while(1){
        //gets messages from display and parser
        if(!m_core2parser->empty()){
            core_message_received = m_core2parser->pop_back();
        }
        
        if(core_message_received != NULL){
            if(core_message_received.occ != NULL){
                int msg = core_message_received.occ.id;
                m_parser2occurrences->push_back( s_occurrences{-msg} );
            }else if(core_message_received.thr != NULL){
                int msg = core_message_received.thr.id;
                m_parser2threads->push_back( s_threads{-msg} );
            }
        }
    }
}
