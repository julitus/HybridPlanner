#ifndef PLANNER_H
#define PLANNER_H

#include "Thread.h"

template <class T>
class Planner
{
    private:
        T quantum;
        T quantum_io;
        T cs;
        vector<Process<T> *> processes;
        void creationProcesses(int, int th = 0);
        vector<Process<T> *> creationThreads(Process<T> *, int);
        void initializeValues(bool, T, T);
    public:
        Planner(int, int, bool, T qt = 0, T cs = 0);
        Planner(int, int, int, bool, T qt = 0, T cs = 0);
        void print();
};

/*
 * Initializes with a random number of processes between "start" and "end" inclusive
 */
template<class T>
Planner<T> :: Planner(int start, int end, bool isRnd, T qt, T cs)
{
    srand (time(NULL));
    int nProcess = randomNumber(start, end);
    this->initializeValues(isRnd, qt, cs);
    this->creationProcesses(nProcess, 0);
    qDebug() << nProcess << " - " << 0;
}

/*
 * Initializes with a random number of processes between "start" and "end" inclusive
 * and a random quantity of up to "t" threads for each process
*/
template<class T>
Planner<T> :: Planner(int start, int end, int t, bool isRnd, T qt, T cs)
{
    srand (time(NULL));
    int nProcess = randomNumber(start, end);
    this->initializeValues(isRnd, qt, cs);
    this->creationProcesses(nProcess, t);
    qDebug() << nProcess << " - " << t;
}

template<class T>
void Planner<T> :: print()
{
    qDebug() << this->quantum << " - " << this->cs << " - " << this->quantum_io;
    for (int i = 0; i < this->processes.size(); ++i)
        this->processes[i]->print();
}

template<class T>
void Planner<T> :: initializeValues(bool isRnd, T qt, T cs)
{
    if (isRnd) {
        this->quantum = randomNumber(BEGIN_QUANTUM, END_QUANTUM);
        this->cs = randomNumber((BEGIN_QUANTUM * PORC) / 100, (END_QUANTUM * PORC) / 100);
    } else {
        this->quantum = qt;
        this->cs = cs;
    }
    this->quantum_io = randomNumber(BEGIN_QUANTUM, END_QUANTUM);
}

template<class T>
void Planner<T> :: creationProcesses(int pr, int th)
{
    Process<T> *process;
    vector<Process<T> *> threads;
    Series s_blast;
    for(int i = 0; i < pr; ++i) {
        if (th == 0) s_blast = randomBlast();
        process = new Process<T>(randomNumber(0, INI_TIME), s_blast);
        if (th) {
            threads = creationThreads(process, randomNumber(1, th));
            process->setThreads(threads);
        }
        this->processes.push_back(process);
    }
}

template<class T>
vector<Process<T> *> Planner<T> :: creationThreads(Process<T> *pr, int th)
{
    vector<Process<T> *> threads;
    for(int i = 0; i < th; ++i) {
        Series s_blast = randomBlast();
        threads.push_back(new Thread<T>(0, s_blast, pr));
    }
    return threads;
}

#endif // PLANNER_H
