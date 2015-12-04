//
// Created by VodalokLab on 2015/12/4.
//

#include "Subject.h"

Subject::~Subject() {

}

void Subject::Attach(Observer *observer) {
    _observers->push_back(observer);
}

void Subject::Detach(Observer *observer) {
    _observers->remove(observer);
}

void Subject::Notify() {
    for(list<Observer*>::iterator iterator = _observers->begin() ; iterator!=_observers->end() ; iterator ++){
        (*iterator)->Update(this);
    }
}

Subject::Subject() {
    _observers = new list<Observer*>();
}
