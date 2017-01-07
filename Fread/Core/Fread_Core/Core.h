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

#include <vector>

#include "thread_guard.h"
#include "threadsafe_list.h"

class Core {
public:
    Core(threadsafe_list display2core, threadsafe_list parser2core);
    Core(const Core& orig);
    
    virtual ~Core();
    
    void thr_core();
    
    
private:
    threadsafe_list<s_display2occurrences> m_display2occurrences;
    threadsafe_list<s_display2threads> m_display2threads;
    threadsafe_list<s_parser2occurrences> m_parser2occurrences;
    threadsafe_list<s_parser2threads> m_parser2threads;
    threadsafe_list<s_core2display> m_core2display;
    threadsafe_list<s_core2parser> m_core2parser;
    
    threadsafe_hashmap<s_occurrences> m_occurrences;
    threadsafe_hashmap<s_threads> m_threads;
    
    void thr_threads_manager();
    void thr_occurrences_manager();
    
    //the router takes messages from the parser or the displayer and gives it to the corresponding thread
    void route_parser_messages();
    void route_display_messages();
};

#endif /* CORE_H */

