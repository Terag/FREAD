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
 * This class is use to parse and read on a container file
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
    private:

        std::string name;
        std::string parent;
        
        std::string mainTrace_Path;
        std::ifstream mainTrace_Stream;

        void eventDef(std::vector<EventDef>& eventDefs, std::string &in);
        FieldDef fieldDef(std::string &in);
        
    public:
        Reader_MainTrace();
        void init(std::string const& path);

        virtual ~Reader_MainTrace();

        void parseHeader(std::vector<EventDef>& eventDefs);
        
        void openStream();
        void closeStream();
        std::string getLine();
        bool end();
        
        std::string getPath() const {return mainTrace_Path;}
        
    };
}

#endif /* READER_MAINTRACE_HPP */

