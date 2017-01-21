#pragma once
#include<vector>

class occurrence
{
private :
	//float tStart;
	//float tEnd;
	int id;
	std::vector<float> timeStamps;
	//std::vector<event> events;
	bool isLoaded;
	int patternId;


public:
	occurrence();
	~occurrence();
};

bool operator==(occurrence A, occurrence B);
bool operator!=(occurrence A, occurrence B);