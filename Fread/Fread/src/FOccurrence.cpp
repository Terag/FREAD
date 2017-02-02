#include "FOccurrence.hpp"

FOccurrence::FOccurrence()
{
}

FOccurrence::FOccurrence(int p, int i): m_patternId(p), m_id(i) 
{
}

FOccurrence::~FOccurrence()
{
}

int FOccurrence::getId() 
{
    return m_id;
}

int FOccurrence::getPatternId() 
{
    return m_patternId;
}

int FOccurrence::getContainerId() 
{
    return m_containerId;
}

std::vector<float> FOccurrence::getTimeStamps() 
{
    return m_timeStamps;
}

bool FOccurrence::getIsLoaded()
{
    return m_isLoaded;
}

bool operator==(FOccurrence A, FOccurrence B)
{
	return ( ( A.getId() == B.getId() ) && ( A.getPatternId() == B.getPatternId() ) );
}

bool operator!=(FOccurrence A, FOccurrence B)
{
	return ( ( A.getId() != B.getId() ) && ( A.getPatternId() != B.getPatternId() ) );
}
