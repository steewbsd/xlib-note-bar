//
// Created by kn1ght on 8/8/20.
//

#include "bar/Bar.h"
#include <X11/Xlib.h>
#include <vector>
#include <map>

#ifndef NOTEBAR_PROCESS_MANAGER_H
#define NOTEBAR_PROCESS_MANAGER_H

class ProcessManager {

public:
    explicit ProcessManager(Display *display);
    ~ProcessManager();
    void distributeBars(const std::vector<Bar*> *processCurrentBars);
    void draw();
    static void receiveXNotification(const XEvent *event);
    std::map<std::string, Bar> barMap;
    bool addBar(const std::string &barPosition, Margin *margin);

    [[noreturn]] void run();

private:
    std::vector<Bar> bars;
    Display *display;
    pthread_t processThreadPool[1]{};
    bool checkPositionAlreadyExists(const std::string *positionCheck);

    void listenToXEvents(XEvent *event);
};

#endif //NOTEBAR_PROCESS_MANAGER_H
