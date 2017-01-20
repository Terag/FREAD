/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   list_wrapper_fullProtection.cpp
 * Author: guillem
 * 
 * Created on 17 décembre 2016, 15:52
 */

#include "list_wrapper_fullProtection.h"

list_wrapper_fullProtection::list_wrapper_fullProtection()
{
}

list_wrapper_fullProtection::list_wrapper_fullProtection(const list_wrapper_fullProtection& orig) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_list = orig.m_list;
}

list_wrapper_fullProtection::~list_wrapper_fullProtection() {
}

template<typename T>
std::shared_ptr<T> list_wrapper_fullProtection::pop_back(){
    std::lock_guard<std::mutex> lock(m_mutex);
    if( !m_list.empty())
        return std::shared_ptr<T> std::make_shared<T>(NULL);
    std::shared_ptr<T> const _element( std::make_shared<T>(m_list.back) );
    m_list.pop_back();
    return _element;
}

template<typename T>
void list_wrapper_fullProtection::push_back(T element){
    std::lock_guard<std::mutex> lock(m_mutex);
    m_list.push_back(element);
}

template<typename T>
std::shared_ptr<T> list_wrapper_fullProtection::pop_front(){
    std::lock_guard<std::mutex> lock(m_mutex);
    if(!m_list.empty())
        return std::shared_ptr<T> std::make_shared<T>(NULL);
    std::shared_ptr<T> const _element(std::make_shared<T>(m_list[0]));
    m_list.erase( m_list.begin() );
    return _element;
}

template<typename T>
void list_wrapper_fullProtection::push_front(T element){
    std::lock_guard<std::mutex> lock(m_mutex);
    m_list.push_front(element);
}

template<typename T>
unsigned int list_wrapper_fullProtection::size() const{
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_list.size();
}

template<typename T>
bool list_wrapper_fullProtection::empty(){
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_list.empty();
}
