// Created by kn1ght on 8/8/20.
//
#include <iostream>
#include <vector>
#include <mutex>
#include "Bar.h"
#include "Size.h"
#include "Note.h"

void Bar::add(const Note &new_note) {
    this->noteCollection.push_back(new_note);
}

std::pair<int,int> Bar::calculateProperties(std::pair<float, float> psize) {
    float margin;
    std::pair<int,int> pos;
    std::cout << "Calculating position for bar in: " << this->position << std::endl;
    if (this->position == "top") {
        // Calculate margin (see above)
        this->relativeSize = psize;
        margin = (rootWindowAttributes.width - this->relativeSize.first)/2;
        pos = {margin,0};
    } else if (this->position == "bottom") {
        this->relativeSize = psize;
        margin = (rootWindowAttributes.width - this->relativeSize.first)/2;
        pos = {margin, rootWindowAttributes.height-this->relativeSize.second};
    } else if (this->position == "right") {
        this->relativeSize = {psize.second, psize.first};
        margin = (rootWindowAttributes.height - this->relativeSize.second)/2;
        pos = {rootWindowAttributes.width-this->relativeSize.first,margin};
    } else if (this->position == "left"){
        this->relativeSize = {psize.second, psize.first};
        margin = (rootWindowAttributes.height - this->relativeSize.second)/2;
        pos = {0,margin};
    } else {
        // IF position is unknown, return dedault bottom bar
        this->relativeSize = psize;
        margin = (rootWindowAttributes.width - this->relativeSize.first)/2;
        pos = {margin, rootWindowAttributes.height-this->relativeSize.second};
    }
    return pos;
}

Bar::Bar(const std::string& newPosition, std::pair<float,float> size, Display* display) {
    this->state_hidden = false;
    this->size = size;
    this->display = display;
    XEvent event;
    int screen = XDefaultScreen(display);
    Window root = XRootWindow(display, screen);
    XGetWindowAttributes(display,root, &this->rootWindowAttributes);
    XSetWindowAttributes swa;
    std::pair<float,float> pos;
    float margin;
    Visual visual = *DefaultVisual(display, screen);
    swa.override_redirect = True;
    swa.background_pixel = 0x00796b;

   // FIXME TEST
   int depth = DefaultDepth(this->display,screen);
    std::cout << "DEPTH: " << depth << std::endl;

    // Locate the bar in the center of its respective position. All the examples are considering bar's default position
    // on top.
    // 1.   Substract the total size of the position from the bar size. space = rootWindowAttributes.width - barWindowAttributes.width
    // 2.   Margin from the border to the bar should be exactly half of that remaining space. margin = space / 2
    // 3.   Place the bar exactly ${margin} pixels from the border.
    // 4.   In the case of this example bar, it should be: y= 0 (top left pixel) x=margin

    this->position = newPosition;
    pos = this->calculateProperties(size);

    // barWindow = XCreateSimpleWindow(this->display,root,100,100,500,300,1,1,WhitePixel(this->display, screen)),WhitePixel(this->display,screen);
    // XCreateWindow(display, parent, x, y, width, height, border_width, depth, class, visual, valuemask, attributes)
    std::cout << "BarWindow initially is: " << this->barWindow << std::endl;
    this->setAssociatedWindow(XCreateWindow( display,root,pos.first,pos.second,
                               this->relativeSize.first,
                               this->relativeSize.second,
                               0, depth, InputOutput, &visual, CWBackPixel|CWOverrideRedirect, &swa));
    // Move window again to force it to ignore window managers
    XSelectInput(display,barWindow, ExposureMask | KeyPressMask | FocusChangeMask | EnterWindowMask | ButtonPressMask);
    std::cout << "Created window: " << this->barWindow << std::endl;
    // Change attributes and replace override_redirect so window managers don't modify bar's position
    // swa.override_redirect = True;
    // XChangeWindowAttributes(this->display,barWindow,0,&swa);
    /////////XResizeWindow(display,barWindow,rootWindowAttributes.width,50);
   // Get new bar window attributes
    /////////XMoveWindow(display, barWindow, 0, rootWindowAttributes.height-this->currentPositionMargin.getMarginBottom()-barWindowAttributes.height);
    // XMapWindow(display, barWindow);
    // FIXME
    this->add(Note(this->display,this->getAssociatedWindow()));
    this->add(Note(this->display,this->getAssociatedWindow()));
    this->add(Note(this->display,this->getAssociatedWindow()));
    this->add(Note(this->display,this->getAssociatedWindow()));
}


// This will return the main size of every note (if position requires notes to be vertically aligned the size will
// represent the height of the notes, in case of horizontal it will represent the width).
Size Bar::distributeAllNotes(const float *MAX_SIZE) {

    // Get number of notes

    Size tmpSize = Size(0,0);
    // Divide max available space with the number of notes to get the size per note (spn) value
    // float spnX = (*MAX_SIZE-this->margin->getMarginLeft()-this->margin->getMarginRight()) /
    return Size(0,0);

}

std::string Bar::getPosition() const {
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

void Bar::resize(std::pair<int, int> newSize) {
    std::cout << "Resizing window: " << this->barWindow << " to: " << newSize.first << "," << newSize.second << std::endl;
    //XUnmapWindow(this->display, this->getAssociatedWindow());
    std::pair<int,int> pos = this->calculateProperties(newSize);
    XResizeWindow(this->display,this->getAssociatedWindow(), this->relativeSize.first,this->relativeSize.second);
    XMoveWindow(this->display,this->getAssociatedWindow(),pos.first,pos.second);
    XWindowAttributes xwa;
    XGetWindowAttributes(this->display,this->getAssociatedWindow(), &xwa);
    std::cout << "Resized window to: " << xwa.width << "," << xwa.height << std::endl;
}

void Bar::setAssociatedWindow(Window win) {
    this->barWindow = win;
}

void Bar::toggleHidden() {
    std::cout << "Toggling hidden state to: " << !this->state_hidden << std::endl;
    this->state_hidden = !this->state_hidden;
    if (this->state_hidden) {
         this->resize({this->size.first,this->size.second/2});
    } else {
        this->resize(this->size);
    }
}

void Bar::moveTo(std::string nPos) {
    // FIXME
    std::cout << "Changed position from: " << this->position;
    this->position = nPos;
    std::cout << " to: " << this->position << std::endl;
    this->resize(this->size);
}

Note* Bar::getNoteByIndex(const int &index) {
    if (index >= this->noteCollection.size() || index < 0) {
        return nullptr;
    }
    return &this->noteCollection[index];
}

void Bar::mapAll() {
    XMapWindow(this->display, this->getAssociatedWindow());
    // Draw notes after the bar itself
    // Get the reference x position (for bottom bar)
    XWindowAttributes xwa;
    XGetWindowAttributes(this->display,this->getAssociatedWindow(),&xwa);
    std::cout << "Mapping all notes" << std::endl;
    int width = this->getNoteWidth();
    int startingX = xwa.x;
    for (int i = 0; i < this->noteCollection.size(); i++) {
        // Place note in the middle for now
        std::cout << "Mapping note with index " << i << std::endl;
        this->getNoteByIndex(i)->resizeAndMove(width*i, 0,width,xwa.height);
        XMapWindow(this->display, this->getNoteByIndex(i)->getNoteWindow());
    }

}

int Bar::getNoteWidth() {
    XWindowAttributes xwa;
    XGetWindowAttributes(this->display,this->getAssociatedWindow(),&xwa);
    return int(
            xwa.width / this->noteCollection.size()
            );
}


Bar::~Bar() = default;

