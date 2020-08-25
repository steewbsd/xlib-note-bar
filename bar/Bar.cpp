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

void Bar::calculateProperties(const std::string& position, const std::pair<float, float> &relativeSize, std::pair<float, float> *size) {

}

Bar::Bar(const std::string& newPosition, std::pair<float,float> size, Display* display) {

    XEvent event;
    int screen = XDefaultScreen(display);
    Window root = XRootWindow(display, screen);
    XWindowAttributes rootWindowAttributes;
    barWindow = *new Window;
    XGetWindowAttributes(display,root, &rootWindowAttributes);
    XSetWindowAttributes swa;
    std::pair<float,float> pos;
    float margin;
    Visual visual = *DefaultVisual(display, screen);
    swa.override_redirect = True;
    swa.background_pixel = 0x00796b;

    // TODO I should make it so the start of the X root coordinates corresponds to usual coords (bottom left)
    // TODO Using top left is a bit confusing.

    // Locate the bar in the center of its respective position. All the examples are considering bar's default position
    // on top.
    // 1.   Substract the total size of the position from the bar size. space = rootWindowAttributes.width - barWindowAttributes.width
    // 2.   Margin from the border to the bar should be exactly half of that remaining space. margin = space / 2
    // 3.   Place the bar exactly ${margin} pixels from the border.
    // 4.   In the case of this example bar, it should be: y= 0 (top left pixel) x=margin

    this->position = newPosition;
    if (this->position == "top") {
        // Calculate margin (see above)
        this->relativeSize = size;
        margin = (rootWindowAttributes.width - this->relativeSize.first)/2;
        pos = {margin,0};
    } else if (this->position == "bottom") {
        this->relativeSize = size;
        margin = (rootWindowAttributes.width - this->relativeSize.first)/2;
        pos = {margin, rootWindowAttributes.height-this->relativeSize.second};
    } else if (this->position == "right") {
        this->relativeSize = {size.second, size.first};
        margin = (rootWindowAttributes.height - this->relativeSize.second)/2;
        pos = {rootWindowAttributes.width-this->relativeSize.first,margin};
    } else if (this->position == "left"){
        this->relativeSize = {size.second, size.first};
        margin = (rootWindowAttributes.height - this->relativeSize.second)/2;
        pos = {0,margin};
    } else {
        return;
    }


    // barWindow = XCreateSimpleWindow(this->display,root,100,100,500,300,1,1,WhitePixel(this->display, screen)),WhitePixel(this->display,screen);
    // XCreateWindow(display, parent, x, y, width, height, border_width, depth, class, visual, valuemask, attributes)
    barWindow = XCreateWindow( display,root,pos.first,pos.second,
                               this->relativeSize.first,
                               this->relativeSize.second,
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

