//
// Created by kn1ght on 9/8/20.
//

#include "Margin.h"
#include <iostream>

// Every margin should be passed to the constructor, if no margin is needed null should be passed
// FIXME
// Top, left, bottom, right (anticlockwise)
Margin::Margin(float top, float left, float bottom, float right) {
    marginTop = top;
    marginLeft = left;
    marginBottom = bottom;
    marginRight = right;
}

Margin::Margin() {
    this->marginBottom = 0;
    this->marginLeft = 0;
    this->marginTop = 0;
    this->marginRight = 0;
}