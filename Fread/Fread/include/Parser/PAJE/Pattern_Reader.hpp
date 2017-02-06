/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * This class is use to parse and read a pattern file
 */

#ifndef PATTERN_READER_HPP
#define PATTERN_READER_HPP
#include <string>
#include <fstream>
#include "FOccurrence.hpp"
#include "paje_interface.hpp"
#include "paje_typedefs.hpp"

#include <vector>
#include <string>
#include <fstream>

namespace paje 
{   
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

            Pattern_Reader();
            Pattern_Reader(std::string const& c_alias, int c_id);

            void init(std::string const& path, int const& id);
            void parseHeader(std::vector<EventDef>& eventDefs);
            
            void openStream();
            void closeStream();
            std::string getLine();
            bool end();

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
    
    //Buffer uses in paje_interface to stock informations with fast access.
    
    typedef struct {
        std::vector<std::string> alias;
        std::vector<StateType> states;
        std::vector<float> timeStamps;
        float t_begin;
        float t_end;
    } Occurrence_Buffer;

    typedef struct {
        int id;
        std::string alias;
        std::shared_ptr<Occurrence_Buffer> occurrence_buffer;
        std::unique_ptr<Pattern_Reader> reader;
    } Pattern_Buffer;
}

#endif /* PATTERN_READER_HPP */

