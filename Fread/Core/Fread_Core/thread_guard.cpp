/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   thread_guard.cpp
 * Author: guillem
 * 
 * Created on 18 décembre 2016, 02:23
 */

#include "thread_guard.h"

thread_guard::thread_guard(std::thread& t):
m_thread(t)
{
}

thread_guard::~thread_guard() {
    if(m_thread.joinable()){
        m_thread.join();
    }
}

