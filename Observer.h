//
// Created by VodalokLab on 2015/12/4.
//

#ifndef HW2_OBSERVER_H
#define HW2_OBSERVER_H

class Subject;

class Observer {
public:
    ~Observer() {}
    virtual void Update(Subject* changedSubject) = 0;

protected:
    Observer() {};
};


#endif //HW2_OBSERVER_H
