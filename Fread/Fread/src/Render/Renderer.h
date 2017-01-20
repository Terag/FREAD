#pragma once
#include<map>
#include "pattern.h"
class Renderer
{
private:
	std::map<int,pattern> patternMap;
public:
	Renderer();
	~Renderer();
};

