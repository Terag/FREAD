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
 * this file is use to launch parser part and communicate with core.
 * You have to communicate with this part if you code your own parser for FREAD
 */

#ifndef PARSER_HPP
#define PARSER_HPP

#include "Parser/parser_specifications.hpp"
#include "FQueue.hpp"
#include "FMessages.hpp"
#include "FContainer.hpp"
#include "FPattern.hpp"
#include "FOccurrence.hpp"

#include <string>
#include <memory>

class Parser {
private:

    bool initDone;
    
    std::shared_ptr<FQueue<std::shared_ptr<FMessages>>> pop_queue;
    std::shared_ptr<FQueue<std::shared_ptr<FMessages>>> push_queue;
    
    std::string trace_path;
    
public:
    Parser();
    Parser(std::shared_ptr<FQueue<std::shared_ptr<FMessages>>> popQueue, std::shared_ptr<FQueue<std::shared_ptr<FMessages>>> pushQueue);
    
    //Call with thread init
    void awake(std::string const& path);
    //Launch parser when START is received in Pop_queue
    void start();
    //Listen on pop_queue and send request to parser_interface
    void listenAndProcess();
    //Send msg in push_queue
    void send(std::shared_ptr<FMessages> msg);
    
    virtual ~Parser();
};

//Function uses to launch parser thread
void parser_thread(std::string path, std::shared_ptr<FQueue<std::shared_ptr<FMessages>>> popQueue, std::shared_ptr<FQueue<std::shared_ptr<FMessages>>> pushQueue);

/*---------------------- Send functions -------------------------*/

void sendContainerToCore(FContainer const& container);

void sendPatternToCore(FPattern const& pattern);

void sendOccurenceToCore(FOccurrence const& occurrence);

void sendPatternStructToCore(patternStruct const& patternS);

#endif /* PARSER_HPP */

