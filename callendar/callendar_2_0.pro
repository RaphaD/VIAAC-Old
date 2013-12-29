TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    TimeHandler.cpp \
    TimeDB.cpp \
    Day.cpp \
    Activity.cpp \
    libFunc.cpp \
    Hour.cpp

QMAKE_CXXFLAGS += -std=c++0x -g

HEADERS += \
    TimeHandler.hpp \
    TimeDB.hpp \
    Day.hpp \
    Activity.hpp \
    libFunc.hpp \
    Hour.hpp

