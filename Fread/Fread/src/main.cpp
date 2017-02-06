//Generic Includes
#include <iostream>
#include <string>
#include <memory>
#include <thread>

//Includes for other tests
//#include "Parser/statesConfig.hpp"

//Includes for parser tests
//#include "Parser/parser.hpp"
//#include "FMessages_structure.hpp"

//Includes for graphics tests

#include <SFML/Graphics.hpp>
#include "Render/FBezierCurve.hpp"
#include "Render/container_render.hpp"
#include "Render/pattern_render.hpp"
#include "Render/FRender.hpp"

//Includes for queue tests
#include "FQueue.hpp"
#include <thread>
#include <memory>
#include <unistd.h>

//Includes for Core tests
#include "Core/FCore.hpp"
#include "Core/FMap.hpp"
#include "FOccurrence.hpp"
#include "FPattern.hpp"
#include "FContainer.hpp"
#include "FMessages.hpp"

using namespace std;

/*
 * Core main function test
 */
/*
void false_parser( std::shared_ptr< FQueue< std::shared_ptr< FMessages> > > _pop_queue_core, std::shared_ptr< FQueue< std::shared_ptr< FMessages> > > _push_queue_core);
void false_render( std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _pop_queue_core, std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _push_queue_core );

int main(){

    std::cout << "start" << std::endl;

    std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _queue_parser_core(new FQueue< std::shared_ptr<FMessages > >);
    std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _queue_core_parser(new FQueue< std::shared_ptr<FMessages > >) ;
    std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _queue_render_core(new FQueue< std::shared_ptr<FMessages > >) ;
    std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _queue_core_render(new FQueue< std::shared_ptr<FMessages > >) ;

    std::cout << "starting fcore" << std::endl;
    std::thread fcore_thr_( start_core, _queue_parser_core,    
                                        _queue_core_parser,
                                        _queue_render_core,
                                        _queue_core_render);

    std::cout << "starting false parser" << std::endl;
    std::thread false_parser_thr_(false_parser, _queue_core_parser, _queue_parser_core);
    FThread_guard lock2(false_parser_thr_);

	std::cout << "starting false render" << std::endl;
    std::thread false_render_thr_(false_render, _queue_core_render, _queue_render_core);
    FThread_guard lock3(false_render_thr_);

    return 0;
}

void false_parser( std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _pop_queue_core, std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _push_queue_core){
    
    std::cout << "in false parser " << std::endl;

    for(int i = 0; i < 10; ++i){
        FMessages pattern(PATTERN, std::shared_ptr<FPattern>(new FPattern(i)));
        _push_queue_core->push(std::make_shared<FMessages>(pattern));
    }


    for(int i = 0; i < 10; ++i){
        FMessages container(CONTAINER, std::shared_ptr<FContainer>(new FContainer(i)));
        _push_queue_core->push(std::make_shared<FMessages>(container));
    }

    while(1){
        std::shared_ptr<FMessages> msg = *(_pop_queue_core->wait_and_pop());
        if( msg.use_count() != 0 && msg != NULL){
        	if(msg->getHeader() == OCCURRENCE){
        		auto received = *( std::static_pointer_cast< std::pair<int, int> >(msg->getContent()) );
        		std::cout << "PARSER >>> OCCURRENCE RECEIVED FROM CORE n°" << received.first << ":" << received.second << std::endl;

        		FOccurrence occurrence(received.first, -(received.second) );
                std::shared_ptr<FOccurrence> occurrence_send = std::make_shared<FOccurrence>(occurrence);
                auto content_send = std::static_pointer_cast<void>( occurrence_send );
                FMessages msg_send(OCCURRENCE, content_send);
                std::cout << "PARSER >>> SEND " << -received.second << " TO CORE" << std::endl;
                _push_queue_core->push(std::make_shared<FMessages>(msg_send) );
                
        	}else if(msg->getHeader() == TIMESTAMP){
                auto received = std::static_pointer_cast< patternStruct >(msg->getContent()) ;
                std::cout << "PARSER >>> TIMESTAMPS RECEIVED FROM CORE on container : " << received->contId << ", from : " << received->tBegin << ", to : " << received->tEnd << std::endl;
                
                float length = received->tEnd - received->tBegin;
                float subdivision = length / 10.0f ;
                
                auto timestamps_send = std::make_shared< std::vector<patternStruct> >();
                float begin_time = received->tBegin;
                
                for(unsigned int i = 0; i < 10; ++i){
                    patternStruct to_insert( i, received->contId, begin_time, begin_time + subdivision );
                    timestamps_send->push_back(to_insert);
                    begin_time += subdivision;
                }
                auto content_send = std::static_pointer_cast<void>( timestamps_send );
                FMessages msg_send(TIMESTAMP, content_send);
                std::cout << "PARSER >>> SEND TIMESTAMPS ON CONTAINER : " << received->contId << " TO CORE" << std::endl;
                _push_queue_core->push(std::make_shared<FMessages>(msg_send) );

            }
        }
    }
}


*/

