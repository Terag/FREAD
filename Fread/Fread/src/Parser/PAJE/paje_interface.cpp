/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <vector>
#include <stdexcept>
#include <bitset>

#include "Parser/PAJE/paje_interface.hpp"
#include "Parser/PAJE/Reader_MainTrace.hpp"

using namespace std;

namespace paje
{   
    typedef void (*PAJE_EventFunc)(std::string, const EventDef&);
    
    void DefineContainerType(std::string line, EventDef const& event);
    void DefineStateType(std::string line, EventDef const& event);
    void DefineEventType(std::string line, EventDef const& event);
    void DefineVariableType(std::string line, EventDef const& event);
    void DefineLinkType(std::string line, EventDef const& event);
    void DefineEntityValue(std::string line, EventDef const& event);
    void StartDefinePattern(std::string line, EventDef const& event);
    void EndDefinePattern(std::string line, EventDef const& event);
    
    void setName(PajeTypeDef& newPJT, string str, FieldType const& type);
    void setType(PajeTypeDef& newPJT, string str, FieldType const& type);
    void setAlias(PajeTypeDef& newPJT, string str, FieldType const& type);
    void setStartContainerType(PajeTypeDef& newPJT, string str, FieldType const& type);
    void setEndContainerType(PajeTypeDef& newPJT, string str, FieldType const& type);
    void setColor(PajeTypeDef& newPJT, string str);
    
    void parseMainTrace();
    void initType(PajeTypeDef& newPJT);
    void defineType(string const& line, EventDef const& event, PajeType type);
    string getNextParamInLine(string const& line, int &spacePos);
    
    static Reader_MainTrace mainTrace;
    
    static PAJE_EventFunc eventFunctions[8] = { DefineContainerType,    //PEF_PajeDefineContainerType
                                                DefineStateType,        //PEF_PajeDefineStateType
                                                DefineEventType,        //PEF_PajeDefineEventType
                                                DefineVariableType,     //PEF_PajeDefineVariableType
                                                DefineLinkType,         //PEF_PajeDefineLinkType
                                                DefineEntityValue,      //PEF_PajeDefineEntityValue
                                                StartDefinePattern,     //PEF_PajeStartDefinePattern
                                                EndDefinePattern        //PEF_PajeEndDefinePattern
                                             };
    
    static vector<EventDef> eventDefs;
    
    static vector<PajeTypeDef> typeDefs;
    
    void awake(string const& path){
        mainTrace.init(path);
        mainTrace.parseHeader(eventDefs);
    }
    
    void start() {
        parseMainTrace();
        for (auto it : typeDefs) {
            switch (it.nameType){
                case FT_STRING :
                    cout << it.type << " name : " << it.name_str;
                    break;
                case FT_INT :
                    cout << it.type << " name : " << it.name_int;
                    break;
                default :
                    cout << "error, unexpected type : " << it.typeType;
                    break;
            }
            switch (it.typeType){
                case FT_STRING :
                    cout << " - type : " << it.type_str;
                    break;
                case FT_INT :
                    cout << " - type : " << it.type_int;
                    break;
                default :
                    cout << "error, unexpected type : " << it.typeType;
                    break;
            }
            if(it.color.a > 0){
                cout << " - color : " << it.color.r << " " << it.color.g << " " << it.color.b;
            }
            switch (it.aliasType){
                case FT_STRING :
                    cout << " - alias : " << it.alias_str << endl;
                    break;
                case FT_INT :
                    cout <<" - alias : " << it.alias_int << endl;
                    break;
                default :
                    cout << "error, unexpected type : " << it.typeType;
            }
        }
    }
    
