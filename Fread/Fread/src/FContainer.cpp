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

void FContainer::add_pattern(patternStruct element){
	patternList.push_back(element);
}

void FContainer::remove_pattern(){
	patternList.pop_back();
}

bool FContainer::contains( patternStruct element ){
	for(auto it = patternList.begin(); it != patternList.end(); ++it){
		if(it->tBegin == element.tBegin){
			return true;
		}
	}
	return false;
}