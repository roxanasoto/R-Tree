#ifndef ELEMENT_H
#define ELEMENT_H

#include "Region.h"

class Element
{
    public:
        int oid;
        Region mbr;
        Element();
};

#endif // ELEMENT_H