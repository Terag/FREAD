#include "FContainer.hpp"


FContainer::FContainer()
{
}

FContainer::FContainer(int i):id(i){

}

FContainer::FContainer( int const& c_id, std::string c_alias, std::pair<float, float> t_begin_and_end) :
    id(c_id), alias(c_alias), timestamp_begin_end(t_begin_and_end)
{
}

FContainer::~FContainer()
{
}

void FContainer::add_pattern(patternStruct element){
	if( !(*this).contains(element) )
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