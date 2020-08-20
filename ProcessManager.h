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
    bool addBar(const std::string *barPosition);
    ~ProcessManager();
    void distributeBars(const std::vector<Bar*> *processCurrentBars);
    void draw();
    static void receiveXNotification(const XEvent *event);
    std::map<std::string, Bar> barMap;

    void run();

private:
    std::vector<Bar> bars;
    [[noreturn]] static void listenToXEvents(ProcessManager* pm);
    Display *display;
    pthread_t processThreadPool[1]{};


    bool checkPositionAlreadyExists(const std::string *positionCheck);

};

#endif //NOTEBAR_PROCESS_MANAGER_H
