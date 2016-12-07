/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Reader_MainTrace.hpp
 * Author: terag
 *
 * Created on December 7, 2016, 3:00 PM
 */

#ifndef READER_MAINTRACE_HPP
#define READER_MAINTRACE_HPP

typedef enum FieldType {
    INT
} FieldType;

struct field {
    std::string name;
    FieldType value;
};

class Reader_MainTrace {
public:
    Reader_MainTrace(std::string mainTrace_Path);
    
    virtual ~Reader_MainTrace();
private:

    std::ifstream mainTrace_Stream;
    
    std::vector<std::vector<field>> Events;
    
};

#endif /* READER_MAINTRACE_HPP */

