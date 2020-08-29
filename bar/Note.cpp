//
// Created by kn1ght on 8/8/20.
//

#include "Note.h"

Note::~Note() {
    XUnmapWindow(this->display,this->getNoteWindow());
};

// Parameter noteSize must be calculated by its own bar and should be passed by the latter.
Note::Note(Display* dis, Window pWindow) {
    this->display = dis;
    Screen *screen = XDefaultScreenOfDisplay(this->display);
    this->parentWindow = pWindow;
    Visual * visual = XDefaultVisualOfScreen(screen);
    int depth = XDefaultDepthOfScreen(screen);
    // Create note but dont map, that is a job for Bar.h
    // XCreateWindow(display, parent, x, y, width, height, border_width, depth, class, visual, valuemask, attributes)
    XSetWindowAttributes swa;
    swa.override_redirect = True;
    swa.background_pixel = 0xFFFFFF;

    this->setNoteWindow(
            XCreateWindow(this->display, this->parentWindow,0,0,1,1,1, depth,InputOutput,visual,CWBackPixel|CWOverrideRedirect,&swa)
            );
}

Window Note::getNoteWindow() const {
    return this->noteWindow;
}

void Note::setNoteWindow(Window newWindow) {
    this->noteWindow = newWindow;
}

void Note::resizeAndMove(int x, int y, int width, int height) {
    XResizeWindow(this->display,this->getNoteWindow(),width,height);
    XMoveWindow(this->display,this->getNoteWindow(),x,y);
    std::cout << "Resized note window" << std::endl;
    std::cout << this->toString() << std::endl;
}

std::string Note::toString() {
    char buffer[50];
    XWindowAttributes xwa;
    XGetWindowAttributes(this->display,this->getNoteWindow(),&xwa);
    sprintf(buffer,"Size: <%d, %d>, Pos: <%d,%d>", xwa.width,xwa.height,xwa.x,xwa.y);
    return std::string(buffer);
}
