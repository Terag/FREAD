/*
 * Copyright (c) 2017, FREAD - Jérôme Berthelin, Emma Goldblum, Maxime Guillem, Victor Rouquette
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the name of the copyright holders nor the names of its contributors 
 *   may be used to endorse or promote products derived from this software without
 *   specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * This class is use to parse and read state.config file
 * This file describes stateType for all events
 */

#ifndef STATESCONFIG_HPP
#define STATESCONFIG_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

typedef enum {
    STATE_WAIT,
    STATE_COMPUTE,
    STATE_SEND,
    STATE_UNKNOWN
} StateType;

typedef struct {
    std::string name;
    std::string alias;
    StateType state;
} Conf_EventType;

class StatesConfig {
public:
    StatesConfig(std::string const& path = "./states.conf");
    
    void initEvents();
    
    StateType getState(std::string const& name, std::string const& alias);
    
    static StateType stringToState(std::string const& str);
    static std::string stateToString(StateType const& state);
    
    virtual ~StatesConfig();
private:

    std::string conf_path;
    std::ifstream conf_stream;
    
    std::vector<Conf_EventType> events;
    
    Conf_EventType defineEvent(std::string const& line, StateType current);
    std::pair<std::string,std::string> getParamInLine(std::string const& line) ;
};

#endif /* STATESCONFIG_HPP */

