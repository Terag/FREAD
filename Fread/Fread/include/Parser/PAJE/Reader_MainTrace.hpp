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
    FT_INT,
    FT_STRING,
    FT_COLOR,
    FT_DATE,
    FT_DOUBLE,
    FT_HEX,
} FieldType;

typedef enum {
    FN_NAME,
    FN_TYPE,
    FN_ALIAS,
    FN_COLOR,
    FN_TIME,
    FN_CONTAINER,
    FN_VALUE,
    FN_STARTCONTAINER,
    FN_ENDCONTAINER,
    FN_KEY,
    FN_FILE,
} FieldName;

typedef enum {
    //PajeTypeDef events
    PEF_PajeDefineContainerType,
    PEF_PajeDefineStateType,
    PEF_PajeDefineEventType,
    PEF_PajeDefineVariableType,
    PEF_PajeDefineLinkType,
    PEF_PajeDefineEntityValue,
    PEF_PajeStartDefinePattern,
    PEF_PajeEndDefinePattern,
    //Container events
    PEF_PajeCreateContainer,
    PEF_PajeDestroyContainer,
    //State events
    PEF_PajeSetState,
    PEF_PajePushState,
    PEF_PajePopState,
    PEF_PajeResetState,
    //Event events
    PEF_PajeNewEvent,
    //Variable events
    PEF_PajeSetVariable,
    PEF_PajeAddVariable,
    PEF_PajeSubVariable,
    //Link events
    PEF_PajeStartLink,
    PEF_PajeEndLink,
    //Include events
    PEF_IncludeFile,
    //Pattern events
    PEF_PajeStartPattern,
    PEF_PajeEndPattern,
} PajeEventFunction;



typedef struct {
    std::string name;
    FieldType type;
} FieldDef;

typedef struct {
    unsigned char id;
    PajeEventFunction name;
    std::vector<FieldDef> fieldDefs;
} EventDef;

class Reader_MainTrace {
public:
    Reader_MainTrace(std::string mainTrace_Path);
    
    //Read Line
    
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

