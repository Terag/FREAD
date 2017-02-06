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

#include "Parser/parser_specifications.hpp"
#include "Parser/parser.hpp"

using namespace std;

static Parser parser;

Parser::Parser() 
{    
}

Parser::Parser(std::shared_ptr<FQueue<msg_coreToParser>> popQueue, std::shared_ptr<FQueue<msg_parserToCore>> pushQueue) :
    initDone(false), pop_queue(popQueue), push_queue(pushQueue)
{
}

void Parser::awake(const std::string& path) {
    trace_path = path;
    PARSER::awake(path);
}

void Parser::start() {
    auto msg = *(pop_queue->wait_and_pop());
    if(msg.header == H_START){
        cout << "go parse" << endl;
        initDone = PARSER::start();
    } else {
        cout << "wrong start message : " << *msg.content << endl;
    }
    msg_parserToCore msg_send;
    msg_send.header = H_INITDONE;
    msg_send.content = make_shared<string>("Init Done");
    push_queue->push(msg_send);
}

void Parser::listenAndProcess() {
    
}

Parser::~Parser() {
    
}

//TO DO : ajouter des retoure d'erreurs sur les fonction awake et start
void parser_thread(std::string path, std::shared_ptr<FQueue<msg_coreToParser>> popQueue, std::shared_ptr<FQueue<msg_parserToCore>> pushQueue) {
    cout << "thread launched" << endl;
    
    parser = Parser(popQueue, pushQueue);
    
    parser.awake(path);
    
    parser.start();
    
    paje::getEventsBetweenTwoTimesInContainer(2, 0.f, 1.f);
    
    parser.listenAndProcess();
}

void sendContainerToCore(FContainer const& container) {
    
}

void sendPatternToCore(FPattern const& pattern) {
    
}

void sendOccurenceToCore(FOccurrence const& occurrence) {
    
}
