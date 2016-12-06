#ifndef PROCESS_H
#define PROCESS_H

#include "TyDefFunc.h"

template <class T>
class Process
{
    protected:
        char type;
        T start_time;
        Process<T> *creator;
        list<Process<T> *> threads;
    public:
        Series blast;
        Process(T, Series &, Process<T> * creator = 0);
        void setThreads(list<Process<T> *> &);
        char getType();
        T getStartTime();
        Process<T> * getPattern();
        virtual void print();
};

template<class T>
Process<T> :: Process(T start, Series &blast, Process<T> * creator)
{
    this->type = PRO;
    this->start_time = start;
    this->blast = blast;
    this->creator = creator;
}

template<class T>
void Process<T> :: setThreads(list<Process<T> *> &threads)
{
    this->threads = threads;
}

template<class T>
char Process<T> :: getType()
{
    return this->type;
}

template<class T>
T Process<T> :: getStartTime()
{
    return this->start_time;
}

template<class T>
Process<T> * Process<T> :: getPattern()
{
    return this->creator;
}

template<class T>
void Process<T> :: print()
{
    qDebug() << this->type << " - " << this->creator;
    QString str = "";

    for (Series::iterator it = this->blast.begin(); it != this->blast.end(); ++it){
        if (it != this->blast.begin()) str += ", ";
        str += QString::number(*it);
    }

    qDebug() << this->start_time << " - " << str;
    for (typename list<Process<T> *>::iterator it = this->threads.begin(); it != this->threads.end(); ++it)
        (*it)->print();

    qDebug() << '\n';
}

#endif // PROCESS_H
