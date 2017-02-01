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

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <memory>
#include <mutex>
#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>

template<typename T>
class FQueue
{   
public:
    FQueue():
            head(new node),
            tail(head.get())
    {
    }

    FQueue(const FQueue& other)=delete;
    FQueue& operator=(const FQueue& other)=delete;

    void setOtherCondition(std::shared_ptr<std::mutex> _mutex, 
                           std::shared_ptr<std::condition_variable> _condition_variable);
    
    std::shared_ptr<T> try_pop();
    
    std::shared_ptr<T> wait_and_pop();
    
    void push(T new_value);
    
    bool empty();
    
private:
    struct node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };
    
    std::unique_ptr<node> head;
    node* tail;
    
    std::mutex m_mutex_mine;
    std::condition_variable m_data_cond_mine;
    
    std::shared_ptr< std::mutex > _m_mutex_other;
    std::shared_ptr< std::condition_variable > _m_data_cond_other;
};

#include "FQueue.tpp"

#endif /* QUEUE_HPP */

