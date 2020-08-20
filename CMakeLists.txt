cmake_minimum_required(VERSION 3.18)
project(notebar)

set(CMAKE_CXX_STANDARD 11)

find_package(X11 REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(notebar main.cpp bar/Bar.h bar/Bar.cpp bar/Note.h ProcessManager.h bar/Note.cpp interfaces/IPosition.h ProcessManager.cpp config.h config.cpp bar/Size.h bar/Size.cpp bar/Margin.h bar/Margin.cpp)
target_link_libraries(notebar X11 Threads::Threads)
