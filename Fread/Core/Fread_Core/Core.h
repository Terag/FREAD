/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Core.h
 * Author: guillem
 *
 * Created on 17 décembre 2016, 15:26
 */

#ifndef CORE_H
#define CORE_H

#define MAX_SIZE 200

#include <vector>

#include "thread_guard.h"
#include "threadsafe_list.h"
#include "threadsafe_hashmap.h"
#include "structures.h"

class Core {
public:
    Core(  std::shared_ptr< threadsafe_list<s_display2occurrences> > display2occurrences,
           std::shared_ptr< threadsafe_list<s_display2threads> > display2threads, 
           std::shared_ptr< threadsafe_list<s_core2display> > core2display, 
           std::shared_ptr< threadsafe_list<s_parser2occurrences> > parser2occurrences,
           std::shared_ptr< threadsafe_list<s_parser2threads> > parser2threads, 
           std::shared_ptr< threadsafe_list<s_core2parser> > core2parser);
    
    Core(const Core& orig);
    
    virtual ~Core();
    
    void thr_core();
    
    
private:
    std::shared_ptr< threadsafe_list<s_display2occurrences> > m_display2occurrences;
    std::shared_ptr< threadsafe_list<s_display2threads> > m_display2threads;
    std::shared_ptr< threadsafe_list<s_parser2occurrences> > m_parser2occurrences;
    std::shared_ptr< threadsafe_list<s_parser2threads> > m_parser2threads;
    std::shared_ptr< threadsafe_list<s_core2display> > m_core2display;
    std::shared_ptr< threadsafe_list<s_core2parser> > m_core2parser;
    
    threadsafe_hashmap<int, s_occurrences> m_occurrences;
    threadsafe_hashmap<int, s_threads> m_threads;
    
    void thr_threads_manager();
    void thr_occurrences_manager();
    
    //check_memory ensure that the two map are not too big
    void check_memory();
};

#endif /* CORE_H */

