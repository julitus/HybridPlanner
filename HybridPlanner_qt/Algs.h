#ifndef ALGS_H
#define ALGS_H

#include "Thread.h"

bool sortTime(Process<int> *, Process<int> *);
bool sortTimeBurst(Process<int> *, Process<int> *);

template<class T>
Process<T> * findMinBurst(list<Process<T> *>& processes)
{
    Process<T> *minPr = *processes.begin();
    T min = minPr->blast.front();
    for (typename list<Process<T> *>::iterator it = processes.begin(); it != processes.end(); ++it){
        if(min > (*it)->blast.front()){
            minPr = *it;
            min = minPr->blast.front();
        }
    }
    return minPr;
}

template<class T>
int fifo(list<Process<T> *>& process, T &cs, T ccs, T &qt, T quantum, char &type, bool &isNew, int &status)
{
    if(!process.empty()){
        if(status == FIR){
            status = NML;
        }
        if(status == NML){
            (*(*process.begin())->blast.begin())--;
            //qDebug() << (*(*process.begin())->blast.begin());
            if((*(*process.begin())->blast.begin()) == 0){
                (*process.begin())->blast.pop_front();
                return ((*process.begin())->blast.size() == 0) ? 5 : 2;
            }
            return 1;
        }else if(status == CSW){
            cs--;
            if (cs <= 0){
                status = NML;
                return 4;
            }
            return 3;
        }
    }
    return 0;
}

template<class T>
int sjf(list<Process<T> *>& process, T &cs, T ccs,  T &qt, T quantum, char &type, bool &isNew, int &status)
{
    if(!process.empty()){
        if(isNew){
            //process.sort(sortTimeBurst);
            isNew = false;
            if(status == FIR){
                status = NML;
                process.sort(sortTimeBurst);
            }else{
                if(process.front() != findMinBurst(process)){
                    if(type == CHG)
                        cs = ccs;
                    type = OWN;
                    status = CSW;
                    if(cs > 0){
                        return 3;
                    }
                }
            }
        }
        if(status == NML){
            (*(*process.begin())->blast.begin())--;
            if((*(*process.begin())->blast.begin()) == 0){
                (*process.begin())->blast.pop_front();
                return ((*process.begin())->blast.size() == 0) ? 5 : 2;
            }
            return 1;
        }else if(status == CSW){
            cs--;
            if (cs <= 0){
                status = NML;
                if (type == OWN){
                    type = CHG;
                    process.sort(sortTimeBurst);
                    (*(*process.begin())->blast.begin())--;
                    return 1;
                }
                return 4;
            }
            return 3;
        }
    }
    return 0;
}

template<class T>
int rr(list<Process<T> *>& process, T &cs, T ccs, T &qt, T quantum, char &type, bool &isNew, int &status)
{
    if(!process.empty()){
        if(status == NML){
            (*(*process.begin())->blast.begin())--;
            //qDebug() << (*(*process.begin())->blast.begin());
            if((*(*process.begin())->blast.begin()) == 0){
                (*process.begin())->blast.pop_front();
                return ((*process.begin())->blast.size() == 0) ? 5 : 2;
            }
            return 1;
        }else if(status == CSW){
            cs--;
            if (cs <= 0){
                status = NML;
                return (cs == -1) ? 1 : 4;
            }
            return 3;
        }
    }
    return 0;
}

#endif // ALGS_H
