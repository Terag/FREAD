#include "FContainer.hpp"


FContainer::FContainer()
{
}

FContainer::FContainer( int const& c_id, std::string c_alias) :
    id(c_id), alias(c_alias)
{
}

FContainer::~FContainer()
{
}

FContainer::push_back(patternStruct element){
	patternList.push_back(element);
}

FContainer::pop_back(){
	patternList.pop_back();
}