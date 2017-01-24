/*
Boost Software License - Version 1.0 - August 17th, 2003
 * Modified by Victor Rouquette - January 2017

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
 */

/* 
 * File:   FThread_guard.hpp
 * Author: guillem
 *
 * Created on 24 janvier 2017, 16:05
 */

#ifndef FTHREAD_GUARD_HPP
#define FTHREAD_GUARD_HPP

#include <thread>

class FThread_guard {
public:
    explicit FThread_guard(std::thread& t);
    thread_guard(FThread_guard const&)=delete;
    FThread_guard& operator=(FThread_guard const&)=delete;
    virtual ~FThread_guard();

private:
    std::thread& m_thread;

};

FThread_guard::FThread_guard(std::thread& t):
m_thread(t)
{
}

FThread_guard::~FThread_guard() {
    if(m_thread.joinable()){
        m_thread.join();
    }
}

#endif /* FTHREAD_GUARD_HPP */

