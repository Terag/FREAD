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

#include "list_wrapper_fullProtection.h"
#include "Core.h"
#include "structures.h"
#include "thread_guard.h"
#include "Test_Parser.h"
#include "Test_Display.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    list_wrapper_fullProtection<s_core2display> p_core2display();
    list_wrapper_fullProtection<s_core2parser> p_core2parser();
    
    list_wrapper_fullProtection<s_display2occurrences> p_display2occurrences();
    list_wrapper_fullProtection<s_display2threads> p_display2threads();
    
    list_wrapper_fullProtection<s_parser2occurrences> p_parser2occurrences();
    list_wrapper_fullProtection<s_parser2threads> p_parser2threads();
    
    Core fread_core(std::make_shared(p_display2occurrences),
                    std::make_shared(p_display2threads),
                    std::make_shared(p_core2display),
                    std::make_shared(p_parser2occurrences),
                    std::make_shared(p_parser2threads),
                    std::make_shared(p_core2parser) );
    
    Test_Parser test_parser(std::make_shared(p_parser2occurrences),
                std::make_shared(p_parser2threads),
                std::make_shared(p_core2parser) );
    
    Test_Display test_display(std::make_shared(p_display2occurrences),
                 std::make_shared(p_display2threads),
                 std::make_shared(p_core2display));
    
    std::thread core_( fread_core.thr_core() );
    thread_guard gc(core_);
    
    std::thread parser_( test_parser.thr_test_parser() );
    thread_guard gp(parser_);
    
    std::thread display_( test_display.thr_test_display() );
    thread_guard gd(display_);
    
    std::thread display_send_( test_display.thr_test_display_send() );
    thread_guard gds(display_send_);    
    
    return 0;
}

