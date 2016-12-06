#include "Algs.h"

bool sortTime(Process<int> * a, Process<int> * b)
{
    return (a->getStartTime() < b->getStartTime());
}

bool sortTimeBurst(Process<int> *a, Process<int> *b)
{
    return (a->blast.front() < b->blast.front());
}
