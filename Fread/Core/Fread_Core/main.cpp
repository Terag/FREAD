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

#include "FCore.hpp"
#include "FThread_guard.hpp"
#include "FQueue.hpp"
#include "FMessages.hpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    std::shared_ptr<FQueue< FMessages<> > > _pop_queue_parser = std::make_shared< FQueue< FMessages<> > >();
    std::shared_ptr<FQueue< FMessages<> > > _push_queue_parser = std::make_shared< FQueue< FMessages<> > >();
    std::shared_ptr<FQueue< FMessages<> > > _pop_queue_renderer = std::make_shared< FQueue< FMessages<> > >();
    std::shared_ptr<FQueue< FMessages<> > > _push_queue_renderer = std::make_shared< FQueue< FMessages<> > >();
    
    FCore fread_core(_pop_queue_parser,
                    _push_queue_parser,
                    _pop_queue_renderer,
                    _push_queue_renderer
                   );
    
    std::thread core_( fread_core.thr_FCore() );
    FThread_guard gc(core_);
      
    return 0;
}

