/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   thread_guard.h
 * Author: guillem
 *
 * Created on 18 décembre 2016, 02:23
 */

#ifndef THREAD_GUARD_H
#define THREAD_GUARD_H

#include <thread>

class thread_guard {
public:
    explicit thread_guard(std::thread& t);
    thread_guard(thread_guard const&)=delete;
    thread_guard& operator=(thread_guard const&)=delete;
    virtual ~thread_guard();

private:
    std::thread& m_thread;

};

#endif /* THREAD_GUARD_H */

