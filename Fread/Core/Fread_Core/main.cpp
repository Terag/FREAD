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

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    std::mutex mx_display2core;
    std::mutex mx_parser2core;
    
    vector_wrapper_fullProtection<s_display2core> p_display2core(std::vector<s_display2core>, mx_display2core);
    vector_wrapper_fullProtection<s_parser2core> p_parser2core(std::vector<s_parser2core>, mx_parser2core);
    
    Core fread_core(p_display2core, p_parser2core);
    
    std::thread core_( fread_core.thr_core() );
    thread_guard g(core_);
    
    
    return 0;
}

