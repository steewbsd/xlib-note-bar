//
// Created by kn1ght on 8/8/20.
//

#include "ProcessManager.h"
#include "bar/Bar.h"
#include <X11/Xlib.h>
#include <algorithm>
#include <iostream>
#include <pthread.h>

typedef void *(*THREADFUNCPTR)(void *);
ProcessManager::~ProcessManager() = default;

ProcessManager::ProcessManager(Display *display) {
  this->display = display;
}

[[noreturn]] void ProcessManager::listenToXEvents(ProcessManager *pm) {
  // TODO
  XEvent *event = nullptr;
  for (;;) {
    std::cout << "Listening to X Events..." << std::endl;
    XNextEvent(pm->display, event);
    // ProcessManager::receiveXNotification(event);
  }
}

void ProcessManager::distributeBars(const std::vector<Bar *> *processCurrentBars ) {
    /*for (int barNum = 0; barNum < this->bars.size(); barNum++) {
    }*/


  // TODO replace this when proven it works (it will just spawn a default bar on the bottom of the screen)
    
}

bool ProcessManager::checkPositionAlreadyExists(
    const std::string *positionCheck) {
  return std::any_of(this->bars.begin(), this->bars.end(),
                     [positionCheck](const Bar &i) {
                       return i.getPosition() == *positionCheck;
                     });
}

bool ProcessManager::addBar(const std::string *barPosition) {
  if (ProcessManager::checkPositionAlreadyExists(barPosition)) {
    return false;
  }
  Margin margin = Margin(nullptr, nullptr, nullptr, nullptr);
  Bar newBar = Bar(barPosition, &margin);
  this->bars.emplace_back(newBar);
  this->barMap.emplace(*barPosition,newBar);
  return true;
}

void ProcessManager::receiveXNotification(const XEvent *event) {
  printf("%d", event->xkey.keycode);
}

// Run program forever (until stopped by user or signal)
void ProcessManager::run() {
    // Add thread for handling X key presses and key combinations
    /* pthread_create(&this->processThreadPool[0], nullptr,
                 (THREADFUNCPTR)ProcessManager::listenToXEvents, this);
    */
    ProcessManager::listenToXEvents(this);
}

void ProcessManager::draw() {
    std::cout << "Drawing window" << std::endl;
    XEvent event;
    int screen = XDefaultScreen(this->display);
    Window root = XRootWindow(this->display, screen);
    XWindowAttributes rootWindowAttributes;
    Window barWindow = *new Window;
    XGetWindowAttributes(this->display,root, &rootWindowAttributes);
    XSetWindowAttributes swa;
    Visual visual = *DefaultVisual(this->display, screen);
    visual.red_mask = 597;
    visual.green_mask = 528;
    visual.blue_mask = 52;
    swa.override_redirect = True;
    // barWindow = XCreateSimpleWindow(this->display,root,100,100,500,300,1,1,WhitePixel(this->display, screen)),WhitePixel(this->display,screen);
    // XCreateWindow(display, parent, x, y, width, height, border_width, depth, class, visual, valuemask, attributes)
    barWindow = XCreateWindow( this->display,root,200, 200, 350, 200, 0, DefaultDepth(this->display,screen), InputOutput, &visual, CWBackPixel|CWOverrideRedirect, &swa);
    // Move window again to force it to ignore window managers
    XSelectInput(this->display,barWindow, ExposureMask | KeyPressMask);
    // Change attributes and replace override_redirect so window managers don't modify bar's position
    // swa.override_redirect = True;
    // XChangeWindowAttributes(this->display,barWindow,0,&swa);
    XResizeWindow(this->display,barWindow,rootWindowAttributes.width,50);
    XMoveWindow(this->display, barWindow, 0, rootWindowAttributes.height -50);
    XMapWindow(this->display, barWindow);

    for (;;) {
        XNextEvent(this->display, &event);
    }
}
