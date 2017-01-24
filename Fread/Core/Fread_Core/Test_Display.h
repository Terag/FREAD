/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Test_Display.h
 * Author: guillem
 *
 * Created on 19 janvier 2017, 23:21
 */

#ifndef TEST_DISPLAY_H
#define TEST_DISPLAY_H

#include <cstdlib>

class Test_Display {
public:
    
    Test_Display(std::shared_ptr< threadsafe_list<s_display2occurrences> > display2occurrences,
                std::shared_ptr< threadsafe_list<s_display2threads> > display2threads, 
                std::shared_ptr< threadsafe_list<s_core2display> > core2display);
    
    Test_Display(const Test_Parser& orig);
    virtual ~Test_Display();
    
    void thr_test_display();
    void thr_test_display_send();
    
private:
    std::shared_ptr< threadsafe_list<s_display2occurrences> > m_display2occurrences;
    std::shared_ptr< threadsafe_list<s_display2threads> > m_display2threads;
    std::shared_ptr< threadsafe_list<s_core2display> > m_core2display;

};

#endif /* TEST_DISPLAY_H */

