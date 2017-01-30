/*
Copyright (c) 2017, FREAD - Jérôme Berthelin, Emma Goldblum, Maxime Guillem, Victor Rouquette
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Neither the name of the copyright holders nor the names of its contributors 
  may be used to endorse or promote products derived from this software without
  specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
*/

#pragma once

#include <vector>
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
	//Color of the curve
	sf::Color color;
	//Thickness
	float thickness;
	//Points of the curve
	std::vector<sf::Vector2f> bezierCurve_points;
	//Vertex of the curve
	sf::VertexArray bezierCurve_vertex;
	//Control points to calculate Bezier curve
	sf::Vector2f controlPointsArray[4];

	float x(float t); // X parametric equation
	float y(float t); // Y parametric equation
	float lenght(); // distance between first and fourth control points 
	sf::Vector2f normalize(); // Normalizes first to fourth points vector
	sf::Vector2f rotate90(sf::Vector2f vector);

	//Thickness
	float thickness;
	//Color of the curve
	sf::Color color;

public:
	FBezierCurve();
	FBezierCurve(sf::Vector2f firstPoint, sf::Vector2f lastPoint, int const& nb_subdiv = 100, float const & thick = 1.f, sf::Color color = sf::Color::Magenta);

	//Set control point on id rank, curbe needs to be recalculate
	void setControlPoint(int const& id, sf::Vector2f newPoint);
	sf::Vector2f getControlPoint(int const& id);

	void calculate(); //Calculates the curve and set calculated boolean to true
	bool isCalculated();

	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

	~FBezierCurve();
};



