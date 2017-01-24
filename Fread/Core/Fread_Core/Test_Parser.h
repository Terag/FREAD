/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test_Parser.h
 * Author: guillem
 *
 * Created on 19 janvier 2017, 23:05
 */

#ifndef TEST_PARSER_H
#define TEST_PARSER_H

#include "structures.h"
#include <cstdlib>

class Test_Parser {
public:
    Test_Parser(std::shared_ptr< threadsafe_list<s_parser2occurrences> > parser2occurrences,
                std::shared_ptr< threadsafe_list<s_parser2threads> > parser2threads, 
                std::shared_ptr< threadsafe_list<s_core2parser> > core2parser);
    Test_Parser(const Test_Parser& orig);
    virtual ~Test_Parser();
    
    void thr_test_parser();
    
private:
    std::shared_ptr< threadsafe_list<s_parser2occurrences> > m_parser2occurrences;
    std::shared_ptr< threadsafe_list<s_parser2threads> > m_parser2threads;
    std::shared_ptr< threadsafe_list<s_core2parser> > m_core2parser;

};

#endif /* TEST_PARSER_H */

