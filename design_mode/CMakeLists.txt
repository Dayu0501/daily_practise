cmake_minimum_required(VERSION 3.16)
project(design_mode)

set(CMAKE_CXX_STANDARD 14)

add_executable(design_mode
        Component_collaboration/observer/FileSplitter1.h
        Component_collaboration/observer/FileSplitter2.h
        Component_collaboration/observer/MainForm1.cpp
        Component_collaboration/observer/MainForm2.cpp
        Component_collaboration/strategy/strategy1.cpp
        Component_collaboration/strategy/strategy2.cpp
        Component_collaboration/template_method/template1_app.cpp
        Component_collaboration/template_method/template1_lib.h
        Component_collaboration/template_method/template2_app.cpp
        Component_collaboration/template_method/template2_lib.h Component_collaboration/observer/test/master.h Component_collaboration/observer/test/observer.cpp Component_collaboration/observer/test/head.h Component_collaboration/observer/test/new_observer.cpp)

add_executable(observer Component_collaboration/observer/test/observer.cpp)
add_executable(new_observer Component_collaboration/observer/test/new_observer.cpp)