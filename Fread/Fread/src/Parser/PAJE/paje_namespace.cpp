/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Parser/PAJE/paje_namespace.hpp"

namespace paje
{   
    void DefineContainerType(std::string line, EventDef event);
    void DefineStateType(std::string line, EventDef event);
    void DefineEventType(std::string line, EventDef event);
    void DefineVariableType(std::string line, EventDef event);
    void DefineLinkType(std::string line, EventDef event);
    void DefineEntityValue(std::string line, EventDef event);
    void StartDefinePattern(std::string line, EventDef event);
    void EndDefinePattern(std::string line, EventDef event);
    
    static PAJE_EventFunc eventFunctions[8] = { DefineContainerType,    //PEF_PajeDefineContainerType
                                                DefineStateType,        //PEF_PajeDefineStateType
                                                DefineEventType,        //PEF_PajeDefineEventType
                                                DefineVariableType,     //PEF_PajeDefineVariableType
                                                DefineLinkType,         //PEF_PajeDefineLinkType
                                                DefineEntityValue,      //PEF_PajeDefineEntityValue
                                                StartDefinePattern,     //PEF_PajeStartDefinePattern
                                                EndDefinePattern        //PEF_PajeEndDefinePattern
                                             };
    
    void PajeEventCall(std::string line, EventDef event)
    {
        if(event.name < 0 || event.name > 8){
            eventFunctions[function](line, event);
        } 
        else if (event.id = -1){
            cout << "error, eventDef not set" << endl;
        }
        else {
            cout << "error, unknow function : " << event.name << " " << event.name_str << endl;
        }
    }
    
    void DefineContainerType(std::string line, EventDef event)
    {
        
    }
    
    void DefineStateType(std::string line, EventDef event)
    {
        
    }
    
    void DefineEventType(std::string line, EventDef event)
    {
        
    }
    
    void DefineVariableType(std::string line, EventDef event)
    {
        
    }
    
    void DefineLinkType(std::string line, EventDef event)
    {
        
    }
    
    void DefineEntityValue(std::string line, EventDef event)
    {
        
    }
    
    void StartDefinePattern(std::string line, EventDef event)
    {
        
    }
    
    void EndDefinePattern(std::string line, EventDef event)
    {
        
    }
}