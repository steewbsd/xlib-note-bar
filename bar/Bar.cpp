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

Bar::Bar(const std::string& newPosition, Margin* optionalMargin, Display* display) {

    this->position = newPosition;
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

    XEvent event;
    int screen = XDefaultScreen(display);
    Window root = XRootWindow(display, screen);
    XWindowAttributes rootWindowAttributes;
    barWindow = *new Window;
    XGetWindowAttributes(display,root, &rootWindowAttributes);
    XSetWindowAttributes swa;
    Visual visual = *DefaultVisual(display, screen);
    swa.override_redirect = True;
    // barWindow = XCreateSimpleWindow(this->display,root,100,100,500,300,1,1,WhitePixel(this->display, screen)),WhitePixel(this->display,screen);
    // XCreateWindow(display, parent, x, y, width, height, border_width, depth, class, visual, valuemask, attributes)
    barWindow = XCreateWindow( display,root,200, 200, 350, 200, 0, DefaultDepth(display,screen), InputOutput, &visual, CWBackPixel|CWOverrideRedirect, &swa);
    // Move window again to force it to ignore window managers
    XSelectInput(display,barWindow, ExposureMask | KeyPressMask);
    // Change attributes and replace override_redirect so window managers don't modify bar's position
    // swa.override_redirect = True;
    // XChangeWindowAttributes(this->display,barWindow,0,&swa);
    XResizeWindow(display,barWindow,rootWindowAttributes.width,50);
   // Get new bar window attributes
   XWindowAttributes barWindowAttributes;
    XGetWindowAttributes(display,barWindow, &barWindowAttributes);
    XMoveWindow(display, barWindow, 0, rootWindowAttributes.height-this->currentPositionMargin.getMarginBottom()-barWindowAttributes.height);
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


Bar::~Bar() = default;

