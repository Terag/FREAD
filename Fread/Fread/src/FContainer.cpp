#include "FContainer.hpp"


FContainer::FContainer()
{
}

FContainer::FContainer( int const& c_id, std::string c_alias, std::pair<float, float> t_begin_and_end) :
    id(c_id), alias(c_alias), timestamp_begin_end(t_begin_and_end)
{
}

FContainer::~FContainer()
{
}
