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
private:
    struct node
    {
        std::shared_ptr<T> data;
        std::unique_ptr<node> next;
    };
    
    std::unique_ptr<node> head;
    node* tail;
    
    std::mutex mut;
    std::condition_variable data_cond;
    
public:
    FQueue():
        head(new node),tail(head.get())
    {}

    FQueue(const FQueue& other)=delete;
    FQueue& operator=(const FQueue& other)=delete;

    std::shared_ptr<T> try_pop();
    
    std::shared_ptr<T> wait_and_pop();
    
    void push(T new_value);
    
    bool empty();
};

template <typename T>
std::shared_ptr<T> FQueue<T>::try_pop()
{
    if(head.get()==tail)
    {
        return std::shared_ptr<T>();
    }
    const std::shared_ptr<T> res(head->data);
    const std::unique_ptr<node> old_head=std::move(head);
    head=std::move(old_head->next);
    return res;
}

template<typename T>
void FQueue<T>::push(T new_value)
{
    std::shared_ptr<T> new_data = std::make_shared<T>(std::move(new_value));
    std::unique_ptr<node> p(new node);
    tail->data=new_data;
    node* const new_tail=p.get();
    tail->next=std::move(p);
    tail=new_tail;
    
    data_cond.notify_one();
}

template<typename T>
std::shared_ptr<T> FQueue<T>::wait_and_pop(){
    std::unique_lock<std::mutex> lk(mut);
    data_cond.wait(lk, [this](){ return !empty();});
    lk.unlock();
    return try_pop();
}

template<typename T>
bool FQueue<T>::empty()
{
    return (head.get() == tail);
}

#endif /* QUEUE_HPP */

