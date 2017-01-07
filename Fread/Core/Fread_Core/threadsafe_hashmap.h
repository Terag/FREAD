/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   threadsafe_hashmap.h
 * Author: guillem
 *
 * Created on 5 janvier 2017, 16:42
 */

#ifndef THREADSAFE_HASHMAP_H
#define THREADSAFE_HASHMAP_H

#include <unordered_map>

template<typename T>
class threadsafe_hashmap {
public:
    virtual std::shared_ptr<T> at();
    virtual void insert(T element);
    virtual void erase();
    virtual std::shared_ptr<T> operator[](const T);
    threadsafe_list& operator=(const threadsafe_list&) = delete;
    
    virtual unsigned int size() const = 0;
    virtual bool empty();
    
private:
    std::unordered_map<T> m_unordered_map;
    std::mutex m_mutex; 
};

#endif /* THREADSAFE_HASHMAP_H */

