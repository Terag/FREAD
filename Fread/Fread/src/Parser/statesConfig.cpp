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


#include "Parser/statesConfig.hpp"

using namespace std;

StatesConfig::StatesConfig(std::string const& path) :
    conf_path(path)
{
}

StateType StatesConfig::getState(std::string const& name, std::string const& alias) {
    for(auto it : events){
        if(it.name == name && it.alias == alias) {
            return it.state;
        }
    }
    return STATE_UNKNOW;
}

void StatesConfig::initEvents() {
    string in;
    StateType currentState = STATE_UNKNOW;
    events.clear();
    
    cout << "Opening : " << conf_path << endl;
    conf_stream.open(conf_path);
    if(conf_stream.is_open()) {
        do {
            getline(conf_stream, in);
            cout << " ----- Get line : " << in << endl;
            if(in[0] == '#'){
                currentState = stringToState(in.substr(1));
            } else {
                events.push_back(defineEvent(in, currentState));
            }
        } while(!conf_stream.eof());
    conf_stream.close();
    } else {
        cout << "file is not open" << endl;
    }
    
    for(auto it : events) {
        cout << "State : " << it.state << " Name : " << it.name << " Alias : " << it.alias << endl; 
    }
}

StateType StatesConfig::stringToState(std::string const& str) {
    if(str == "Wait_states") {
        return STATE_WAIT;
    }
    else if (str == "Compute_states") {
        return STATE_COMPUTE;
    }
    else if (str == "Send_states") {
        return STATE_SEND;
    }
    else {
        return STATE_UNKNOW;
    }
}

Conf_EventType StatesConfig::defineEvent(std::string const& line, StateType current) {
    pair<string, string> params = getParamInLine(line);
    
    Conf_EventType newEventType;
    newEventType.name = params.first;
    newEventType.alias = params.second;
    newEventType.state = current;
    
    return newEventType;
}

std::pair<std::string,std::string> StatesConfig::getParamInLine(string const& line) {
    std::pair<std::string, std::string> params;
    string str = line;
    
    auto fpos = str.find('\"');
    auto spos = str.find('\"', fpos+1);
    params.first = str.substr(fpos+1, spos-1);
    
    fpos = str.find('\"', spos+1);
    spos = str.find('\"', fpos+1);
    cout << "f=" << fpos << " s=" << spos << endl;
    //params.second = str.substr(fpos+1, spos-1);
    params.second = "";
    for(auto i=fpos+1; i<spos; i++) {
        params.second.push_back(line[i]);
    }
    
    return params;
}

StatesConfig::~StatesConfig() {
}

