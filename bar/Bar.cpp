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

Bar::Bar(const std::string& newPosition, std::pair<float,float> size, Display* display) {

    XEvent event;
    int screen = XDefaultScreen(display);
    Window root = XRootWindow(display, screen);
    XWindowAttributes rootWindowAttributes;
    barWindow = *new Window;
    XGetWindowAttributes(display,root, &rootWindowAttributes);
    XSetWindowAttributes swa;
    Visual visual = *DefaultVisual(display, screen);
    swa.override_redirect = True;
    swa.background_pixel = 0x00796b;

    this->position = newPosition;
    if (this->position == "top" || this->position == "left") {
        // Position relative to top should be x: 0 and y: 0 (axis starts top left)
        this->respectivePosition = {0,0};
        this->directionMultiplier = {1,1};
    } else if (this->position == "bottom") {
        // Position relative to bottom should start at x: 0 and y: root.heigth
        this->respectivePosition = {0, rootWindowAttributes.height};
        this->directionMultiplier = {1,-1};
    } else if (this->position == "right") {
        this->respectivePosition = {rootWindowAttributes.width, 0};
        this->directionMultiplier = {-1,1};
    } else {
        return;
    }


    // barWindow = XCreateSimpleWindow(this->display,root,100,100,500,300,1,1,WhitePixel(this->display, screen)),WhitePixel(this->display,screen);
    // XCreateWindow(display, parent, x, y, width, height, border_width, depth, class, visual, valuemask, attributes)
    barWindow = XCreateWindow( display,root,0,0,
                               this->respectivePosition.first + (this->directionMultiplier.first * size.first),
                               this->respectivePosition.second + (this->directionMultiplier.second*size.second),
                               0, DefaultDepth(display,screen), InputOutput, &visual, CWBackPixel|CWOverrideRedirect, &swa);
    // Move window again to force it to ignore window managers
    XSelectInput(display,barWindow, ExposureMask | KeyPressMask);
    // Change attributes and replace override_redirect so window managers don't modify bar's position
    // swa.override_redirect = True;
    // XChangeWindowAttributes(this->display,barWindow,0,&swa);
    /////////XResizeWindow(display,barWindow,rootWindowAttributes.width,50);
   // Get new bar window attributes
    XWindowAttributes barWindowAttributes;
    XGetWindowAttributes(display,barWindow, &barWindowAttributes);
    /////////XMoveWindow(display, barWindow, 0, rootWindowAttributes.height-this->currentPositionMargin.getMarginBottom()-barWindowAttributes.height);
    // XMapWindow(display, barWindow);
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

Window Bar::getAssociatedWindow() {

    return this->barWindow;
}

const std::pair<float, float> &Bar::getSize() const {
    return size;
}

void Bar::setSize(const std::pair<float, float> &size) {
    Bar::size = size;
}


Bar::~Bar() = default;

