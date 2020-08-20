//
// Created by kn1ght on 9/8/20.
//

#include "Size.h"

Size::Size(float sizeX, float sizeY) {

}

float Size::getSizeX() const {
    return sizeX;
}

void Size::setSizeX(float newSizeX) {
    this->sizeX = newSizeX;
}

float Size::getSizeY() const {
    return sizeY;
}

void Size::setSizeY(float newSizeY) {
    this->sizeY = newSizeY;
}

void Size::resizeTo(const Size *newSize) {
    this->sizeX = newSize->getSizeX();
    this->sizeY = newSize->getSizeY();
}

void Size::expand(const Size *addSize) {
    this->setSizeX(this->getSizeX()+addSize->getSizeX());
    this->setSizeY(this->getSizeY()+addSize->getSizeY());
}

