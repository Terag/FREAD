/*#pragma once
#include<vector>
#include<string>	
#include "occurrence.h"

struct event
{
	EventType type;
	Color color;
	std::string Alias;

};
enum EventType
{
	Wait,
	Compute,
	Send
};
struct event
{
	int id;
	struct coord
	{
		float t;
		int id;
	};
	coord start;
	coord end;
};
class Pattern
{
private :
	int id;
	std::vector<event> events;
	std::vector<float> meanTimeStamps;
	std::vector<occurrence> occurrences;
	
	

public:
	Pattern();
	~Pattern();
};
bool operator==(pattern A,pattern B);
bool operator!=(pattern A, pattern B);

*/