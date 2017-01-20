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

template<typename Key, typename T>
class threadsafe_hashmap {
public:
    virtual std::shared_ptr<T> at(const Key& k);
    virtual void insert(Key key, T element);
    //virtual void erase(Key k);
    //virtual void erase(T element);
    virtual void erase(std::unordered_map<Key, T>::iterator it);
    virtual bool contains(T element);
    virtual std::shared_ptr<T> operator[](const T);
    
    typedef typename std::unordered_map<Key, T>::iterator begin();
    
    virtual unsigned int size() const;
    virtual bool empty();
    
private:
    std::unordered_map<Key, T> m_unordered_map;
    std::mutex m_mutex; 
};

#endif /* THREADSAFE_HASHMAP_H */

