//
// Created by kn1ght on 8/8/20.
//

#include "Note.h"
#include <X11/Xlib.h>
#include "Size.h"
#include <vector>

#ifndef NOTEBAR_BAR_H
#define NOTEBAR_BAR_H

class Bar {
private:


    std::vector<Note>noteCollection;
    Window barWindow;
    std::string position;
    // Distance from the bar to the sides of the screen
    // This margin is a copy of this->margin but removing the unneeded margin side
    std::pair<float,float> size;
    /* This pair will be multiplied to the size pair to obtain whether the coordinates should be subtracted from the relative position (this->respectivePosition), for example, if a bar is moved from top to bottom,
    the y index should be multiplied by -1 (because the relative position would be rootWindowAttributes.height), otherwise most windows would be off-screen after mirroring them to the other side
     */
    std::pair<float,float> directionMultiplier;
public:
    const std::pair<float, float> &getSize() const;
    std::pair<float,float> respectivePosition;

    void setSize(const std::pair<float, float> &size);
    Bar(const std::string &newPosition, std::pair<float, float> size, Display *display);

    const std::string &getPosition() const;
    Window getAssociatedWindow();
    void add(const Note *new_note);
    std::vector<Note> notes();
    ~Bar();

    Size distributeAllNotes(const float *MAX_SIZE);
};


#endif //NOTEBAR_BAR_H
