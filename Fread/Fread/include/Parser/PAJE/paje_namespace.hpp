/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   paje_namespace.hpp
 * Author: terag
 *
 * Created on December 19, 2016, 6:55 PM
 */

#ifndef PAJE_NAMESPACE_HPP
#define PAJE_NAMESPACE_HPP

namespace paje
{
    std::vector<EventDef> eventDefs;
    
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
    PEF_PajeDefineContainerType,    //0
    PEF_PajeDefineStateType,        //1
    PEF_PajeDefineEventType,        //2
    PEF_PajeDefineVariableType,     //3
    PEF_PajeDefineLinkType,         //4
    PEF_PajeDefineEntityValue,      //5
    PEF_PajeStartDefinePattern,     //6
    PEF_PajeEndDefinePattern,       //7
    //Container events
    PEF_PajeCreateContainer,        //8
    PEF_PajeDestroyContainer,       //9
    //State events
    PEF_PajeSetState,               //10
    PEF_PajePushState,              //11
    PEF_PajePopState,               //12
    PEF_PajeResetState,             //13
    //Event events
    PEF_PajeNewEvent,               //14
    //Variable events
    PEF_PajeSetVariable,            //15
    PEF_PajeAddVariable,            //16
    PEF_PajeSubVariable,            //17
    //Link events
    PEF_PajeStartLink,              //18
    PEF_PajeEndLink,                //19
    //Include events
    PEF_IncludeFile,                //20
    //Pattern events
    PEF_PajeStartPattern,           //21
    PEF_PajeEndPattern,             //22
} PajeEventFunction;

void DefineContainerType(std::string line);
void DefineStateType(std::string line);
void DefineEventType(std::string line);
void DefineVariableType(std::string line);
void DefineLinkType(std::string line);
void DefineEntityValue(std::string line);
void StartDefinePattern(std::string line);
void EndDefinePattern(std::string line);

typedef void (*PAJE_EventFunc)(std::string, EventDef);

PAJE_EventFunc eventFunctions[8]{   DefineContainerType,    //PEF_PajeDefineContainerType
                                    DefineStateType,        //PEF_PajeDefineStateType
                                    DefineEventType,        //PEF_PajeDefineEventType
                                    DefineVariableType,     //PEF_PajeDefineVariableType
                                    DefineLinkType,         //PEF_PajeDefineLinkType
                                    DefineEntityValue,      //PEF_PajeDefineLinkType
                                    StartDefinePattern,     //PEF_PajeStartDefinePattern
                                    EndDefinePattern        //PEF_PajeEndDefinePattern
                                };

}


#endif /* PAJE_NAMESPACE_HPP */

