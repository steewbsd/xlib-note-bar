//
// Created by kn1ght on 8/8/20.
//

#include "ProcessManager.h"
#include "bar/Bar.h"
#include <X11/Xlib.h>
#include <algorithm>
#include <iostream>

// typedef void *(*THREADFUNCPTR)(void *);
ProcessManager::~ProcessManager() = default;

ProcessManager::ProcessManager(Display *display) {
  this->display = display;
}

void ProcessManager::listenToXEvents(XEvent *event) {
    // Create a new any variable which holds the interface XAnyEvent. This contains info about the processed event,
    // most important one for this case scenario is to know which window received the event.
    XAnyEvent any = event->xany;
    std::cout << "Received XEvent " << event << std::endl;
        switch (event->type) {
            case KeyPress:
                std::cout << "Received KeyPress event with keycode:" << event->xkey.keycode << std::endl;
               if (event->xkey.keycode == 80) {
                    std::cout << "numKey 8 pressed" << std::endl;
                }
               break;
            case ButtonPress:
                // TODO separate keycodes
                std::cout << "Received ButtonPress event with keycode:" << event->xkey.keycode << std::endl;
                // HERE ONLY GENERAL BAR EVENTS WILL BE HANDLED, FOR SPECIFIC NOTE EVENTS GO BELOW
                if (event->xkey.keycode == 1) {
                    this->barMap.find(any.window)->second.toggleHidden();
                } else if (event->xkey.keycode == 3) {
                    srand(time(nullptr));
                    int num = rand() % 10 + 1;
                    this->barMap.find(any.window)->second.moveTo(num>5?"top":"bottom");
                } else if (event->xkey.keycode == 2) {
                    //this->barMap.find(any.window)->second.
                }
                this->draw();
                break;
            case EnterNotify:
                std::cout << "Entered window boundaries in window: " << any.window << std::endl;
                // FIXME ----------------------------------------------------------------------------
                break;
            default:
                return;
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

bool ProcessManager::addBar(const std::string &barPosition, std::pair<float,float> size) {
  if (ProcessManager::checkPositionAlreadyExists(&barPosition)) {
    return false;
  }
  Bar newBar = Bar(barPosition, size, this->display);
  this->bars.emplace_back(newBar);
  this->barMap.emplace(newBar.getAssociatedWindow(),newBar);
  // Update bar map
  this->draw();
  return true;
}

// Run program forever (until stopped by user or signal)
[[noreturn]] void ProcessManager::run() {
    // Add thread for handling X key presses and key combinations
    this->addBar("bottom", {1000,70});
    /* pthread_create(&this->processThreadPool[0], nullptr,
                 (THREADFUNCPTR)listenToXEvents, this); */

    // Main event loop
    for(;;) {
        XEvent event;
        XNextEvent(this->display, &event);
        listenToXEvents(&event);
    }
}

void ProcessManager::draw() {
    std::cout << "Drawing window" << std::endl;
    auto place = [&](std::pair<Window, Bar> map){
        map.second.mapAll();
    };
    std::for_each(this->barMap.begin(), this->barMap.end(), place);
}



