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
 * File:   FMap.hpp
 * Author: guillem
 *
 * Created on 28 janvier 2017, 11:42
 */

#ifndef FMAP_HPP
#define FMAP_HPP

#include <unordered_map>
#include <memory>

template<typename K, typename T>
class FMap {
public:
    FMap();
    FMap(const FMap& orig);
    ~FMap();
    
    std::shared_ptr<T> at(const K& k);
    void insert(K key, T element);
    bool erase( std::unordered_map<K, T>::iterator it);
    
    bool contains(T element);
    bool contains(K key);
    
    std::shared_ptr<T> operator[](const K key);
    
    typename std::unordered_map<K, T>::iterator begin();
    
    unsigned int size() const;
    bool empty();
    
    std::unordered_map<K, std::shared_ptr<T> > getMap() const;
    std::mutex getMutex() const;
    
private:
    std::unordered_map<K, std::shared_ptr<T> > m_unordered_map;
    std::mutex m_mutex; 
};

#include "FMap.tpp"

#endif /* FMAP_HPP */

