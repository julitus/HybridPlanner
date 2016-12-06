#ifndef TYDEFFUNC_H
#define TYDEFFUNC_H

#include <iostream>
#include <list>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <QDebug>
#include <QString>
#include <QList>

using namespace std;

#define PRO 'P'
#define THR 'T'
#define BEGIN_QUANTUM 5 //50
#define END_QUANTUM 12 //120
#define PORC 10
#define S_BLAST 7
#define DIF_MIN 3 //30
#define DIF_MAX 10 //100
#define INI_TIME 5 //20

#define CHG 'C'
#define OWN 'O'

#define PLN 'X'
#define IAO 'Y'

#define NML 1
#define CSW 2
#define TOU 3
#define FIR 4

typedef int Num;
typedef list<Num> Series;

int randomNumber(int, int);
Series randomBlast();

#endif // TYDEFFUNC_H
