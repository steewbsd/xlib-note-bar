//
// Created by kn1ght on 8/8/20.
//

#include "Note.h"
#include "Size.h"
#include <vector>
#include "Margin.h"

#ifndef NOTEBAR_BAR_H
#define NOTEBAR_BAR_H

class Bar {
private:

    std::vector<Note>noteCollection;
    std::string position;
    Margin *margin;
    // This margin serves as the current margin, because if the bar is in one position one of the margins should be ditched. (Example: Bar in the left, right border should not be used)
    Margin currentPositionMargin;


public:
    const std::string &getPosition() const;
    void add(const Note *new_note);
    std::vector<Note> notes();
    Bar(const std::string *newPosition, Margin *optionalMargin);
    ~Bar();

    Size distributeAllNotes(const float *MAX_SIZE);
};


#endif //NOTEBAR_BAR_H
