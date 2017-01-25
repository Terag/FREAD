/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FMessages.hpp
 * Author: guillem
 *
 * Created on 25 janvier 2017, 16:05
 */

#ifndef FMESSAGES_HPP
#define FMESSAGES_HPP

#include <memory>

enum HEADER{
     START,
     INITDONE,
     TIMESTAMP,
     INITDONE,
     CONTAINER,
     PATTERN,
     OCCURRENCE
};

template<typename T>
class FMessages{
public:
    
    //give a content to the constructor it will make a shared_ptr of it
    FMessages(HEADER header, T content);
    FMessages(const Core& orig);
    
    FMessages& operator=(const FMessages&);
    
    virtual ~FMessages();
    
    HEADER getHeader();
    void setHeader(HEADER var);
    
    std::shared_ptr<T> getContent();
    void setContent(T var);
    
private:
    HEADER m_header;
    std::shared_ptr<T> m_content;
};

FMessages::FMessages(HEADER header, 
                     T content):
                     m_header(header),
                     m_content(std::make_shared<T>(content))
{    
}

FMessages& FMessages::operator=(const FMessages& other){
    m_header = other.getHeader();
    m_content = other.getContent();  
}

HEADER FMessages::getHeader(){
    return m_header;
}

void FMessages::setHeader(HEADER var){
    m_header = var;
}

template<typename T>
std::shared_ptr<T> FMessages::getContent(){
    return m_content;
}

template<typename T>
void FMessages::setContent(T var){
    m_content = var;
}

#endif /* FMESSAGES_HPP */

