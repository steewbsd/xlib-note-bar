//
// Created by kn1ght on 8/8/20.
//
#include <iostream>
#include <vector>
#include <mutex>
#include "Bar.h"
#include "Size.h"
#include "Note.h"

void Bar::add(const Note *new_note) {
    this->noteCollection.push_back(*new_note);
}

std::vector<Note> Bar::notes() {
    return this->noteCollection;
}

std::pair<int,int> Bar::calculateProperties(std::pair<float, float> size) {
    float margin;
    std::pair<int,int> pos;
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
        // IF position is unknown, return dedault bottom bar
        this->relativeSize = size;
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
                               0, DefaultDepth(display,screen), InputOutput, &visual, CWBackPixel|CWOverrideRedirect, &swa));
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
    XResizeWindow(this->display,this->getAssociatedWindow(), newSize.first,newSize.second);
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
    // FIXME Temporary test, bar just moves counterclockwise
    this->position = nPos;
    std::pair<int,int> pos = this->calculateProperties(this->size);
    XMoveWindow(this->display,this->getAssociatedWindow(),pos.first,pos.second);
}


Bar::~Bar() = default;

