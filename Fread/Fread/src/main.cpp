//Generic Includes
#include <iostream>
#include <string>

//Includes for parser tests
#include "Parser/PAJE/paje_interface.hpp"

//Includes for graphics tests
#include <SFML/Graphics.hpp>
#include "Render/FBezierCurve.hpp"
#include "Render/container_render.hpp"

//Includes for queue tests
#include "queue.hpp"
#include <thread>
#include <memory>
#include <unistd.h>

using namespace std;

/*
 * Parser main function test
 */
/*int main(int argc, char* argv[])
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
    
    paje::awake(path);
    paje::start();
    
    return 0;
}*/

/*
 * Render main function test
 */
int main(void)
{

    sf::RenderWindow window(sf::VideoMode(1500, 1000), "Container and occurrences test");

    /* FBezierCurve bezierCurve1(sf::Vector2f(50,50), sf::Vector2f(350,350), 20, sf::Color::Cyan);
    FBezierCurve bezierCurve2(sf::Vector2f(100,100), sf::Vector2f(300,300), 20, sf::Color::Magenta);

    bezierCurve1.calculate();
    bezierCurve2.calculate();
    */
    
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
    scale scale1(0.1847, 900);
    
    container_render container1(1,"coucou",scale1.getContainerSize());
    container_render container2(2,"ça va ?", scale1.getContainerSize());
    container_render container3(3,"Oui et toi ?", scale1.getContainerSize());

    occurrence_render occurrence1(1, container1.getId(), container1.getOffsetY(), scale1.getScale(), timeStamps1, eventType1);
    occurrence_render occurrence2(2, container2.getId(), container2.getOffsetY(), scale1.getScale(), timeStamps2, eventType2);
    occurrence_render occurrence3(3, container3.getId(), container3.getOffsetY(), scale1.getScale(), timeStamps3, eventType3);

    container1.addOccurrence(occurrence1);
    container2.addOccurrence(occurrence2);
    container3.addOccurrence(occurrence3);

    while (window.isOpen())
    {
            sf::Event event;
            while (window.pollEvent(event))
            {
                    if (event.type == sf::Event::Closed)
                            window.close();
            }
            window.clear(sf::Color(255,255,255));
            window.draw(container1);
            window.draw(container2);
            window.draw(container3);
        //    window.draw(bezierCurve1);
        //    window.draw(bezierCurve2);
            window.display();
    }
    
    return 0;
}

/*
 * Queue main function test
 */

/* void push_thread(Queue<string>* queue) {
    for(int i=0; i<5; i++){
        string msg = "msg " + to_string(i);
        queue->push(msg);
        cout << msg << " just pushed" << endl;
    }
    sleep(5);
    for(int i=5; i<10; i++){
        string msg = "msg " + to_string(i);
        queue->push(msg);
        cout << msg << " just pushed" << endl;
        sleep(1);
    }
    string endMsg = "End";
    queue->push(endMsg);
    cout << endMsg << " just pushed" << endl;
}

void pop_thread(Queue<string>* queue) {
    sleep(3);
    while(1) {
        shared_ptr<string> string_ptr(queue->wait_and_pop());
        cout << *(string_ptr.get()) << " found" << endl;
        if(*(string_ptr.get()) == "End"){
            break;
        }
    }
}

int main(void){
    
    Queue<string> testQueue;
    cout << "queue has been created" << endl;
    
    thread pusher(push_thread, &testQueue);
    thread poper(pop_thread, &testQueue);
    
    pusher.join();
    poper.join();
} */