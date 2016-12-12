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

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

typedef enum {
    INT,
    FLOAT,
    DOUBLE,
    STRING,
    COLOR,
    DATE
} FieldType;

typedef struct {
    std::string name;
    std::string type;
} FieldDef;

typedef struct {
    unsigned char id;
    std::string name;
    std::vector<FieldDef> fieldDefs;
} EventDef;

class Reader_MainTrace {
public:
    Reader_MainTrace(std::string mainTrace_Path);
    
    virtual ~Reader_MainTrace();
private:

    std::string mainTrace_Path;
    std::ifstream mainTrace_Stream;
    std::vector<EventDef> eventDefs;
    
    void parseHeader();
    void eventDef();
    void fieldDef(int eventID);
    
};

#endif /* READER_MAINTRACE_HPP */

