/*
Copyright (c) 2017, FREAD - Jérôme Berthelin, Emma Goldblum, Maxime Guillem, Victor Rouquette
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Neither the name of the copyright holders nor the names of its contributors 
  may be used to endorse or promote products derived from this software without
  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
*/

#ifndef PAJE_TYPEDEFS_HPP
#define PAJE_TYPEDEFS_HPP

#include "Parser/statesConfig.hpp"
#include "FColor.hpp"
#include "FOccurrence.hpp"

#include <vector>
#include <string>
#include <memory>

namespace paje
{
    typedef enum {
        FT_INT,
        FT_STRING,
        FT_COLOR,
        FT_DATE,
        FT_DOUBLE,
        FT_HEX,
        FT_UNDEFINED
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
        FN_UNDEFINED
    } FieldName;

    typedef enum {
        //PajeTypeDef events
        PEF_PajeDefineContainerType,    //0
        PEF_PajeDefineStateType,        //1
        PEF_PajeDefineEventType,        //2
        PEF_PajeDefineVariableType,     //3
        PEF_PajeDefineLinkType,         //4
        PEF_PajeDefineEntityValue,      //5
        //PajePatternDef events
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
        PEF_IncludeContainerFile,       //21
        PEF_IncludePatternFile,         //22
        //Pattern events
        PEF_PajeStartPattern,           //23
        PEF_PajeEndPattern,             //24
        //Error case
        PEF_Undefined                   //25
    } PajeEventFunction;
    
    typedef enum {
        PT_CONTAINER    = 0x1,
        PT_STATE        = 0x2,
        PT_EVENT        = 0x4,
        PT_VARIABLE     = 0x8,
        PT_LINK         = 0x10,
        PT_VALUE        = 0x20,
        PT_UNDEFINED    = 0x40
    } PajeType;
    
    typedef struct {
        PajeType type;

        FieldType nameType;
        std::string name_str;
        int name_int;

        FieldType typeType;
        std::string type_str;
        int type_int;
        
        FieldType aliasType;
        std::string alias_str;
        int alias_int;

        FieldType startContainerTypeType;
        std::string startContainerType_str;
        int startContainerType_int;

        FieldType endContainerTypeType;
        std::string endContainerType_str;
        int endContainerType_int;
        
        StateType state;

        FColor color;
    } PajeTypeDef;

    typedef struct {
        FieldName name;
        FieldType type;
    } FieldDef;

    typedef struct {
        int id;
        std::string name_str;
        PajeEventFunction name;
        std::vector<FieldDef> fieldDefs;
    } EventDef;  
}

#endif /* PAJE_TYPEDEFS_HPP */

