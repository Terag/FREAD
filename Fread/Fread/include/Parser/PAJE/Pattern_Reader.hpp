/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pattern_reader.hpp
 * Author: terag
 *
 * Created on February 1, 2017, 12:42 AM
 */

#ifndef PATTERN_READER_HPP
#define PATTERN_READER_HPP
#include <string>
#include <fstream>
#include "FOccurrence.hpp"

class Pattern_Reader {
    private:
        int id;
        std::string alias;
        int current_occurence;
        int occurrence_list_begining_line;
        
        bool readyToRead;

        std::string pattern_Path;

        std::ifstream pattern_Stream;    
        
    public:

        //Pattern_Reader(std::string const& c_alias, int c_idl);
        Pattern_Reader();
        //Pattern_Reader(const Pattern_Reader& orig);
        void init(std::string const& path, int const& c_id, FOccurrence& occurrence);

        //getter
        int getId() const {return id;}
        std::string getAlias() const {return alias;}
        int getCurrentOccurence() const {return current_occurence;}
        int getOccurrenceListBegining() const {return occurrence_list_begining_line;}
        
        //setter
        void setId(int const& newId) {id = newId;}
        void setAlias(std::string const& newAlias) {alias = newAlias;}
        void setCurrentOccurence(int const& current) {current_occurence = current;}
        void setOccurrenceListBeginingLine(int const& begining) {occurrence_list_begining_line = begining;}
        
        //Return ready boolean value
        bool isReadyToRead() const {return readyToRead;}
        
        virtual ~Pattern_Reader();

};

#endif /* PATTERN_READER_HPP */

