#ifndef PROCESS_H
#define PROCESS_H

#include "TyDefFunc.h"

template <class T>
class Process
{
    protected:
        char type;
        Series blast;
        T start_time;
        Process<T> *creator;
        vector<Process<T> *> threads;
    public:
        Process(T, Series &, Process<T> * creator = 0);
        void setThreads(vector<Process<T> *> &);
        char getType();
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
void Process<T> :: setThreads(vector<Process<T> *> &threads)
{
    this->threads = threads;
}

template<class T>
char Process<T> :: getType()
{
    return this->type;
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
    for (int i = 0; i < this->blast.size(); i++) {
        if (i > 0) str += ", ";
        str += QString::number(this->blast[i]);
    }
    qDebug() << this->start_time << " - " << str;
    for (int i = 0; i < this->threads.size(); ++i)
        this->threads[i]->print();
    qDebug() << '\n';
}

#endif // PROCESS_H
