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
#include "FMessages.hpp" 
#include "Core/FMap.hpp" //template
#include "FThread_guard.hpp"
#include "FOccurrence.hpp"
#include "FPattern.hpp"
#include "FContainer.hpp"

class FCore {
public:
    FCore();

    FCore( std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _pop_queue_parser, 
           std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _push_queue_parser,
           std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _pop_queue_render,
           std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _push_queue_render
           );
    
    FCore(const FCore& orig);
    
    virtual ~FCore();

    void thr_FCore();

    //static std::vector<std::shared_ptr<FContainer> > view_containers(int a, int b);
    static std::shared_ptr<FPattern> view_patterns(int a);


private:   
    std::shared_ptr< FQueue< std::shared_ptr<FMessages> > > _m_pop_queue_parser;
    std::shared_ptr< FQueue< std::shared_ptr<FMessages> > > _m_push_queue_parser;
    std::shared_ptr< FQueue< std::shared_ptr<FMessages> > > _m_pop_queue_render;
    std::shared_ptr< FQueue< std::shared_ptr<FMessages> > > _m_push_queue_render;

    FQueue< std::shared_ptr< FMessages > > m_parser_occurrences;
    FQueue< std::shared_ptr< FMessages > > m_parser_timestamps;
    FQueue< std::shared_ptr< FMessages > > m_render_occurrences;
    FQueue< std::shared_ptr< FMessages > > m_render_timestamps;

    FMap< int, FPattern > m_patterns;
    FMap< int, FContainer > m_containers;
    FMap< int, std::vector< std::shared_ptr<FOccurrence > > > m_occurrences;

    bool initdone; //after initdone
    
    std::vector<int> get_containers_id();
    std::vector<int> get_patterns_id();

    void thr_timestamps_manager();
    void thr_occurrences_manager();

    void thr_messages_handler_parser();
    void thr_messages_handler_render();

    float get_container_content(int id, float t1);
    bool is_container_full(int id, float t1, float t2);

    //check_memory ensure that the two map are not too big
    void thr_check_memory();

    bool contains_occurrence(int idPattern, int idOccurrence);
    std::shared_ptr<FOccurrence> find_occurrence(int idPattern, int idOccurrence);

    patternStruct get_first_pattern(int contId, float beginTime);
    patternStruct get_next_pattern( patternStruct current_pattern );

    void get_total_time();

    void occurrences_from_parser();
    void occurrences_from_render();

    void timestamps_from_parser();
    void timestamps_from_render();
};

//function start that will launch the threads
void core_thread( std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _pop_queue_parser, 
                 std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _push_queue_parser,
                 std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _pop_queue_render,
                 std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _push_queue_render
                );

#endif /* FCORE_HPP */