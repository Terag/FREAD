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

#include "Parser/PAJE/paje_namespace.hpp"

namespace paje
{
    class Reader_MainTrace {
    public:
        Reader_MainTrace(std::string mainTrace_Path);

        virtual ~Reader_MainTrace();
        
        static std::vector<PajeTypeDef> typesDef;
        
    private:
        
        std::vector<EventDef> eventDefs;

        std::string mainTrace_Path;
        std::ifstream mainTrace_Stream;
        

        void parseHeader();
        void createHierarchie();
        void eventDef(std::string &in);
        void fieldDef(int eventID, std::string &in);
    };
}

#endif /* READER_MAINTRACE_HPP */

