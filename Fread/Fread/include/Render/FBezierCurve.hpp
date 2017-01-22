#pragma once

#include <SFML/Graphics.hpp>

/* Uses to draw a line between two points with a bezier équation
Bezier curve is based on 4 control points, second and third points are calculated
from the first and fourth control points
It's a drawable object for SFML render window
Usage is :
	FBezierCurbe myBezierCurve(param ... );
	myBezierCurve.calculate();
	window.draw(myBezierCurve);

If the line curve is not calculate before draw it will not be draw
	*/

class FBezierCurve : public sf::Drawable
{
private:

	//Check if curve had been calculated
	bool calculated;
	//Number of segments use to draw the curve
	int nb_subdivision;
	//Vertex of the curve
	sf::VertexArray bezierCurve_points;
	//Control points to calculate Bezier curve
	sf::Vector2f controlPointsArray[4];
	//Color of the curve
	sf::Color color;

	float x(float t); // X parametric equation
	float y(float t); // Y parametric equation
	float lenght(); // distance between first and fourth control points 
	sf::Vector2f normalize(); // Normalizes first to fourth points vector
	sf::Vector2f rotate90(sf::Vector2f vector);

public:
	FBezierCurve();
	FBezierCurve(sf::Vector2f firstPoint, sf::Vector2f lastPoint, int const& nb_subdiv = 100, sf::Color color = sf::Color::Magenta);

	//Set control point on id rank, curbe needs to be recalculate
	void setControlPoint(int const& id, sf::Vector2f newPoint);
	sf::Vector2f getControlPoint(int const& id);

	void calculate(); //Calculates the curve and set calculated boolean to true
	bool isCalculated();

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

	~FBezierCurve();
};

