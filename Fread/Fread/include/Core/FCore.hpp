/*
Boost Software License - Version 1.0 - August 17th, 2003
 * Modified by Victor Rouquette - January 2017

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
 */

/* 
 * File:   FCore.hpp
 * Author: guillem
 *
 * Created on 24 janvier 2017, 15:38
 */

#ifndef FCORE_HPP
#define FCORE_HPP

#define MAX_SIZE 200

#include <vector>

#include <thread>
#include <mutex>
#include <condition_variable>

#include "FQueue.hpp" //template
#include "FMessages.hpp" //template
#include "Core/FMap.hpp" //template
#include "FThread_guard.hpp"
#include "FOccurrence.hpp"
#include "FPattern.hpp"
#include "FContainer.hpp"

class FCore {
public:
    FCore( std::shared_ptr< FQueue< std::shared_ptr< FOccurrence > > > _pop_queue_parser_occurrences, 
           std::shared_ptr< FQueue< std::shared_ptr< std::pair<int,int> > > > _push_queue_parser_occurrences,
           std::shared_ptr< FQueue< std::shared_ptr< std::pair<int,int> > > > _pop_queue_renderer_occurrences,
           std::shared_ptr< FQueue< std::shared_ptr< FOccurrence > > > _push_queue_renderer_occurrences,
           std::shared_ptr< FQueue< std::shared_ptr< std::vector<patternStruct> > > > _pop_queue_parser_containers,
           std::shared_ptr< FQueue< std::shared_ptr< patternStruct > > > _push_queue_parser_containers,
           std::shared_ptr< FQueue< std::shared_ptr< patternStruct> > > _pop_queue_render_containers,
           std::shared_ptr< FQueue< std::shared_ptr< patternStruct> > > _push_queue_render_containers
           );
    
    FCore(const FCore& orig);
    
    virtual ~FCore();
    
    void thr_FCore();

    static std::vector<std::shared_ptr<FContainer> > view_containers(int a, int b);
    static std::shared_ptr<FPattern> view_patterns(int a);
    
    static FMap<int, FContainer > m_containers;
    static FMap<int, FPattern > m_patterns;

private:
    bool awake; //is in awake phase
    
    std::shared_ptr< FQueue< std::shared_ptr< FOccurrence > > > _m_pop_queue_parser_occurrences;
    std::shared_ptr< FQueue< std::shared_ptr< std::pair<int,int> > > > _m_push_queue_parser_occurrences;
    std::shared_ptr< FQueue< std::shared_ptr< std::pair<int,int> > > > _m_pop_queue_render_occurrences;
    std::shared_ptr< FQueue< std::shared_ptr< FOccurrence > > > _m_push_queue_render_occurrences;
    std::shared_ptr< FQueue< std::shared_ptr< std::vector<patternStruct> > > > _m_pop_queue_parser_containers;
    std::shared_ptr< FQueue< std::shared_ptr< patternStruct > > > _m_push_queue_parser_containers;
    std::shared_ptr< FQueue< std::shared_ptr< patternStruct> > > _m_pop_queue_render_containers;
    std::shared_ptr< FQueue< std::shared_ptr< patternStruct> > > _m_push_queue_render_containers;
    
    /*
     TODO
     */
    FMap< int, FMap< int,  FOccurrence > > m_occurrences;
    
    void thr_containers_manager();
    void thr_occurrences_manager();


    //check_memory ensure that the two map are not too big
    void check_memory();
};


#endif /* FCORE_HPP */
