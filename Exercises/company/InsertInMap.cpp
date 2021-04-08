#include "InsertInMap.hpp"

namespace company {

InsertInMap::InsertInMap(multimap<string, Employee*> &m)
    : m_(m)
{}

void InsertInMap::operator() (Employee* e)
{
    m_.insert(make_pair(e->Employee::getName(), e));
}

}