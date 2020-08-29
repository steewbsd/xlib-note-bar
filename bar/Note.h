//
// Created by kn1ght on 8/8/20.
//
#include <iostream>
#include <X11/Xlib.h>

#ifndef NOTEBAR_NOTE_H
#define NOTEBAR_NOTE_H

class Note {
private:

    Display* display;
    Window parentWindow;
    Window noteWindow;
    // Constructor and destructor
public:
    std::string toString();
    Window getNoteWindow() const;
    void setNoteWindow(Window newWindow);
    std::string Content;
    ~Note();
    void resizeAndMove(int x, int y, int width, int height);

    Note(Display *dis, Window pWindow);
};

#endif //NOTEBAR_NOTE_H