    void parseMainTrace(){
        int id;
        int fpos;
        string line;
        
        mainTrace.openStream();
        line = mainTrace.getLine();
        while(!mainTrace.end() && line != "!"){
            
            try{
                fpos = line.find(' ');
                id = stoi(line.substr(0,fpos));
            }
            catch(const std::invalid_argument& ia){
                cout << "error, invalid format : " << ia.what() << " parameter " << line.substr(0, fpos) << endl;
            }
            
            if(eventDefs[id].name > -1 && eventDefs[id].name < 8){
                cout << "function call : " << eventDefs[id].id << " ";
                eventFunctions[eventDefs[id].name](line, eventDefs[id]);
            } 
            else if (eventDefs[id].id == -1){
                cout << "error, eventDef not set : " << eventDefs[id].id << endl;
            }
            else {
                cout << "error, unknow function : " << eventDefs[id].name << " " << eventDefs[id].name_str << endl;
            }
            line = mainTrace.getLine();
        }
        
        mainTrace.closeStream();
    }
    
    void DefineContainerType(std::string line, EventDef const& event) {
        cout << "DefineContainerType function called with : " << event.name_str << " " << event.name << endl;
        
        defineType(line, event, PT_CONTAINER);
    }
    
    void DefineStateType(std::string line, EventDef const& event) {
        cout << "DefineStateType function called with : " << event.name_str << " " << event.name << endl;
        
        defineType(line, event, PT_STATE);        
    }
    
    void DefineEventType(std::string line, EventDef const& event) {
        cout << "DefineEventType function called with : " << event.name_str << " " << event.name << endl;
        
        defineType(line, event, PT_EVENT);
    }
    
    void DefineVariableType(std::string line, EventDef const& event) {
        cout << "DefineVariableType function called with : " << event.name_str << " " << event.name << endl;
        
        defineType(line, event, PT_VARIABLE);
    }
    
    void DefineLinkType(std::string line, EventDef const& event) {
        cout << "DefineLinkType function called with : " << event.name_str << " " << event.name << endl;
        
        defineType(line, event, PT_LINK);
    }
    
    void DefineEntityValue(std::string line, EventDef const& event) {
        cout << "DefineEntityValue function called with : " << event.name_str << " " << event.name << endl;
        
        defineType(line, event, PT_VALUE);
    }
    
    void initType(PajeTypeDef& newPJT){
        newPJT.type = PT_UNDEFINED;
        
        newPJT.nameType = FT_UNDEFINED;
        newPJT.typeType = FT_UNDEFINED;
        newPJT.aliasType = FT_UNDEFINED;
        newPJT.startContainerTypeType = FT_UNDEFINED;
        newPJT.endContainerTypeType = FT_UNDEFINED;
        newPJT.color = FColor();
    }
    
    void defineType(string const& line, EventDef const& event, PajeType type) {
        int spacePos;
        string sub_str;
        
        PajeTypeDef newPajeType;
        initType(newPajeType);
        
        newPajeType.type = type;
        spacePos = line.find(' ');
        
        for (auto it : event.fieldDefs){
            sub_str = getNextParamInLine(line, spacePos);
            switch(it.name){
                case FN_NAME :
                    setName(newPajeType, sub_str, it.type);
                    break;
                case FN_TYPE :
                    setType(newPajeType, sub_str, it.type);
                    break;
                case FN_ALIAS :
                    setAlias(newPajeType, sub_str, it.type);
                    break;
                case FN_STARTCONTAINERTYPE :
                    setStartContainerType(newPajeType, sub_str, it.type);
                    break;
                case FN_ENDCONTAINERTYPE :
                    setEndContainerType(newPajeType, sub_str, it.type);
                    break;
                case FN_COLOR :
                    setColor(newPajeType, sub_str);
                    break;
                default :
                    cout << "error, unexpected FieldName : " << it.name << endl;
                    break;
            }
        }
        typeDefs.push_back(newPajeType);
    }
  
