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

#include "thread_guard.h"
#include "threadsafe_list.h"

class Core {
public:
    Core(threadsafe_list display2core, threadsafe_list parser2core);
    Core(const Core& orig);
    
    virtual ~Core();
    
    void thr_core();

    
private:
    threadsafe_list m_display2core;
    threadsafe_list m_parser2core;
    
    void thr_threads_manager();
    void thr_occurrences_manager();
    
    void route_parser_messages();
    void route_display_messages();
};

#endif /* CORE_H */

