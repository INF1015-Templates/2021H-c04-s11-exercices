#pragma once

#include "Employee.hpp"

#include <map>

namespace company {

class InsertInMap {
public:
    InsertInMap(multimap<string, Employee*> &m);
    void operator() (Employee* e);
private:
    multimap<string, Employee*> &m_;
};

}

