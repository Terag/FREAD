#include "Render/FBezierCurve.hpp"

#include <math.h>

using namespace sf;
using namespace std;

FBezierCurve::FBezierCurve() :
	calculated(false), nb_subdivision(20), color(sf::Color::Magenta)
{
	bezierCurve_points = VertexArray(sf::LinesStrip, nb_subdivision+1);

	controlPointsArray[0] = Vector2f(0, 200);
	controlPointsArray[3] = Vector2f(300, 400);

	float l = lenght()/100;
	Vector2f directionnal(normalize());
	Vector2f normale(rotate90(directionnal));

	controlPointsArray[1] = controlPointsArray[0] + 5.f * l * directionnal + 20.f * l * normale;
	controlPointsArray[2] = controlPointsArray[3] + -30.f * l * directionnal + 2.f * l * normale;
}

FBezierCurve::FBezierCurve(sf::Vector2f firstPoint, sf::Vector2f lastPoint, int const & nb_subdiv, sf::Color curveColor) :
	calculated(false), nb_subdivision(nb_subdiv), color(curveColor)
{
	bezierCurve_points = VertexArray(sf::LinesStrip, nb_subdivision+1);

	controlPointsArray[0] = firstPoint;
	controlPointsArray[3] = lastPoint;

	float l = lenght()/100;
	Vector2f directionnal(normalize());
	Vector2f normale(rotate90(directionnal));

	controlPointsArray[1] = controlPointsArray[0] + 5.f * l * directionnal + 20.f * l * normale;
	controlPointsArray[2] = controlPointsArray[3] + -30.f * l * directionnal + 2.f * l * normale;
}

float FBezierCurve::x(float t)
{
	float x = (controlPointsArray[0].x)*pow((1 - t), 3) + 3 * (controlPointsArray[1].x) *t *pow((1 - t), 2) + 3 * (controlPointsArray[2].x)*pow(t, 2) * (1 - t) + (controlPointsArray[3].x)*pow(t, 3);
	return x;
}

float FBezierCurve::y(float t)
{
	float y = (controlPointsArray[0].y)*pow((1 - t), 3) + 3 * (controlPointsArray[1].y) *t *pow((1 - t), 2) + 3 * (controlPointsArray[2].y)*pow(t, 2) * (1 - t) + (controlPointsArray[3].y)*pow(t, 3);
	return y;
}

float FBezierCurve::lenght()
{
	return sqrt(pow(controlPointsArray[3].x - controlPointsArray[0].x, 2) + pow(controlPointsArray[3].y - controlPointsArray[0].y, 2));
}

sf::Vector2f FBezierCurve::normalize()
{
	return Vector2f((controlPointsArray[3].x - controlPointsArray[0].x) / lenght(), (controlPointsArray[3].y - controlPointsArray[0].y) / lenght());
}

sf::Vector2f FBezierCurve::rotate90(sf::Vector2f vector)
{
	return sf::Vector2f(vector.y, -vector.x);
}


void FBezierCurve::setControlPoint(int const & id, sf::Vector2f newPoint)
{
	calculated = false;
	controlPointsArray[id] = newPoint;
}

sf::Vector2f FBezierCurve::getControlPoint(int const & id)
{
	return controlPointsArray[id];
}

void FBezierCurve::calculate()
{
	for (int i = 0; i < nb_subdivision+1; i++) {
		float t = (float)i / (float)nb_subdivision;
		bezierCurve_points[i] = Vertex(Vector2f(x(t), y(t)), color);
	}
	calculated = true;
}

bool FBezierCurve::isCalculated()
{
	return calculated;
}

void FBezierCurve::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (calculated) {
		target.draw(bezierCurve_points, states);
	}
}


FBezierCurve::~FBezierCurve()
{
}
