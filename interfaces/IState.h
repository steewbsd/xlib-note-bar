
#ifndef ISTATE_H
#define ISTATE_H

#include <iostream>

template<class T>
class IState {
public:
    virtual void set(T newT);
    virtual T get();

};

#endif