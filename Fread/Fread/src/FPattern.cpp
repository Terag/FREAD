#include "FPattern.hpp"



FPattern::FPattern()
{
}

FPattern::FPattern(int i):m_id(i){
	
}

FPattern::~FPattern()
{
}

std::vector<eventType> FPattern::getEventTypes() 
{
    return m_eventTypes;
}

int FPattern::getId() 
{
    return m_id;
}

std::vector<float> FPattern::getMeanTimeStamps()
{
    return m_meanTimeStamps;
}

/* std::vector<FOccurrence> FPattern::getOccurrences() 
{
    return m_occurrences;
} */

bool operator==(FPattern A, FPattern B)
{
	return A.getId() == B.getId();
}

bool operator!=(FPattern A, FPattern B)
{
	return A.getId() != B.getId();
}
