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

#include "Parser/PAJE/paje_interface.hpp"
#include "Parser/PAJE/paje_typedefs.hpp"

namespace paje
{
    class Reader_MainTrace {
    public:
        Reader_MainTrace();
        void init(std::string const& path);

        virtual ~Reader_MainTrace();

        void parseHeader(std::vector<EventDef>& eventDefs);
        
        void openStream();
        void closeStream();
        std::string getLine();
        bool end();
        
    private:

        std::string mainTrace_Path;
        std::ifstream mainTrace_Stream;

        void eventDef(std::vector<EventDef>& eventDefs, std::string &in);
        FieldDef fieldDef(std::string &in);
    };
}

#endif /* READER_MAINTRACE_HPP */

