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
#include "FContainer.hpp"

using namespace std;

static Parser parser;

Parser::Parser() 
{    
}

Parser::Parser(std::shared_ptr<FQueue<std::shared_ptr<FMessages>>> popQueue, std::shared_ptr<FQueue<std::shared_ptr<FMessages>>> pushQueue) :
    initDone(false), pop_queue(popQueue), push_queue(pushQueue)
{
}

void Parser::awake(const std::string& path) {
    trace_path = path;
    PARSER::awake(path);
}

void Parser::start() {
    std::shared_ptr<FMessages> msg = *(pop_queue->wait_and_pop());
    if(msg->getHeader() == START){
        cout << "go parse" << endl;
        initDone = PARSER::start();
    } else {
        cout << "wrong start message" << endl;
    }
    std::shared_ptr<FMessages> msg_send = make_shared<FMessages>();
    msg_send->setHeader(INITDONE);
    push_queue->push(msg_send);
}

void Parser::listenAndProcess() {
    while(1){
        std::shared_ptr<FMessages> msg = *(pop_queue->wait_and_pop());
        if(msg->getHeader() == TIMESTAMP) {
            auto content = static_pointer_cast<patternStruct>(msg->getContent);
            PARSER::getEventsBetweenTwoTimesInContainer(content->contId, content->tBegin, content->tEnd);
        }
    }
}

void Parser::send(std::shared_ptr<FMessages> msg) {
    push_queue->push(msg);
}


Parser::~Parser() {
    
}

//TO DO : ajouter des retoure d'erreurs sur les fonction awake et start
void parser_thread(std::string path, std::shared_ptr<FQueue<std::shared_ptr<FMessages>>> popQueue, std::shared_ptr<FQueue<std::shared_ptr<FMessages>>> pushQueue) {
    cout << "thread launched" << endl;
    
    parser = Parser(popQueue, pushQueue);
    
    parser.awake(path);
    
    parser.start();
    
    parser.listenAndProcess();
}

void sendContainerToCore(FContainer const& container) {
    auto content = make_shared<FContainer>(container);
    auto content_void = static_pointer_cast<void>(content);
    auto msg = make_shared<FMessages>(CONTAINER, content_void);
    parser.send(msg);
}

void sendPatternToCore(FPattern const& pattern) {
    auto content = make_shared<FPattern>(pattern);
    auto content_void = static_pointer_cast<void>(content);
    auto msg = make_shared<FMessages>(PATTERN, content_void);
    parser.send(msg);
}

void sendOccurenceToCore(FOccurrence const& occurrence) {
    auto content = make_shared<FOccurrence>(occurrence);
    auto content_void = static_pointer_cast<void>(content);
    auto msg = make_shared<FMessages>(OCCURRENCE, content_void);
    parser.send(msg);
}
