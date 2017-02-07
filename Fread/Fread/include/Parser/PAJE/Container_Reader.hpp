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

/*
 * This class is use to parse and read a container file
 */

#ifndef CONTAINER_READER_HPP
#define CONTAINER_READER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <memory>
#include <utility>

#include "FContainer.hpp"
#include "paje_typedefs.hpp"


namespace paje
{   
    class Container_Reader {
    private:
        std::string alias;
        int id;
        int curseur_line;
        std::pair<float, float> timestamps_begin_end;
        
        bool readyToRead;

        std::string container_Path;

        std::ifstream container_Stream;   
        
        float lineTime(std::string const& line);
        
    public:

        Container_Reader(std::string const& c_alias, int c_id);
        
        void init(std::string const& path, int const& c_id);
        //FContainer start();

        //getter
        int getId() const {return id;}
        std::string getAlias() const {return alias;}
        float getBeginTime() const {return timestamps_begin_end.first;}
        float getEndTime() const {return timestamps_begin_end.second;}
        
        //setter
        void setId(int const& newId) {id = newId;}
        void setAlias(std::string const& newAlias) {alias = newAlias;}
        void setBeginTime(float const& t_begin) {timestamps_begin_end.first = t_begin;}
        void setEndTime(float const& t_end) {timestamps_begin_end.second = t_end;}
        
        //Verify if container_reader has all attributes defined to be use
        void checkIfReady();
        //Return ready boolean value
        bool isReadyToRead() const {return readyToRead;}
        
        std::vector<std::string> getLinesBetweenTwoTimes(float const& t1, float const& t2);
        
        virtual ~Container_Reader();

    };
    
    typedef struct {
        int id;
        std::string name;
        std::string alias;
        PajeTypeDef type;
        float beginTime;
        float endTime;
        std::unique_ptr<Container_Reader> reader;
    } Container_Buffer;
}

#endif /* CONTAINER_READER_HPP */

