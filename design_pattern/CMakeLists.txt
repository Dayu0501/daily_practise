cmake_minimum_required(VERSION 3.16)
project(design_pattern)

set(CMAKE_CXX_STANDARD 14)

include_directories(Component_collaboration/observer)
include_directories(Component_collaboration/observer/test)
include_directories(Component_collaboration/template_method)
include_directories(Object_create/abstract_factory)
include_directories(Object_create/factory_method)

aux_source_directory(Status_change/status STATUS)
aux_source_directory(Status_change/memento MEMENTO)
aux_source_directory(Data_structor/chainOfResposibility CHAINOFRESPOSIBILITY)
aux_source_directory(Object_performance/flyweight FLYWEIGHT)
aux_source_directory(Object_performance/singleton SINGLETON)

add_executable(design_pattern
        Component_collaboration/observer/test/head.h
        Component_collaboration/observer/test/master.h
        Component_collaboration/observer/test/new_observer.cpp
        Component_collaboration/observer/test/observer.cpp
        Component_collaboration/observer/FileSplitter1.h
        Component_collaboration/observer/FileSplitter2.h
        Component_collaboration/observer/MainForm1.cpp
        Component_collaboration/observer/MainForm2.cpp
        Component_collaboration/strategy/strategy1.cpp
        Component_collaboration/strategy/strategy2.cpp
        Component_collaboration/template_method/template1_app.cpp
        Component_collaboration/template_method/template1_lib.h
        Component_collaboration/template_method/template2_app.cpp
        Component_collaboration/template_method/template2_lib.h
        Object_create/abstract_factory/EmployeeDAO1.cpp
        Object_create/abstract_factory/EmployeeDAO2.cpp
        Object_create/abstract_factory/EmployeeDAO3.cpp
        Object_create/abstract_factory/head.h
        Object_create/builder/builder.cpp
        Object_create/factory_method/FileSplitter1.cpp
        Object_create/factory_method/FileSplitter2.cpp
        Object_create/factory_method/head.h
        Object_create/factory_method/ISplitterFactory.cpp
        Object_create/factory_method/MainForm1.cpp
        Object_create/factory_method/MainForm2.cpp
        Object_create/prototype/Client.cpp
        Object_create/prototype/ConcretePrototype.cpp
        Object_create/prototype/Prototype.cpp
        Single_responsibility/brigde/bridge1.cpp
        Single_responsibility/brigde/bridge2.cpp
        Single_responsibility/decorator/decorator1.cpp
        Single_responsibility/decorator/decorator2.cpp
        Single_responsibility/decorator/decorator3.cpp
        ${STATUS} ${MEMENTO} ${CHAINOFRESPOSIBILITY} ${FLYWEIGHT} ${SINGLETON})