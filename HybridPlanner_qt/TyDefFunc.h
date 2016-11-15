#ifndef TYDEFFUNC_H
#define TYDEFFUNC_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <QDebug>
#include <QString>

using namespace std;

#define PRO 'P'
#define THR 'T'
#define BEGIN_QUANTUM 50
#define END_QUANTUM 120
#define PORC 10
#define S_BLAST 7
#define DIF_MIN 30
#define DIF_MAX 100
#define INI_TIME 20

typedef int Num;
typedef vector<Num> Series;

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

#endif // TYDEFFUNC_H
