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

#include <string>
#include <vector>

namespace paje
{
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
        FN_STARTCONTAINERTYPE,
        FN_ENDCONTAINERTYPE,
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
    
    typedef enum {
        PT_CONTAINER,
        PT_STATE,
        PT_EVENT,
        PT_VARIABLE,
        PT_LINK,
        PT_VALUE,
    } PajeType;
    
    typedef struct {
        FieldType nameType;
        union {
            std::string name_str;
            int name_int;
        };
        FieldType typeType;
        union {
            std::string type_dtr;
            int type_int;
        };
        FieldType aliasType;
        union {
            std::string alias_str;
            int alias_int;
        };
    } PajeContainerType;
    
    typedef struct {
        FieldType nameType;
        union {
            std::string name_str;
            int name_int;
        };
        FieldType typeType;
        union {
            std::string type_dtr;
            int type_int;
        };
        FieldType aliasType;
        union {
            std::string alias_str;
            int alias_int;
        };
    } PajeStateType;
    
    typedef struct {
        FieldType nameType;
        union {
            std::string name_str;
            int name_int;
        };
        FieldType typeType;
        union {
            std::string type_dtr;
            int type_int;
        };
        FieldType aliasType;
        union {
            std::string alias_str;
            int alias_int;
        };  
    } PajeEventType;

    typedef struct {        
        FieldType nameType;
        union {
            std::string name_str;
            int name_int;
        };
        FieldType typeType;
        union {
            std::string type_dtr;
            int type_int;
        };
        FColor color;
        FieldType aliasType;
        union {
            std::string alias_str;
            int alias_int;
        };
    } PajeVariableType;
    
    typedef struct {
        FieldType nameType;
        union {
            std::string name_str;
            int name_int;
        };
        FieldType typeType;
        union {
            std::string type_dtr;
            int type_int;
        };
        FieldType StartContainerTypeType;
        union {
            std::string StartContainerType_str;
            int StartContainerType_int;
        };
        FieldType EndContainerTypeType;
        union {
            std::string EndContainerType_str;
            int EndContainerType_int;
        };
        FieldType aliasType;
        union {
            std::string alias_str;
            int alias_int;
        };        
    } PajeLinkType;
        
    typedef struct {
        FieldType nameType;
        union {
            std::string name_str;
            int name_int;
        };
        FieldType typeType;
        union {
            std::string type_dtr;
            int type_int;
        };
        FColor color;
        FieldType aliasType;
        union {
            std::string alias_str;
            int alias_int;
        };
    } PajeValueType;
    
    typedef struct {
        PajeType type;
        union {
            PajeContainerType container;
            PajeStateType state;
            PajeEventType event;
            PajeVariableType variable;
            PajeLinkType link;
            PajeValueType value;
        };
    } PajeTypeDef;

    typedef struct {
        FieldName name;
        FieldType type;
    } FieldDef;

    typedef struct {
        int id;
        string name_str;
        PajeEventFunction name;
        std::vector<FieldDef> fieldDefs;
    } EventDef;
    
    typedef void (*PAJE_EventFunc)(std::string, EventDef);

    void PajeEventCall(std::string line, EventDef event);
}


#endif /* PAJE_NAMESPACE_HPP */