void false_render( std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _pop_queue_core, std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _push_queue_core ){
    std::cout << "in false render " << std::endl;


    FMessages init(INITDONE, NULL);
    FMessages start(START, NULL);

    _push_queue_core->push(std::make_shared<FMessages>(init));
    _push_queue_core->push(std::make_shared<FMessages>(start));
    
    int i = 0;
    int minId = 0;
    std::vector<int> to_render_patterns;
    

	std::this_thread::sleep_for (std::chrono::seconds(1));

    while(i < 10 && minId != -10){
        FMessages pattern(PATTERN, std::make_shared< int >(i) );
        std::cout << "RENDER >>> SEND PATTERN " << i << " TO CORE" << std::endl;
        _push_queue_core->push(std::make_shared<FMessages>(pattern));

        if(!_pop_queue_core->empty()){
            auto msg_core = *(_pop_queue_core->try_pop() );
            if(msg_core->getHeader() == PATTERN){
                auto received = std::static_pointer_cast< FPattern >(msg_core->getContent() ) ;
                std::cout << "RENDER >>> PATTERN RECEIVED FROM CORE n°" << received->getId() <<  std::endl;

                to_render_patterns.push_back(received->getId());
            }
        }
        
        std::cout << "RENDERING PATTERNS : " ;
        for(auto it = to_render_patterns.begin(); it != to_render_patterns.end(); ++it){
            std::cout << " " << *it ;
        }
        std::cout << std::endl;

        if(i < 10) ++i;

        std::this_thread::sleep_for (std::chrono::milliseconds(1));
    }

    while(!_pop_queue_core->empty()){
        auto msg_core = *(_pop_queue_core->try_pop() );
        if(msg_core->getHeader() == PATTERN){
            auto received = std::static_pointer_cast< FPattern >(msg_core->getContent() ) ;
            std::cout << "RENDER >>> PATTERN RECEIVED FROM CORE n°" << received->getId() <<  std::endl;

            to_render_patterns.push_back(received->getId());
        }
    }
        
    std::cout << "RENDERING PATTERNS : " ;
    for(auto it = to_render_patterns.begin(); it != to_render_patterns.end(); ++it){
        std::cout << " " << *it ;
    }
    std::cout << std::endl;

    i = 0;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "///////////////////////////" << std::endl;
    std::cout << "FIN DE L ENVOI DES PATTERNS" << std::endl;
    std::cout << "///////////////////////////" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    std::this_thread::sleep_for (std::chrono::milliseconds(1000));

    std::vector<int> to_render_occurrences0;
    std::vector<int> to_render_occurrences1;
    std::vector<int> to_render_occurrences2;

    while(i < 10 && minId != -10){
        FMessages occurrence0(OCCURRENCE, std::shared_ptr< std::pair<int,int> >(new std::pair<int, int>(0, i)));
        std::cout << "RENDER >>> SEND OCCURRENCE 0:" << i << " TO CORE" << std::endl;
    	_push_queue_core->push(std::make_shared<FMessages>(occurrence0));

        FMessages occurrence1(OCCURRENCE, std::shared_ptr< std::pair<int,int> >(new std::pair<int, int>(1, i)));
        std::cout << "RENDER >>> SEND OCCURRENCE 1:" << i << " TO CORE" << std::endl;
        _push_queue_core->push(std::make_shared<FMessages>(occurrence1));

        FMessages occurrence2(OCCURRENCE, std::shared_ptr< std::pair<int,int> >(new std::pair<int, int>(2, i)));
        std::cout << "RENDER >>> SEND OCCURRENCE 2:" << i << " TO CORE" << std::endl;
        _push_queue_core->push(std::make_shared<FMessages>(occurrence2));

    	if(!_pop_queue_core->empty()){
            auto msg_core = *(_pop_queue_core->try_pop() );
            if(msg_core->getHeader() == OCCURRENCE){
            	auto received = std::static_pointer_cast< FOccurrence >(msg_core->getContent() ) ;
            	std::cout << "RENDER >>> OCCURRENCE RECEIVED FROM CORE n°" << received->getPatternId() << ":" << received->getId() << std::endl;

                switch(received->getPatternId()){
                    case(0):
                        to_render_occurrences0.push_back(received->getId());
                    break;
                    case(1):
                        to_render_occurrences1.push_back(received->getId());
                    break;
                    case(2):
                        to_render_occurrences2.push_back(received->getId());
                    break;
                }
            }
    	}
        
        std::cout << "RENDERING OCCURRENCES 0: " ;
        for(auto it0 = to_render_occurrences0.begin(); it0 != to_render_occurrences0.end(); ++it0){
          	std::cout << " " << *it0 ;
        }
        std::cout << std::endl;

        std::cout << "RENDERING OCCURRENCES 1: " ;
        for(auto it1 = to_render_occurrences1.begin(); it1 != to_render_occurrences1.end(); ++it1){
            std::cout << " " << *it1 ;
        }
        std::cout << std::endl;

        std::cout << "RENDERING OCCURRENCES 2: " ;
        for(auto it2 = to_render_occurrences2.begin(); it2 != to_render_occurrences2.end(); ++it2){
            std::cout << " " << *it2 ;
        }
        std::cout << std::endl;

    	if(i < 10) ++i;

    	std::this_thread::sleep_for (std::chrono::milliseconds(1));
    }
    while(!_pop_queue_core->empty()){
        auto msg_core = *(_pop_queue_core->try_pop() );
        if(msg_core->getHeader() == OCCURRENCE){
            auto received = std::static_pointer_cast< FOccurrence >(msg_core->getContent() ) ;
            //std::cout << "RENDER >>> OCCURRENCE RECEIVED FROM CORE n°" << received->getPatternId() << ":" << received->getId() << std::endl;

            switch(received->getPatternId()){
                    case(0):
                        to_render_occurrences0.push_back(received->getId());
                    break;
                    case(1):
                        to_render_occurrences1.push_back(received->getId());
                    break;
                    case(2):
                        to_render_occurrences2.push_back(received->getId());
                    break;
                }
        }
        std::this_thread::sleep_for (std::chrono::milliseconds(1));
    }

    std::cout << "RENDERING OCCURRENCES 0: " ;
    for(auto it0 = to_render_occurrences0.begin(); it0 != to_render_occurrences0.end(); ++it0){
        std::cout << " " << *it0 ;
    }
    std::cout << std::endl;

    std::cout << "RENDERING OCCURRENCES 1: " ;
    for(auto it1 = to_render_occurrences1.begin(); it1 != to_render_occurrences1.end(); ++it1){
        std::cout << " " << *it1 ;
    }
    std::cout << std::endl;

    std::cout << "RENDERING OCCURRENCES 2: " ;
    for(auto it2 = to_render_occurrences2.begin(); it2 != to_render_occurrences2.end(); ++it2){
        std::cout << " " << *it2 ;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "//////////////////////////////////////////" << std::endl;
    std::cout << "FIN DE LA DEMANDE DE NOUVELLES OCCURRENCES" << std::endl;
    std::cout << "//////////////////////////////////////////" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::this_thread::sleep_for (std::chrono::milliseconds(1000));

    std::vector<int> to_render_old_occurrences0;

    i = 0;

    while(i < 10 && minId != -10){
        FMessages occurrence0(OCCURRENCE, std::shared_ptr< std::pair<int,int> >(new std::pair<int, int>(0, -i)));
        std::cout << "RENDER >>> SEND OLD OCCURRENCE 0:" << -i << " TO CORE" << std::endl;
        _push_queue_core->push(std::make_shared<FMessages>(occurrence0));

        if(!_pop_queue_core->empty()){
            auto msg_core = *(_pop_queue_core->try_pop() );
            if(msg_core->getHeader() == OCCURRENCE){
                auto received = std::static_pointer_cast< FOccurrence >(msg_core->getContent() ) ;
                std::cout << "RENDER >>> OLD OCCURRENCE RECEIVED FROM CORE n°" << received->getPatternId() << ":" << received->getId() << std::endl;

                to_render_old_occurrences0.push_back(received->getId());

            }
        }
        
        std::cout << "RENDERING OLD OCCURRENCES 0: " ;
        for(auto it0 = to_render_old_occurrences0.begin(); it0 != to_render_old_occurrences0.end(); ++it0){
            std::cout << " " << *it0 ;
        }
        std::cout << std::endl;

        if(i < 10) ++i;

        std::this_thread::sleep_for (std::chrono::milliseconds(1));
    }
    while(!_pop_queue_core->empty()){
        auto msg_core = *(_pop_queue_core->try_pop() );
        if(msg_core->getHeader() == OCCURRENCE){
            auto received = std::static_pointer_cast< FOccurrence >(msg_core->getContent() ) ;
            std::cout << "RENDER >>> OLD OCCURRENCE RECEIVED FROM CORE n°" << received->getPatternId() << ":" << received->getId() << std::endl;

            to_render_old_occurrences0.push_back(received->getId());

        }
        std::this_thread::sleep_for (std::chrono::milliseconds(1));
    }

    std::cout << "RENDERING OLD OCCURRENCES 0: " ;
    for(auto it0 = to_render_old_occurrences0.begin(); it0 != to_render_old_occurrences0.end(); ++it0){
        std::cout << " " << *it0 ;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "/////////////////////////////////////////" << std::endl;
    std::cout << "FIN DE LA DEMANDE D'ANCIENNES OCCURRENCES" << std::endl;
    std::cout << "/////////////////////////////////////////" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

std::this_thread::sleep_for (std::chrono::milliseconds(1000));

    i = 0;

    std::vector<float> to_render_timestamps0;
    std::vector<float> to_render_timestamps1;
    std::vector<float> to_render_timestamps2;

    FMessages timestamps0(TIMESTAMP, std::shared_ptr< patternStruct >(new patternStruct(-1, 0, 0.0f, 1.0f)));
    std::cout << "RENDER >>> SEND TIMESTAMPS  on container : 0, from : 0.0, to : 1.0" << std::endl;
    _push_queue_core->push(std::make_shared<FMessages>(timestamps0));

    FMessages timestamps1(TIMESTAMP, std::shared_ptr< patternStruct >(new patternStruct(-1, 1, 0.0f, 1.0f)));
    std::cout << "RENDER >>> SEND TIMESTAMPS  on container : 1, from : 0.0, to : 1.0" << std::endl;
    _push_queue_core->push(std::make_shared<FMessages>(timestamps1));

    FMessages timestamps2(TIMESTAMP, std::shared_ptr< patternStruct >(new patternStruct(-1, 2, 0.0f, 1.0f)));
    std::cout << "RENDER >>> SEND TIMESTAMPS  on container : 2, from : 0.0, to : 1.0" << std::endl;
    _push_queue_core->push(std::make_shared<FMessages>(timestamps2));

    while(i < 10 && minId != -10){


        if(!_pop_queue_core->empty()){
            auto msg_core = *(_pop_queue_core->try_pop() );
            if(msg_core->getHeader() == TIMESTAMP){
                auto received = std::static_pointer_cast< std::vector<patternStruct> >(msg_core->getContent() ) ;
                std::cout << "RENDER >>> TIMESTAMPS RECEIVED FROM CORE on container : " << received->begin()->contId << ", from : " << received->begin()->tBegin << ", to : " << (--received->end())->tEnd << std::endl;

                switch(received->begin()->contId){
                    case(0):
                        for(auto it = received->begin(); it != received->end(); ++it){
                            to_render_timestamps0.push_back(it->id);
                            to_render_timestamps0.push_back(it->tBegin);
                            to_render_timestamps0.push_back(it->tEnd);
                        }
                    break;
                    case(1):
                        for(auto it = received->begin(); it != received->end(); ++it){
                            to_render_timestamps1.push_back(it->id);
                            to_render_timestamps1.push_back(it->tBegin);
                            to_render_timestamps1.push_back(it->tEnd);
                        }
                    break;
                    case(2):
                        for(auto it = received->begin(); it != received->end(); ++it){
                            to_render_timestamps2.push_back(it->id);
                            to_render_timestamps2.push_back(it->tBegin);
                            to_render_timestamps2.push_back(it->tEnd);
                        }
                    break;

                }


            }
        }
        if(i < 10) ++i;

        std::this_thread::sleep_for (std::chrono::milliseconds(1));
    }
    while(!_pop_queue_core->empty()){
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
        if(!_pop_queue_core->empty()){
            auto msg_core = *(_pop_queue_core->try_pop() );
            if(msg_core->getHeader() == TIMESTAMP){
                auto received = std::static_pointer_cast< std::vector<patternStruct> >(msg_core->getContent() ) ;
                std::cout << "RENDER >>> TIMESTAMPS RECEIVED FROM CORE on container : " << received->begin()->contId << ", from : " << received->begin()->tBegin << ", to : " << (--received->end())->tEnd << std::endl;

                switch(received->begin()->contId){
                    case(0):
                        for(auto it = received->begin(); it != received->end(); ++it){
                            to_render_timestamps0.push_back(it->id);
                            to_render_timestamps0.push_back(it->tBegin);
                            to_render_timestamps0.push_back(it->tEnd);
                        }
                    break;
                    case(1):
                        for(auto it = received->begin(); it != received->end(); ++it){
                            to_render_timestamps1.push_back(it->id);
                            to_render_timestamps1.push_back(it->tBegin);
                            to_render_timestamps1.push_back(it->tEnd);
                        }
                    break;
                    case(2):
                        for(auto it = received->begin(); it != received->end(); ++it){
                            to_render_timestamps2.push_back(it->id);
                            to_render_timestamps2.push_back(it->tBegin);
                            to_render_timestamps2.push_back(it->tEnd);
                        }
                    break;

                }


            }
        }

    std::cout << "RENDERING TIMESTAMPS 0: " ;
    for(auto it0 = to_render_timestamps0.begin(); it0 != to_render_timestamps0.end(); ++it0){
        std::cout << " " << *it0 ;
    }
    std::cout << std::endl;

    std::cout << "RENDERING TIMESTAMPS 1: " ;
    for(auto it1 = to_render_timestamps1.begin(); it1 != to_render_timestamps1.end(); ++it1){
        std::cout << " " << *it1 ;
    }
    std::cout << std::endl;

    std::cout << "RENDERING TIMESTAMPS 2: " ;
    for(auto it2 = to_render_timestamps2.begin(); it2 != to_render_timestamps2.end(); ++it2){
        std::cout << " " << *it2 ;
    }

        
    }

    std::cout << "RENDERING TIMESTAMPS 0: " ;
    for(auto it0 = to_render_timestamps0.begin(); it0 != to_render_timestamps0.end(); ++it0){
        std::cout << " " << *it0 ;
    }
    std::cout << std::endl;

    std::cout << "RENDERING TIMESTAMPS 1: " ;
    for(auto it1 = to_render_timestamps1.begin(); it1 != to_render_timestamps1.end(); ++it1){
        std::cout << " " << *it1 ;
    }
    std::cout << std::endl;

    std::cout << "RENDERING TIMESTAMPS 2: " ;
    for(auto it2 = to_render_timestamps2.begin(); it2 != to_render_timestamps2.end(); ++it2){
        std::cout << " " << *it2 ;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "//////////////////////////////////////////" << std::endl;
    std::cout << "FIN DE LA DEMANDE DE NOUVEAUX TIMESTAMPS" << std::endl;
    std::cout << "//////////////////////////////////////////" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::this_thread::sleep_for (std::chrono::milliseconds(1000));

    i = 0;

    std::vector<float> to_render_old_timestamps0;
    std::vector<float> to_render_old_timestamps1;
    std::vector<float> to_render_old_timestamps2;

    FMessages old_timestamps0(TIMESTAMP, std::shared_ptr< patternStruct >(new patternStruct(-1, 0, 0.0f, 1.0f)));
    std::cout << "RENDER >>> SEND TIMESTAMPS  on container : 0, from : 0.0, to : 1.0" << std::endl;
    _push_queue_core->push(std::make_shared<FMessages>(old_timestamps0));
/*
    FMessages old_timestamps1(TIMESTAMP, std::shared_ptr< patternStruct >(new patternStruct(-1, 1, 0.0f, 1.0f)));
    std::cout << "RENDER >>> SEND TIMESTAMPS  on container : 1, from : 0.0, to : 1.0" << std::endl;
    _push_queue_core->push(std::make_shared<FMessages>(old_timestamps1));

    FMessages old_timestamps2(TIMESTAMP, std::shared_ptr< patternStruct >(new patternStruct(-1, 2, 0.0f, 1.0f)));
    std::cout << "RENDER >>> SEND TIMESTAMPS  on container : 2, from : 0.0, to : 1.0" << std::endl;
    _push_queue_core->push(std::make_shared<FMessages>(old_timestamps2));
*/
    while(i < 10 && minId != -10){


        if(!_pop_queue_core->empty()){
            auto msg_core = *(_pop_queue_core->try_pop() );
            if(msg_core->getHeader() == TIMESTAMP){
                auto received = std::static_pointer_cast< std::vector<patternStruct> >(msg_core->getContent() ) ;
                std::cout << "RENDER >>> TIMESTAMPS RECEIVED FROM CORE on container : " << received->begin()->contId << ", from : " << received->begin()->tBegin << ", to : " << (--received->end())->tEnd << std::endl;

                switch(received->begin()->contId){
                    case(0):
                        for(auto it = received->begin(); it != received->end(); ++it){
                            to_render_old_timestamps0.push_back(it->id);
                            to_render_old_timestamps0.push_back(it->tBegin);
                            to_render_old_timestamps0.push_back(it->tEnd);
                        }
                    break;
                    case(1):
                        for(auto it = received->begin(); it != received->end(); ++it){
                            to_render_old_timestamps1.push_back(it->id);
                            to_render_old_timestamps1.push_back(it->tBegin);
                            to_render_old_timestamps1.push_back(it->tEnd);
                        }
                    break;
                    case(2):
                        for(auto it = received->begin(); it != received->end(); ++it){
                            to_render_old_timestamps2.push_back(it->id);
                            to_render_old_timestamps2.push_back(it->tBegin);
                            to_render_old_timestamps2.push_back(it->tEnd);
                        }
                    break;

                }


            }
        }

        if(i < 10) ++i;

        std::this_thread::sleep_for (std::chrono::milliseconds(1));
    }
    while(!_pop_queue_core->empty()){
        if(!_pop_queue_core->empty()){
            auto msg_core = *(_pop_queue_core->try_pop() );
            if(msg_core->getHeader() == TIMESTAMP){
                auto received = std::static_pointer_cast< std::vector<patternStruct> >(msg_core->getContent() ) ;
                std::cout << "RENDER >>> TIMESTAMPS RECEIVED FROM CORE on container : " << received->begin()->contId << ", from : " << received->begin()->tBegin << ", to : " << (--received->end())->tEnd << std::endl;

                switch(received->begin()->contId){
                    case(0):
                        for(auto it = received->begin(); it != received->end(); ++it){
                            to_render_old_timestamps0.push_back(it->id);
                            to_render_old_timestamps0.push_back(it->tBegin);
                            to_render_old_timestamps0.push_back(it->tEnd);
                        }
                    break;
                    case(1):
                        for(auto it = received->begin(); it != received->end(); ++it){
                            to_render_old_timestamps1.push_back(it->id);
                            to_render_old_timestamps1.push_back(it->tBegin);
                            to_render_old_timestamps1.push_back(it->tEnd);
                        }
                    break;
                    case(2):
                        for(auto it = received->begin(); it != received->end(); ++it){
                            to_render_old_timestamps2.push_back(it->id);
                            to_render_old_timestamps2.push_back(it->tBegin);
                            to_render_old_timestamps2.push_back(it->tEnd);
                        }
                    break;

                }


            }
        }

        std::this_thread::sleep_for (std::chrono::milliseconds(10));
    }

    std::cout << "RENDERING TIMESTAMPS 0: " ;
    for(auto it0 = to_render_old_timestamps0.begin(); it0 != to_render_old_timestamps0.end(); ++it0){
        std::cout << " " << *it0 ;
    }
    std::cout << std::endl;
/*
    std::cout << "RENDERING TIMESTAMPS 1: " ;
    for(auto it1 = to_render_old_timestamps1.begin(); it1 != to_render_old_timestamps1.end(); ++it1){
        std::cout << " " << *it1 ;
    }
    std::cout << std::endl;

    std::cout << "RENDERING TIMESTAMPS 2: " ;
    for(auto it2 = to_render_old_timestamps2.begin(); it2 != to_render_old_timestamps2.end(); ++it2){
        std::cout << " " << *it2 ;
    }
    */
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "//////////////////////////////////////" << std::endl;
    std::cout << "FIN DE LA DEMANDE D'ANCIENS TIMESTAMPS" << std::endl;
    std::cout << "//////////////////////////////////////" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::this_thread::sleep_for (std::chrono::milliseconds(1000));

}


/*
 * Parser main function test
 */
 /* int main(int argc, char* argv[])
{
    if(argc != 2){
        std::cout << "invalid format\n valid format : Fread trace_path" << std::endl;
        return -1;
    }
    
    std::string path = argv[1];
            
    if(path.substr(path.size()-6, 6) != ".trace"){
        std::cout << "invalid trace format, need *.trace" << std::endl;
        return -1;
    }
    
    auto coreToParserQueue = make_shared<FQueue<msg_coreToParser>>();
    auto parserToCoreQueue = make_shared<FQueue<msg_parserToCore>>();
    
    thread parserThread(parser_thread, path, coreToParserQueue, parserToCoreQueue);
    
    sleep(2);
    msg_coreToParser msg;
    msg.header = H_START;
    msg.content = make_shared<string>("Start");
    coreToParserQueue->push(msg);
    shared_ptr<msg_parserToCore> str_msg = parserToCoreQueue->wait_and_pop();
    cout << *(str_msg->content) << endl;
    
    parserThread.join();
    
    return 0;
} */

/*
 * Render main function test
 */

 int main(void)
{
 sf::ContextSettings settings;
 settings.antialiasingLevel = 8;
 settings.minorVersion =0;
  settings.majorVersion =4;
sf::RenderWindow window(sf::VideoMode(1500,800), "Container and occurrences test",sf::Style::Default, settings);

int sizeX =window.getSize().x;
int sizeY =window.getSize().y;

    FBezierCurve bezierCurve1(sf::Vector2f(50,50), sf::Vector2f(350,350), 20, 2.f, sf::Color::Cyan);
    FBezierCurve bezierCurve2(sf::Vector2f(100,100), sf::Vector2f(300,300), 20, 2.f, sf::Color::Magenta);

    bezierCurve1.calculate();
    bezierCurve2.calculate();
    
    //timeStamps test vectors implementation
    std::vector<float> timeStamps1;
    timeStamps1.push_back(0.1124f);
    timeStamps1.push_back(0.1321f);
    timeStamps1.push_back(0.1321f);
    timeStamps1.push_back(0.1398f);

    std::vector<float> timeStamps2;
    timeStamps2.push_back(0.0924f);
    timeStamps2.push_back(0.1021f);
    timeStamps2.push_back(0.1521f);
    timeStamps2.push_back(0.1598f);
    
    std::vector<float> timeStamps3;
    timeStamps3.push_back(0.1024f);
    timeStamps3.push_back(0.1090f);
    timeStamps3.push_back(0.1090f);
    timeStamps3.push_back(0.1108f);
    timeStamps3.push_back(0.1108f);
    timeStamps3.push_back(0.1122f);
    timeStamps3.push_back(0.1122f);
    timeStamps3.push_back(0.1187f);
    
    //eventType vectors implementation
    std::vector<eventType> eventType1;
    eventType1.push_back(WAIT);
    eventType1.push_back(COMPUTE);
    
    std::vector<eventType> eventType2;
    eventType2.push_back(SEND);
    eventType2.push_back(WAIT);
    
    std::vector<eventType> eventType3;
    eventType3.push_back(COMPUTE);
    eventType3.push_back(WAIT);
    eventType3.push_back(COMPUTE);
    eventType3.push_back(SEND);

    //definition of the scalling we want
    scale scale1(0.1847, 3, (sizeX - 100), 100, 50,(sizeY*3)/100, sizeY/100, (sizeY*45)/100);
    
    //definition of a container_render vector
    std::vector<container_render> containers;
    
    container_render container1(1,"coucou",scale1.getContainerSize(), scale1.getContainerOffsetX(), scale1.getContainerOffsetY(), scale1.getWindowContainerOffsetY());
    container_render container2(2,"ça va ?", scale1.getContainerSize(), scale1.getContainerOffsetX(), scale1.getContainerOffsetY(), scale1.getWindowContainerOffsetY());
    container_render container3(3,"Oui et toi ?", scale1.getContainerSize(), scale1.getContainerOffsetX(), scale1.getContainerOffsetY(), scale1.getWindowContainerOffsetY());
    
    occurrence_render occurrence1(1, container1.getId(), scale1.getContainerOffsetY(), scale1.getContainerOffsetX(), scale1.getEventOffsetY(),scale1.getWindowContainerOffsetY(), scale1.getScale(), timeStamps1, eventType1);
    occurrence_render occurrence2(2, container2.getId(), scale1.getContainerOffsetY(), scale1.getContainerOffsetX(), scale1.getEventOffsetY(),scale1.getWindowContainerOffsetY(), scale1.getScale(), timeStamps2, eventType2);
    occurrence_render occurrence3(3, container3.getId(), scale1.getContainerOffsetY(), scale1.getContainerOffsetX(), scale1.getEventOffsetY(),scale1.getWindowContainerOffsetY(), scale1.getScale(), timeStamps3, eventType3);

    container1.addOccurrence(occurrence1);
    container2.addOccurrence(occurrence2);
    container3.addOccurrence(occurrence3);
    
    containers.push_back(container1);
    containers.push_back(container2);
    containers.push_back(container3);
    std::vector<pattern_render> lp;
    pattern_render pattern(1, timeStamps3, occurrence3);
    lp.push_back(pattern);
 //  pattern.SetPosition(200, 200,100.0);
    pattern_render pattern2(2, timeStamps2, occurrence2);
       lp.push_back(pattern2);
  // pattern2.SetPosition(410, 200,100.0);
       FMessages init(INITDONE, NULL);
    FMessages start(START, NULL);
std::shared_ptr< FQueue< std::shared_ptr<FMessages> > > _pop_queue_core;
std::shared_ptr< FQueue< std::shared_ptr<FMessages> > > _push_queue_core;
 //   _push_queue_core->push(std::make_shared<FMessages>(init));
           FRender render(_pop_queue_core,_push_queue_core,0.7);
           sf::RectangleShape barre(sf::Vector2f(1000, 10));
           barre.setPosition(100,sizeY-20);
           barre.setFillColor(sf::Color(131,131,131));
            sf::RectangleShape barre2(sf::Vector2f(100, 10));
           barre2.setPosition(100,sizeY-20);
           barre2.setFillColor(sf::Color(200,200,200));
           int startclic =0 ;
           bool clic=false;
    while (window.isOpen())
    {
        int spacing =100;
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::Resized)
                    {
                        std::cout << "new width: " << event.size.width << std::endl;
                        std::cout << "new height: " << event.size.height << std::endl;
                        
                        sizeX =window.getSize().x;
                        sizeY =window.getSize().y;
                        
                        scale1.updateScale((sizeX - spacing),spacing,scale1.getContainerOffsetX(),(sizeY*3)/100,sizeY/100,(sizeY*45)/100,3);
                        
                        container1.updatePosition(scale1.getContainerSize(),scale1.getContainerOffsetX(),scale1.getContainerOffsetY(),scale1.getWindowContainerOffsetY());
                        container2.updatePosition(scale1.getContainerSize(),scale1.getContainerOffsetX(),scale1.getContainerOffsetY(),scale1.getWindowContainerOffsetY());                       
                        container3.updatePosition(scale1.getContainerSize(),scale1.getContainerOffsetX(),scale1.getContainerOffsetY(),scale1.getWindowContainerOffsetY());
                        
                        occurrence1.updatePosition(scale1.getScale(),scale1.getContainerOffsetY(),scale1.getContainerOffsetX(),scale1.getEventOffsetY());
                        occurrence2.updatePosition(scale1.getScale(),scale1.getContainerOffsetY(),scale1.getContainerOffsetX(),scale1.getEventOffsetY());
                        occurrence3.updatePosition(scale1.getScale(),scale1.getContainerOffsetY(),scale1.getContainerOffsetX(),scale1.getEventOffsetY());
                        
                    }
               if (event.type == sf::Event::MouseButtonPressed)
                    {
                if (event.mouseButton.button == sf::Mouse::Left)
                     {
        
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                  if (barre2.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y))
                  {
                    std::cout << "the barre2 button was pressed" << std::endl;
                    clic =true;
                    startclic=(event.mouseButton.x-barre2.getPosition().x);
                  }
                  else if (clic)  { barre2.setPosition(event.mouseMove.x-barre2.getPosition().x,sizeY-20); }
                  else if (barre.getGlobalBounds().contains(event.mouseButton.x,event.mouseButton.y)){
                    std::cout << "the barre button was pressed" << std::endl;
                    }
                    
                }
            }  
                    
                
                
            }
            
            window.clear(sf::Color(255,255,255));
            scale1.draw(window);
            for (unsigned int i =0; i < containers.size(); i++)
            {
                window.draw(containers[i]); 
            }
            window.draw(barre);
             window.draw(barre2);
            render.drawPatterns(lp,sizeX,sizeY,window);
            //pattern.draw(window);
           // window.draw(pattern2);
            window.display();
    }
    
    return 0;
 
}

/*
 * FQueue main function test
 */

/*void push_thread(FQueue<string>* Fqueue) {
    for(int i=0; i<5; i++){
        string msg = "msg " + to_string(i);
        Fqueue->push(msg);
        cout << msg << " just pushed" << endl;
    }
    sleep(5);
    for(int i=5; i<10; i++){
        string msg = "msg " + to_string(i);
        Fqueue->push(msg);
        cout << msg << " just pushed" << endl;
        sleep(1);
    }
    string endMsg = "End";
    Fqueue->push(endMsg);
    cout << endMsg << " just pushed" << endl;
}

void pop_thread(FQueue<string>* Fqueue) {
    sleep(3);
    while(1) {
        shared_ptr<string> string_ptr(Fqueue->wait_and_pop());
        cout << *(string_ptr.get()) << " found" << endl;
        if(*(string_ptr.get()) == "End"){
            break;
        }
    }
}

int main(void){
    
    FQueue<string> testFQueue;
    cout << "Fqueue has been created" << endl;
    
    thread pusher(push_thread, &testFQueue);
    thread poper(pop_thread, &testFQueue);
    
    pusher.join();
    poper.join();
}*/
