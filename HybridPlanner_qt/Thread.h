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

    for (Series::iterator it = this->blast.begin(); it != this->blast.end(); ++it){
        if (it != this->blast.begin()) str += ", ";
        str += QString::number(*it);
    }
    qDebug() << this->type << " - " << this->creator << " - " << this->start_time << " - " << str;

    for (typename list<Process<T> *>::iterator it = this->threads.begin(); it != this->threads.end(); ++it)
        (*it)->print();
}

#endif // THREAD_H
