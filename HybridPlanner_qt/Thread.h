#ifndef THREAD_H
#define THREAD_H

#include "Process.h"

template <class T>
class Thread: public Process<T>
{
    public:
        Thread(T, Series &, Process<T> *);
        void print();
};

template<class T>
Thread<T> :: Thread(T start, Series &blast, Process<T> * creator): Process<T>(start, blast, creator)
{
    this->type = THR;
}

template<class T>
void Thread<T> :: print()
{
    QString str = "";
    for (int i = 0; i < this->blast.size(); i++) {
        if (i > 0) str += ", ";
        str += QString::number(this->blast[i]);
    }
    qDebug() << this->type << " - " << this->creator << " - " << this->start_time << " - " << str;
    for (int i = 0; i < this->threads.size(); ++i)
        this->threads[i]->print();
}

#endif // THREAD_H
