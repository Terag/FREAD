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

void false_parser( std::shared_ptr< FQueue< std::shared_ptr< FMessages> > > _pop_queue_core, std::shared_ptr< FQueue< std::shared_ptr< FMessages> > > _push_queue_core);
void false_render( std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _pop_queue_core, std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _push_queue_core );

int main(){

    std::cout << "start" << std::endl;

    std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _queue_parser_core(new FQueue< std::shared_ptr<FMessages > >);
    std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _queue_core_parser(new FQueue< std::shared_ptr<FMessages > >) ;
    std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _queue_render_core(new FQueue< std::shared_ptr<FMessages > >) ;
    std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _queue_core_render(new FQueue< std::shared_ptr<FMessages > >) ;

    std::cout << "creating fcore" << std::endl;

    FCore fcore(_queue_parser_core,    
                _queue_core_parser,
                _queue_render_core,
                _queue_core_render
                );

    std::cout << "starting fcore" << std::endl;
    fcore.start();

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


    FMessages init(INITDONE, NULL);
    FMessages start(START, NULL);

    _push_queue_core->push(std::make_shared<FMessages>(init));
    _push_queue_core->push(std::make_shared<FMessages>(start));

    for(int i = 0; i < 5; ++i){
        FMessages pattern(PATTERN, std::shared_ptr<FPattern>(new FPattern(i)));
        _push_queue_core->push(std::make_shared<FMessages>(pattern));
    }


    for(int i = 0; i < 5; ++i){
        FMessages container(CONTAINER, std::shared_ptr<FContainer>(new FContainer(i)));
        _push_queue_core->push(std::make_shared<FMessages>(container));
    }

    while(1){
        std::shared_ptr<FMessages> msg = *(_pop_queue_core->wait_and_pop());
        if( msg.use_count() != 0 && msg != NULL){
        	if(msg->getHeader() == OCCURRENCE){
        		auto received = *( std::static_pointer_cast< std::pair<int, int> >(msg->getContent()) );
        		std::cout << "PARSER OCCURRENCE RECEIVED FROM CORE n°" << received.first << ":" << received.second << std::endl;

        		FOccurrence occurrence(received.first, -(received.second) );
                std::shared_ptr<FOccurrence> occurrence_send = std::make_shared<FOccurrence>(occurrence);
                auto content_send = std::static_pointer_cast<void>( occurrence_send );
                FMessages msg_send(OCCURRENCE, content_send);
                _push_queue_core->push(std::make_shared<FMessages>(msg_send) );
                std::cout << "PARSER SEND " << -received.second << " TO CORE" << std::endl;
        	}
        }
    }

}

void false_render( std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _pop_queue_core, std::shared_ptr< FQueue< std::shared_ptr< FMessages > > > _push_queue_core ){
    std::cout << "in false render " << std::endl;


    FMessages init(INITDONE, NULL);
    FMessages start(START, NULL);

    _push_queue_core->push(std::make_shared<FMessages>(init));
    _push_queue_core->push(std::make_shared<FMessages>(start));

    FMessages pattern(PATTERN, std::shared_ptr<FPattern>(new FPattern(0)));
    _push_queue_core->push(std::make_shared<FMessages>(pattern));

    FMessages container(CONTAINER, std::shared_ptr<FContainer>(new FContainer(0)));
    _push_queue_core->push(std::make_shared<FMessages>(container));
    
    int i = 0;
    int minId = 0;
    std::vector<int> to_render;

	std::this_thread::sleep_for (std::chrono::seconds(3));

    while(i < 50 && minId != -50){
        FMessages occurrence(OCCURRENCE, std::shared_ptr< std::pair<int,int> >(new std::pair<int, int>(0, i)));
        std::cout << "RENDER SEND " << -i << " TO CORE" << std::endl;
    	_push_queue_core->push(std::make_shared<FMessages>(occurrence));

    	if(!_pop_queue_core->empty()){
            auto msg_core = *(_pop_queue_core->try_pop() );
            if(msg_core->getHeader() == OCCURRENCE){
            	auto received = std::static_pointer_cast< FOccurrence >(msg_core->getContent() ) ;
            	std::cout << "RENDER OCCURRENCE RECEIVED FROM CORE n°" << received->getPatternId() << ":" << received->getId() << std::endl;

            	to_render.push_back(received->getId());
            	if(received->getId() < minId) minId = received->getId();
            }
    	}
        
        for(auto it = to_render.begin(); it != to_render.end(); ++it){
          	std::cout << *it << std::endl;
        }

		std::cout << i << std::endl;

    	if(i < 50) ++i;

    	std::this_thread::sleep_for (std::chrono::milliseconds(100));
    }

}


/*
 * Parser main function test
 */
/*
int main(int argc, char* argv[])
>>>>>>> core
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
<<<<<<< HEAD
} 

=======
}
*/
/*
 * Render main function test
 */
/* int main(void)
{
 sf::ContextSettings settings;
 settings.antialiasingLevel = 8;

 int sizeX = 1500;
 int sizeY = 1000;
 
    sf::RenderWindow window(sf::VideoMode(sizeX, sizeY), "Container and occurrences test",sf::Style::Default, settings);

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
    scale scale1(0.1847, 3, (sizeX - 100), 100, 50, 30, 8, (sizeY*45)/100);
    
    container_render container1(1,"coucou",scale1.getContainerSize(), scale1.getContainerOffsetX(), scale1.getContainerOffsetY(), scale1.getWindowContainerOffsetY());
    container_render container2(2,"ça va ?", scale1.getContainerSize(), scale1.getContainerOffsetX(), scale1.getContainerOffsetY(), scale1.getWindowContainerOffsetY());
    container_render container3(3,"Oui et toi ?", scale1.getContainerSize(), scale1.getContainerOffsetX(), scale1.getContainerOffsetY(), scale1.getWindowContainerOffsetY());

    occurrence_render occurrence1(1, container1.getId(), scale1.getContainerOffsetY(), scale1.getContainerOffsetX(), scale1.getEventOffsetY(),scale1.getWindowContainerOffsetY(), scale1.getScale(), timeStamps1, eventType1);
    occurrence_render occurrence2(2, container2.getId(), scale1.getContainerOffsetY(), scale1.getContainerOffsetX(), scale1.getEventOffsetY(),scale1.getWindowContainerOffsetY(), scale1.getScale(), timeStamps2, eventType2);
    occurrence_render occurrence3(3, container3.getId(), scale1.getContainerOffsetY(), scale1.getContainerOffsetX(), scale1.getEventOffsetY(),scale1.getWindowContainerOffsetY(), scale1.getScale(), timeStamps3, eventType3);

    container1.addOccurrence(occurrence1);
    container2.addOccurrence(occurrence2);
    container3.addOccurrence(occurrence3);

    pattern_render pattern(1,timeStamps3,occurrence3);

    while (window.isOpen())
    {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear(sf::Color(255,255,255));
            scale1.draw(window);
            window.draw(container1);
            window.draw(container2);
            window.draw(container3);
           pattern.draw(window);
            window.display();
    }
    
    return 0;
}*/

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
