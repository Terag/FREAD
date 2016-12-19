#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280,1024), "SFML works!");
	sf::RectangleShape shape(sf::Vector2f(100,20));
	shape.setFillColor(sf::Color(120,140,0));
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        
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
	}

	return 0;
}