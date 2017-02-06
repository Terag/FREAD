/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pattern_reader.cpp
 * Author: terag
 * 
 * Created on February 1, 2017, 12:42 AM
 */

#include "Parser/PAJE/Pattern_Reader.hpp"
#include "Parser/PAJE/paje_interface.hpp"

using namespace std;

namespace paje
{
    Pattern_Reader::Pattern_Reader() {
    }

    Pattern_Reader::Pattern_Reader(const std::string& c_alias, int c_id) :
        alias(c_alias), id(c_id)
    {
    }

    void Pattern_Reader::init(const std::string& path, const int& c_id) {
        pattern_Path = path;
        id = id;


    }

    void Pattern_Reader::parseHeader(std::vector<EventDef>& eventDefs) {
        string in;
        int event_id;
        int spacePos;
        
        pattern_Stream.open(pattern_Path);
        
        do{
            getline(pattern_Stream, in);
            spacePos = in.find(" ");
            event_id = stoi(in.substr(0, spacePos));
            if(eventDefs[event_id].name == PEF_PajeStartDefinePattern){
                break;
            }
        } while(!pattern_Stream.eof());
        //cout << "calling : " << event_id << " event : " << eventDefs[event_id].name << endl;
        PajeEventCall(in, eventDefs[event_id]);
        
        do {
            getline(pattern_Stream, in);
            spacePos = in.find(" ");
            event_id = stoi(in.substr(0, spacePos));
            //cout << "calling : " << event_id << " event : " << eventDefs[event_id].name << endl;
            PajeEventCall(in, eventDefs[event_id]);
            if(eventDefs[event_id].name == PEF_PajeEndDefinePattern){
                //cout << "break" << endl;
                break;
            }
        } while(!pattern_Stream.eof());
        pattern_Stream.close();
    }

    void Pattern_Reader::openStream() {
        pattern_Stream.open(pattern_Path);
    }

    void Pattern_Reader::closeStream() {
        pattern_Stream.close();
    }

    std::string Pattern_Reader::getLine() {
        string in;
        if(!pattern_Stream.eof()) {
            getline(pattern_Stream, in);
        };
        return "!";
    }

    bool Pattern_Reader::end() {
        return pattern_Stream.eof();
    }

    Pattern_Reader::~Pattern_Reader() {
    }
}

