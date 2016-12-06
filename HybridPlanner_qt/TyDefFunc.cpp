#include "TyDefFunc.h"

int randomNumber(int a, int b)
{
    if (a > b) swap(a, b);
    return rand() % (b - a + 1) + a;
}

Series randomBlast()
{
    int n_times = randomNumber(0, S_BLAST);
    n_times += (n_times % 2) ? 0 : 1;
    Series blast;
    for(int i = 0; i < n_times; ++i)
        blast.push_back(randomNumber(BEGIN_QUANTUM - DIF_MIN, END_QUANTUM + DIF_MAX));
    return blast;
}
