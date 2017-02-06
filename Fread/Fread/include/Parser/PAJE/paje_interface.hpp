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
 * This file is use to be call by parser. He creates a context with some statics elements.
 * When you crate a parser the following functions have to be implemented :
 * - awake
 * - start
 * - getEventsBetweenTwoTimesInContainer
 */

#ifndef PAJE_NAMESPACE_HPP
#define PAJE_NAMESPACE_HPP

#include <string>

#include "Parser/PAJE/paje_typedefs.hpp"

namespace paje
{
    //Call to awake parser and begin parsing of configuration files
    void awake(std::string const& path);
    //Call to launch parser, now he can send messages to core with parser
    bool start();
    //Ask event between two times. It will call send functions in Parser.hpp
    void getEventsBetweenTwoTimesInContainer(int container_id, float t_begin, float t_end);
    
    //use in PAJE context
    void PajeEventCall(std::string line, EventDef &event);
}


#endif /* PAJE_NAMESPACE_HPP */