    string getNextParamInLine(string const& line, int &spacePos) {
        int fpos,spos;
        fpos = spacePos;
        string sub_str;
        if(line.substr(fpos, 1) == " "){
            if(line.substr(fpos+1, 1) == "\""){
                spos = line.find("\"", fpos+2);
                spacePos = line.find(" ", spos);
                sub_str = line.substr(fpos+2, spos-fpos-2);
                return sub_str;
            }
            else {
                spos = line.find(" ", fpos+1);
                spacePos = spos;
                sub_str = line.substr(fpos+1, spos-fpos-1);
                return sub_str;
            }
        }
        else if(fpos == 0){
            if(line.substr(fpos, 1) == "\""){
                spos = line.find("\"", fpos+1);
                spacePos = line.find(" ", spos);
                sub_str = line.substr(fpos+1, spos-fpos-1);
                return sub_str;
            }
            else {
                spos = line.find(" ", fpos);
                spacePos = spos;
                sub_str = line.substr(fpos, spos-fpos);
                return sub_str;
            }
        }
        else {
            cout << "error, " << spacePos << " is not a space position in line : " << line << endl;
            return "!";
        }
    }
    
    void setName(PajeTypeDef& newPJT, string str, FieldType const& type){
        switch(type){
            case FT_STRING :
                newPJT.nameType = FT_STRING;
                newPJT.name_str = str;
                break;
            case FT_INT :
                newPJT.nameType = FT_INT;
                newPJT.name_int = stoi(str);
                break;
            default :
                cout << "error, unexpected FieldType : " << type << endl;
                break;
        }
    }
    
    void setType(PajeTypeDef& newPJT, string str, FieldType const& type){
        switch(type){
            case FT_STRING :
                newPJT.typeType = FT_STRING;
                newPJT.type_str = str;
                break;
            case FT_INT :
                newPJT.typeType = FT_INT;
                newPJT.type_int = stoi(str);
                break;
            default :
                cout << "error, unexpected FieldType : " << type << endl;
                break;
        }
    }
    
    void setAlias(PajeTypeDef& newPJT, string str, FieldType const& type){
        switch(type){
            case FT_STRING :
                newPJT.aliasType = FT_STRING;
                newPJT.alias_str = str;
                break;
            case FT_INT :
                newPJT.aliasType = FT_INT;
                newPJT.alias_int = stoi(str);
                break;
            default :
                cout << "error, unexpected FieldType : " << type << endl;
                break;
        }
    }
    
    void setStartContainerType(PajeTypeDef& newPJT, string str, FieldType const& type){
        switch(type){
            case FT_STRING :
                newPJT.startContainerTypeType = FT_STRING;
                newPJT.startContainerType_str = str;
                break;
            case FT_INT :
                newPJT.startContainerTypeType = FT_INT;
                newPJT.startContainerType_int = stoi(str);
                break;
            default :
                cout << "error, unexpected FieldType : " << type << endl;
                break;
        }
    }
    
    void setEndContainerType(PajeTypeDef& newPJT, string str, FieldType const& type){
        switch(type){
            case FT_STRING :
                newPJT.endContainerTypeType = FT_STRING;
                newPJT.endContainerType_str = str;
                break;
            case FT_INT :
                newPJT.endContainerTypeType = FT_INT;
                newPJT.endContainerType_int = stoi(str);
                break;
            default :
                cout << "error, unexpected FieldType : " << type << endl;
                break;
        }
    }

    void setColor(PajeTypeDef& newPJT, string str){
        int spacePos = 0;
        int r = (int)(stof(getNextParamInLine(str, spacePos))*255);
        int g = (int)(stof(getNextParamInLine(str, spacePos))*255);
        int b = (int)(stof(getNextParamInLine(str, spacePos))*255);
        newPJT.color = FColor(r, g, b, 255);
    }
    
    void StartDefinePattern(std::string line, EventDef const& event) {
        cout << "DefinePatternStart function called with : " << event.name_str << " " << event.name << endl;
    }
    
    void EndDefinePattern(std::string line, EventDef const& event) {
        cout << "DefinePatternEnd function called with : " << event.name_str << " " << event.name << endl;
    }
}