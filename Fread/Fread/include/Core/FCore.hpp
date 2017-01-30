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
#include "FMap.hpp" //template
#include "FThread_guard.hpp"
#include "FObjet.hpp"
#include "FOccurrence.hpp"
#include "FPattern.hpp"
#include "FContainer.hpp"

class FCore {
public:
    FCore( std::shared_ptr< FQueue< FMessages< FObjet > > > _pop_queue_parser, 
           std::shared_ptr< FQueue< FMessages< FObjet > > > _push_queue_parser,
           std::shared_ptr< FQueue< FMessages< FObjet > > > _pop_queue_renderer,
           std::shared_ptr< FQueue< FMessages< FObjet > > > _push_queue_renderer
           );
    
    FCore(const FCore& orig);
    
    virtual ~FCore();
    
    void thr_FCore();
    
private:
    bool awake; //is in awake phase
    
    std::shared_ptr<FQueue< FMessages< FObjet > > > _m_pop_queue_parser;
    std::shared_ptr<FQueue< FMessages< FObjet > > > _m_push_queue_parser;
    std::shared_ptr<FQueue< FMessages< FObjet > > > _m_pop_queue_renderer;
    std::shared_ptr<FQueue< FMessages< FObjet > > > _m_push_queue_renderer;
     
    /*
     TODO
     */
    FQueue< FMessages< FOccurrence > > m_renderer_occurrences;
    FQueue< FMessages< FContainer > > m_renderer_container;
    FQueue< FMessages< FOccurrence > > m_occurrences_renderer;
    FQueue< FMessages< FContainer > > m_container_renderer;
    
    FQueue< FMessages< FOccurrence > > m_parser_occurrences;
    FQueue< FMessages< FContainer > > m_parser_container;
    FQueue< FMessages< FOccurrence > > m_occurrences_parser;
    FQueue< FMessages< FContainer > > m_container_parser;
    
    /*
     TODO
     */
    FMap< std::pair<int, int>, FOccurrence > m_occurrences;
    FMap<int, FContainer > m_container;
    FMap<int, FPattern > m_patterns;
    
    void thr_container_manager();
    void thr_occurrences_manager();
    
    void thr_message_handler_parser();
    void thr_message_handler_renderer();

	std::mutex message_parser_mutex;
	std::condition_variable message_parser_cond;

	std::mutex message_renderer_mutex;
	std::condition_variable message_renderer_cond;

	std::mutex containers_manager_mutex;
	std::condition_variable containers_manager_cond;

	std::mutex occurrences_manager_mutex;
	std::condition_variable occurrences_manager_cond;


    //check_memory ensure that the two map are not too big
    void check_memory();
};


#endif /* FCORE_HPP */
