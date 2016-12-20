#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Parser/PAJE/Reader_MainTrace.hpp"
#include "FColor.hpp"

int main(int argc, char* argv[])
{
    /*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
            sf::Event event;
            while (window.pollEvent(event))
            {
                    if (event.type == sf::Event::Closed)
                            window.close();
            }

            window.clear();
            window.draw(shape);
            window.display();
    }*/
    if(argc != 2){
        std::cout << "invalid format\n valid format : Fread trace_path" << std::endl;
        return -1;
    }
    
    std::string path = argv[1];
            
    if(path.substr(path.size()-6, 6) != ".trace"){
        std::cout << "invalid trace format, need *.trace" << std::endl;
        return -1;
    }
    
    paje::Reader_MainTrace mainTrace(path);
    
    return 0;
}