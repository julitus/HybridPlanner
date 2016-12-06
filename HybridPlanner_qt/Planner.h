#ifndef PLANNER_H
#define PLANNER_H

#include "Algs.h"

template <class T>
class Planner
{
    typedef int (*alg)(list<Process<T> *>&, T &, T, T &, T, char &, bool &, int &);
    private:
        T quantum;
        T quantum_io;
        T cs;
        pair<alg, alg> algs;
        list<Process<T> *> processes;
        map<Process<T> *, QString> dic;
        void creationProcesses(int, int th = 0);
        QList<QString> timeProcess;
        QList<QString> timeIO;
        list<Process<T> *> creationThreads(Process<T> *, int);
        void initializeValues(bool, T, T);
        void sortStartTime();
        void moveToStructure(list<Process<T> *> &, list<Process<T> *> &); //1er -> 2do
        void evaluateEvent(char, int, list<Process<T> *> &, list<Process<T> *> &, int &, bool &, int &);
    public:
        Planner(int, int, bool, T qt = 0, T cs = 0);
        Planner(int, int, int, bool, T qt = 0, T cs = 0);
        void startPlanner();
        void setAlgorithms(alg, alg);
        void print();
        QList<QString> getTimeList(char);
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
    qDebug() << "Nro Procesos:"<< nProcess << " - Nro Max de Hilos por Proceso:" << 0;
    sortStartTime();
    this->print();
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
    qDebug() << "Nro Procesos:"<< nProcess << " - Nro Max de Hilos por Proceso:" << t;
    sortStartTime();
    this->print();
}

template<class T>
void Planner<T> :: setAlgorithms(alg pln, alg iao)
{
    this->algs = make_pair(pln, iao);
}

template<class T>
void Planner<T> :: sortStartTime(){
    processes.sort(sortTime);
    int i = 0;
    for (typename list<Process<T> *>::iterator it = this->processes.begin(); it != this->processes.end(); ++it)
        dic[*it] = "P" + QString::number(i++);
}

template<class T>
void Planner<T> :: moveToStructure(list<Process<T> *> & fir, list<Process<T> *> & sec)
{
    sec.push_back(fir.front());
    fir.pop_front();
}

template<class T>
void Planner<T> :: evaluateEvent(char type, int event, list<Process<T> *> &fir, list<Process<T> *> &sec, int &n_cs, bool &isNew, int &status)
{
    if(type == PLN){
        switch(event){
            case 0: break;
            case 1: break;
            case 2:
                n_cs = this->cs;
                status = CSW;
                break;
            case 3: break;
            case 4:
                status = NML;
                isNew = true;
                moveToStructure(fir, sec);
                break;
            case 5:
                fir.pop_front();  break;
            case 6:
                n_cs = this->cs;
                status = CSW;
                break;
            default:
                break;
        }
    }else if(type == IAO){
        switch(event){
            case 0: break;
            case 1: break;
            case 2:
                isNew = true;
                moveToStructure(fir, sec);
                break;
            default:
                break;
        }
    }
}

template<class T>
void Planner<T> :: startPlanner(){
    int time = 0, n_pln = 1, n_iao, n_cs = cs, n_quantum = quantum, n_quantum_io = quantum_io;
    int pln_status = FIR, iao_status = FIR;
    char pln_type = CHG, iao_type = CHG;
    bool pln_isNew = false, iao_isNew = false, isNotStarted = true;
    typename list<Process<T> *>::iterator it = this->processes.begin();
    list<Process<T> *> pln;
    list<Process<T> *> iao;
    while(!pln.empty() or !iao.empty() or isNotStarted){
        while(it != this->processes.end()){
            if((*it)->getStartTime() != time)
                break;
            else{
                pln.push_back(*it++);
                pln_isNew = true;
                isNotStarted = false;
            }
        }
        n_pln = this->algs.first(pln, n_cs, cs, n_quantum, quantum, pln_type, pln_isNew, pln_status);
        n_iao = this->algs.second(iao, n_cs, cs, n_quantum_io, quantum_io, iao_type, iao_isNew, iao_status);
        if(!pln.empty())
            this->timeProcess << ((n_pln == 3 or n_pln == 4 or n_pln == 6) ? "CSW" : dic[pln.front()]);
        else
            this->timeProcess << "TOU";
        if(!iao.empty())
            this->timeIO << dic[iao.front()];
        else
            this->timeIO << "TOU";
        qDebug() << "t = " << time << " >> " << this->timeProcess.last() << " - " << this->timeIO.last();
        qDebug() << n_pln << " - " << n_iao;
        evaluateEvent(PLN, n_pln, pln, iao, n_cs, iao_isNew, pln_status);
        evaluateEvent(IAO, n_iao, iao, pln, n_cs, pln_isNew, iao_status);
        time++;
    }
}

template<class T>
void Planner<T> :: print()
{
    qDebug() << "Quatum:" << this->quantum << " - Cambio de Contexto:" << this->cs << " - Quantum para E/S:" << this->quantum_io;
    for (typename list<Process<T> *>::iterator it = this->processes.begin(); it != this->processes.end(); ++it)
        (*it)->print();
}

template<class T>
void Planner<T> :: initializeValues(bool isRnd, T qt, T cs)
{
    if (isRnd) {
        this->quantum = randomNumber(BEGIN_QUANTUM, END_QUANTUM);
        this->cs = randomNumber((BEGIN_QUANTUM * PORC) / 100, (END_QUANTUM * PORC) / 100) + 1;
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
    list<Process<T> *> threads;
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
list<Process<T> *> Planner<T> :: creationThreads(Process<T> *pr, int th)
{
    list<Process<T> *> threads;
    for(int i = 0; i < th; ++i) {
        Series s_blast = randomBlast();
        threads.push_back(new Thread<T>(0, s_blast, pr));
    }
    return threads;
}

template<class T>
QList<QString> Planner<T> :: getTimeList(char c)
{
    return (c == 'P') ? timeProcess : timeIO;
}

#endif // PLANNER_H
