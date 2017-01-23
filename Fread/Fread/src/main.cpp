#include <iostream>
#include <string>
#include "Parser/PAJE/paje_interface.hpp"

#include <SFML/Graphics.hpp>
#include "Render/FBezierCurve.hpp"

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
int main(int argc, char* argv[])
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