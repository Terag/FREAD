/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: guillem
 *
 * Created on 17 décembre 2016, 14:45
 */

#include <cstdlib>
#include <thread>
#include <mutex>

#include "FMessages_structure.hpp"
#include "FCore.hpp"
#include "FThread_guard.hpp"
#include "Test_Parser.h"
#include "Test_Display.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    std::shared_ptr<FQueue<msg_parser> > _pop_queue_parser = std::make_shared< FQueue<msg_parser> >();
    std::shared_ptr<FQueue<msg_parser> > _push_queue_parser = std::make_shared< FQueue<msg_parser> >();
    std::shared_ptr<FQueue<msg_renderer> > _pop_queue_renderer = std::make_shared< FQueue<msg_renderer> >();
    std::shared_ptr<FQueue<msg_renderer> > _push_queue_renderer = std::make_shared< FQueue<msg_renderer> >();
    
    Core fread_core(_pop_queue_parser,
                    _push_queue_parser,
                    _pop_queue_renderer,
                    _push_queue_renderer
                   );
    /*
    Test_Parser test_parser(std::make_shared(p_parser2occurrences),
                std::make_shared(p_parser2threads),
                std::make_shared(p_core2parser) );
    
    Test_Display test_display(std::make_shared(p_display2occurrences),
                 std::make_shared(p_display2threads),
                 std::make_shared(p_core2display));
    */
    
    std::thread core_( fread_core.thr_core() );
    FThread_guard gc(core_);
    
    /*
    std::thread parser_( test_parser.thr_test_parser() );
    thread_guard gp(parser_);
    
    std::thread display_( test_display.thr_test_display() );
    thread_guard gd(display_);
    
    std::thread display_send_( test_display.thr_test_display_send() );
    thread_guard gds(display_send_);    
    */
      
    return 0;
}

