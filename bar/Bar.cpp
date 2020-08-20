//
// Created by kn1ght on 8/8/20.
//
#include <iostream>
#include <vector>
#include "Bar.h"
#include "Size.h"
#include "Note.h"

void Bar::add(const Note *new_note) {
    this->noteCollection.push_back(*new_note);
}

std::vector<Note> Bar::notes() {
    return this->noteCollection;
}

Bar::Bar(const std::string *newPosition, Margin* optionalMargin) {
    this->position = *newPosition;
    this->margin = optionalMargin;
    this->currentPositionMargin = *this->margin;
    if (this->position == "top") {
        this->currentPositionMargin.setMarginBottom(0);
    } else if (this->position == "left") {
        this->currentPositionMargin.setMarginRight(0);
    } else if (this->position == "bottom") {
        this->currentPositionMargin.setMarginLeft(0);
    } else if (this->position == "right") {
        this->currentPositionMargin.setMarginTop(0);
    } else {
        return;
    }
}


// This will return the main size of every note (if position requires notes to be vertically aligned the size will
// represent the height of the notes, in case of horizontal it will represent the width).
Size Bar::distributeAllNotes(const float *MAX_SIZE) {

    // Get number of notes
    int currentNotes = this->notes().size();

    Size tmpSize = Size(0,0);
    // Divide max available space with the number of notes to get the size per note (spn) value
    // float spnX = (*MAX_SIZE-this->margin->getMarginLeft()-this->margin->getMarginRight()) /
    return Size(0,0);

}

const std::string &Bar::getPosition() const {
    return position;
}


Bar::~Bar() = default;

