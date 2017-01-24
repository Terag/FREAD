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

Parser::Parser() :
    initDone(false)
{
}

Parser::Parser(shared_ptr<FQueue<string>> popQueue, shared_ptr<FQueue<string>> pushQueue) :
    initDone(false), pop_queue(popQueue), push_queue(pushQueue)
{
}

Parser::Parser(const Parser& orig) {
}


void Parser::awake(const std::string& path) {
    trace_path = path;
    PARSER::awake(path);
}

void Parser::start() {
    auto msg = *(pop_queue->wait_and_pop());
    if(msg == "Start"){
        initDone = PARSER::start();
    } else {
        cout << "wrong start message : " << msg << endl;
    }
    string send_msg = "done";
    push_queue->push(send_msg);
}

void Parser::listenAndProcess() {
    
}

Parser::~Parser() {
    
}

//TO DO : ajouter des retoure d'erreurs sur les fonction awake et start
void parser_thread(std::string path, std::shared_ptr<FQueue<std::string>> popQueue, std::shared_ptr<FQueue<std::string>> pushQueue) {
    cout << "thread launched" << endl;
    
    Parser parser(popQueue, pushQueue);
    
    parser.awake(path);
    
    parser.start();
    
    parser.listenAndProcess();
}

