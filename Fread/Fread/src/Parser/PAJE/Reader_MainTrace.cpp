/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Reader_MainTrace.cpp
 * Author: terag
 * 
 * Created on December 7, 2016, 3:00 PM
 */

using namespace std;

#include "Parser/PAJE/Reader_MainTrace.hpp"

Reader_MainTrace::Reader_MainTrace(string path) :
    mainTrace_Path(path)
{
    parseHeader();
}

void Reader_MainTrace::parseHeader()
{
    string in;
    int size = -1;
    int i = 0;
    
    mainTrace_Stream.open(mainTrace_Path);
    while(!mainTrace_Stream.eof()){
        mainTrace_Stream >> in;
        if(in == "EventDef"){
            i++;
            mainTrace_Stream >> in;
            mainTrace_Stream >> i;
            if(i>size){
                size = i+1;
            }
        }
        mainTrace_Stream.ignore(256, '%');
    }
    mainTrace_Stream.close();
    
    eventDefs.reserve(size + 1);
    for(int i = 0; i < size + 1; i++){
        eventDefs.push_back(EventDef());
    }
    
    mainTrace_Stream.open(mainTrace_Path);
    mainTrace_Stream.ignore(256, '%');
    while(!mainTrace_Stream.eof()) {
        mainTrace_Stream >> in;
        if(in == "EventDef"){
            eventDef();
        }
        mainTrace_Stream.ignore(256, '%');
    }
    mainTrace_Stream.close();
    
    /*for(auto it : eventDefs){
        if(it.name != ""){
            cout << it.name << " " << (int)it.id << " et " << it.fieldDefs.size() << " fields" << endl;
        }
    }*/
}

void Reader_MainTrace::eventDef()
{
    string in;
    int id;
    
    mainTrace_Stream >> in;
    mainTrace_Stream >> id;
    eventDefs[id].id = id;
    eventDefs[id].name = PEF_IncludeFile;
    
    mainTrace_Stream >> in;
    while(in != "%EndEventDef"){
        if(in == "%"){
            fieldDef(id);
        }
        mainTrace_Stream >> in;
    }
}

void Reader_MainTrace::fieldDef(int eventID)
{
    FieldDef newField;
    string name;
    mainTrace_Stream >> name;
    if(name == "Name"){
        cout << "name" << endl;
    }
    else if(name == "Type"){
        cout << "type" << endl;
    }
    else if(name == "Alias"){
        cout << "alias" << endl;
    }
    
    string type;
    mainTrace_Stream >> type;
    if(type == "string"){
        newField.type = FT_STRING;
    }
    else if(type == "int"){
        newField.type = FT_INT;
    }
    else if(type == "color"){
        newField.type = FT_COLOR;
    }
    else if(type == "date"){
        newField.type = FT_DATE;
    }
    else if(type == "double"){
        newField.type = FT_DOUBLE;
    }
    else if(type == "hex"){
        newField.type = FT_HEX;
    } 
    else {
        cout << "error, unknow fieldType" << endl;
    }
    eventDefs[eventID].fieldDefs.push_back(newField);
}

Reader_MainTrace::~Reader_MainTrace() {
}

