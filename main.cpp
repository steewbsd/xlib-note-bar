#include <iostream>
#include <X11/Xlib.h>
#include "ProcessManager.h"

int main() {
   Display *display = XOpenDisplay(nullptr);
   if (display == nullptr) {
       std::cout << "Failed to open X display connection...\n"
        << std::endl;
       // Return status -1, program failed to open successfully
       exit(1);
   }
   std::cout << "X display opened without errors.\n";
   // Temporary debug with default bottom bar
    ProcessManager pm = ProcessManager(display);
    pm.draw();
}
