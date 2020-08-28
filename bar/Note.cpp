//
// Created by kn1ght on 8/8/20.
//

#include "Note.h"

Note::~Note() = default;

// Parameter noteSize must be calculated by its own bar and should be passed by the latter.
Note::Note(Display* dis, Window pWindow, std::pair<int,int> noteSize) {
    this->display = dis;
    this->parentWindow = pWindow;
    Screen *screen;
    // Create note but dont map, that is a job for Bar.h
    this->setNoteWindow(
            XCreateSimpleWindow(dis, pWindow,0,0,10,10,0,1,BlackPixel(this->display,XDefaultScreen(this->display)))
            );
}

Window Note::getNoteWindow() const {
    return this->noteWindow;
}

void Note::setNoteWindow(Window newWindow) {
    this->noteWindow = newWindow;
}
