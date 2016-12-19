/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   list_wrapper_fullProtection.h
 * Author: guillem
 *
 * Created on 17 décembre 2016, 15:52
 */

#ifndef LIST_WRAPPER_FULLPROTECTION_H
#define LIST_WRAPPER_FULLPROTECTION_H

#include <list>
#include <mutex>
#include <memory>

template<typename T>
class list_wrapper_fullProtection : threadsafe_list {
public:
    list_wrapper_fullProtection(std::list<T> my_list, std::mutex my_mutex);
    list_wrapper(const list_wrapper_fullProtection& orig);
    virtual ~list_wrapper_fullProtection();
    
    std::shared_ptr<T> pop_back();
    void push_back(T element);
    std::shared_ptr<T> pop_front();
    void push_front(T element);
    
    unsigned int size() const;
    bool empty();
    
private:
    std::list<T> m_list;
    std::mutex m_mutex; 

};

#endif /* LIST_WRAPPER_FULLPROTECTION_H */

