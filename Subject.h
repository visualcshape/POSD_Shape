//
// Created by VodalokLab on 2015/12/4.
//

#ifndef HW2_SUBJECT_H
#define HW2_SUBJECT_H
#include "Observer.h"
#include <list>

using namespace std;

class Subject {
public:
    virtual ~Subject();

    virtual void Attach(Observer*);

    virtual void Detach(Observer*);
protected:
    virtual void Notify();

    Subject();
private:
    list<Observer*> *_observers;
};


#endif //HW2_SUBJECT_H
