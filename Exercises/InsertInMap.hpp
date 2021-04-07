#ifndef INSERTINMAP_H
#define INSERTINMAP_H

#include "Employee.hpp"

#include <map>

class InsertInMap {
public:
    InsertInMap(multimap<string, Employee*> &m);
    void operator() (Employee* e);
private:
    multimap<string, Employee*> &m_;
};

#endif // INSERTINMAP_H
