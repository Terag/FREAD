/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hashmap_wrapper_fullProtection.cpp
 * Author: guillem
 * 
 * Created on 19 janvier 2017, 19:52
 */

#include "hashmap_wrapper_fullProtection.h"

hashmap_wrapper_fullProtection::hashmap_wrapper_fullProtection() {
}

hashmap_wrapper_fullProtection::hashmap_wrapper_fullProtection(const hashmap_wrapper_fullProtection& orig) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_unordered_map = orig.m_unordered_map;
}

hashmap_wrapper_fullProtection::~hashmap_wrapper_fullProtection() {
}
template<Key, T>
std::shared_ptr<T> hashmap_wrapper_fullProtection::at(const Key& k){
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_unordered_map.at(k);
}

template<Key, T>
void hashmap_wrapper_fullProtection::insert(const Key& key, T element){
    std::lock_guard<std::mutex> lock(m_mutex);
    m_unordered_map.insert(key, element);
}

template<Key, T>
void hashmap_wrapper_fullProtection::erase(Key k){
    std::lock_guard<std::mutex> lock(m_mutex);
    m_unordered_map.erase(k);
}

template<Key, T>
void hashmap_wrapper_fullProtection::erase(T element){
    std::lock_guard<std::mutex> lock_mutex(m_mutex);
    m_unordered_map.erase(T);
}

template<Key, T>
void hashmap_wrapper_fullProtection::erase(std::unordered_map<Key, T>::iterator it){
    std::lock_guard<std::mutex> lock(m_mutex);
    m_unordered_map.erase(it);
}

template<Key, T>
bool hashmap_wrapper_fullProtection::contains(T element){
    std::lock_guard<std::mutex> lock(m_mutex);
    for(auto it = m_unordered_map.begin(); it != m_unordered_map.end(); ++it){
        if(it == element){
            return true;
        }
        return false;
    }
}

template<Key, T>
std::shared_ptr<T> hashmap_wrapper_fullProtection::operator[](const Key key){
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_unordered_map[key];
}
    
template<Key, T>
std::unordered_map<Key, T>::iterator hashmap_wrapper_fullProtection::begin(){
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_unordered_map.begin();
}

template<Key, T>
unsigned int hashmap_wrapper_fullProtection::size() const{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_unordered_map.size();
}

template<Key, T>
bool hashmap_wrapper_fullProtection::empty(){
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_unordered_map.empty(); 
}

