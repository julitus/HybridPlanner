#include "mainwindow.h"
#include "Planner.h"
#include <QApplication>
#include <typeinfo> // typeid(objectClass).name()

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*
    Series s(2, 10);
    Series t(3, 20);

    Process<Num> *pr = new Process<Num>(5, s);
    pr->print();
    pr = new Thread<Num>(25, t, pr);
    pr->print();
    pr->getPattern()->print();
    */

    qDebug() << "Creacion de 7 Procesos Aleatorios con quantum y cambio de contexto aleatorio";
    Planner<Num> *pl1 = new Planner<Num>(3, 3, true);
    //pl1->setAlgorithms(fifo, fifo);
    pl1->setAlgorithms(sjf, sjf);
    //pl1->setAlgorithms(rr, rr);

    /*pl1->print();
    qDebug() << "-----------------------------------";*/
    /*pl1->sortStartTime();
    pl1->print();*/

    pl1->startPlanner();

    /*qDebug() << "Creacion de entre 3 a 9 Procesos Aleatorios con con quantum y cambio de contexto estatico";
    Planner<Num> *pl2 = new Planner<Num>(9, 3, false, fifo, fifo, 100, 7);
    pl2->print();
    qDebug() << "Creacion de entre 3 a 9 Procesos Aleatorios, con 1 a 5 hilos en cada proceso y con quantum y cambio de contexto aleatorio";
    Planner<Num> *pl3 = new Planner<Num>(3, 9, 5, true, fifo, fifo);
    pl3->print();
    qDebug() << "Creacion de entre 1 a 7 Procesos Aleatorios, con 1 a 3 hilos en cada proceso y con quantum y cambio de contexto estatico";
    Planner<Num> *pl4 = new Planner<Num>(1, 7, 3, false, fifo, fifo, 80, 10);
    pl4->print();*/

    return a.exec();
}

