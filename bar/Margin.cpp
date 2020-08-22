//
// Created by kn1ght on 9/8/20.
//

#include "Margin.h"
#include <iostream>

// Every margin should be passed to the constructor, if no margin is needed null should be passed
// FIXME
// Top, left, bottom, right (anticlockwise)
Margin::Margin(float* margins...) {
  if (&margins[0] != nullptr) {
    marginTop = margins[0];
  }
  if (&margins[1] != nullptr) {
    marginLeft = margins[1];
  }
  if (&margins[2] != nullptr) {
    marginBottom = margins[2];
  }
  if (&margins[3] != nullptr) {
    marginRight = margins[3];
  }
}

Margin::Margin() {
    this->marginBottom = 0;
    this->marginLeft = 0;
    this->marginTop = 0;
    this->marginRight = 0;
}