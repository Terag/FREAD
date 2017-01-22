/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hashmap_wrapper_fullProtection.h
 * Author: guillem
 *
 * Created on 19 janvier 2017, 19:52
 */

#ifndef HASHMAP_WRAPPER_FULLPROTECTION_H
#define HASHMAP_WRAPPER_FULLPROTECTION_H

template<typename Key, typename T>
class hashmap_wrapper_fullProtection : threadsafe_hashmap {
public:
    hashmap_wrapper_fullProtection();
    hashmap_wrapper_fullProtection(const hashmap_wrapper_fullProtection& orig);
    virtual ~hashmap_wrapper_fullProtection();
    
    std::shared_ptr<T> at(const Key& k);
    void insert(const Key& key, T element);
    //void erase(Key k);
    //void erase(T element);
    void erase(std::unordered_map<Key, T>::iterator it);
    bool contains(T element);
    std::shared_ptr<T> operator[](const T);
    threadsafe_list& operator=(const threadsafe_list&) = delete;
    
    std::unordered_map<Key, T>::iterator begin();
    
    unsigned int size() const;
    bool empty();
    
private:
    std::unordered_map<Key, T> m_unordered_map;
    std::mutex m_mutex; 
};

#endif /* HASHMAP_WRAPPER_FULLPROTECTION_H */

