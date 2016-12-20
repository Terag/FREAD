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
    typedef struct {
        std::string name;
        paje::FieldType type;
    } FieldDef;

    typedef struct {
        unsigned char id;
        paje::PajeEventFunction name;
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

        void parseHeader();
        void eventDef();
        void fieldDef(int eventID);
    };
}

#endif /* READER_MAINTRACE_HPP */

