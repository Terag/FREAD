//Generic Includes
#include <iostream>
#include <string>

//Includes for parser tests
#include "Parser/PAJE/paje_interface.hpp"

//Includes for graphics tests
#include <SFML/Graphics.hpp>
#include "Render/FBezierCurve.hpp"

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

    sf::RenderWindow window(sf::VideoMode(500, 500), "BezierCurve test");

    FBezierCurve bezierCurve1(sf::Vector2f(50,50), sf::Vector2f(350,350), 20, sf::Color::Cyan);
    FBezierCurve bezierCurve2(sf::Vector2f(100,100), sf::Vector2f(300,300), 20, sf::Color::Magenta);

    bezierCurve1.calculate();
    bezierCurve2.calculate();
    
    while (window.isOpen())
    {
            sf::Event event;
            while (window.pollEvent(event))
            {
                    if (event.type == sf::Event::Closed)
                            window.close();
            }
            window.clear();
            window.draw(bezierCurve1);
            window.draw(bezierCurve2);
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