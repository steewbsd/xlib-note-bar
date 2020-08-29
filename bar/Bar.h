//
// Created by kn1ght on 8/8/20.
//

#include "Note.h"
#include <X11/Xlib.h>
#include "Size.h"
#include <map>
#include <vector>

#ifndef NOTEBAR_BAR_H
#define NOTEBAR_BAR_H

class Bar {
private:
    bool state_hidden;
    std::vector<Note>noteCollection;
    Window barWindow;
    Display* display;
    std::string position;
    XWindowAttributes rootWindowAttributes;
    int getNoteWidth();
    // Distance from the bar to the sides of the screen
    // This margin is a copy of this->margin but removing the unneeded margin side
    std::pair<float,float> size;
    /* This pair will be multiplied to the size pair to obtain whether the coordinates should be subtracted from the relative position (this->respectivePosition), for example, if a bar is moved from top to bottom,
    the y index should be multiplied by -1 (because the relative position would be rootWindowAttributes.height), otherwise most windows would be off-screen after mirroring them to the other side
     */
public:
    void mapAll();
    void setAssociatedWindow(Window win);
    std::pair<int,int> calculateProperties(std::pair<float,float> size);
    const std::pair<float, float> &getSize() const;
    std::pair<float,float> relativeSize;
    void toggleHidden();

    void setSize(const std::pair<float, float> &size);
    Bar(const std::string &newPosition, std::pair<float, float> size, Display *display);

    std::string getPosition() const;
    Window getAssociatedWindow();
    Note* getNoteByIndex(const int& index);
    void add(const Note &new_note);
    ~Bar();

    Size distributeAllNotes(const float *MAX_SIZE);


    void resize(std::pair<int, int> newSize);
    void moveTo(std::string nPos);
};


#endif //NOTEBAR_BAR_H
