/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   threadsafe_list.h
 * Author: guillem
 *
 * Created on 17 décembre 2016, 17:28
 */

#ifndef THREADSAFE_LIST_H
#define THREADSAFE_LIST_H

#include <list>

template <typename T>
class threadsafe_list {
public:
    virtual T pop_back();
    virtual void push_back(T element);
    virtual T pop_front();
    virtual void push_front(T element);
    threadsafe_list& operator=(const threadsafe_list&) = delete;
    
    virtual unsigned int size() const;
    virtual bool empty();
    
private:
    std::list<T> m_list;
    std::mutex m_mutex; 

};

#endif /* THREADSAFE_LIST_H */

