######################################################################
# Automatically generated by qmake (2.01a) Sat Dec 14 17:13:53 2013
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

QMAKE_CXXFLAGS += -std=c++11 -g
QMAKE_CC = gcc-4.8
QMAKE_CXX = g++-4.8

LIBS += -lfmod -pthread

# include(/usr/include/qextserialport/src/qextserialport.pri) #for qextserialport !

# Input
HEADERS += PortSender.hpp \
    MusicMaker.hpp \
    Song.hpp \
    M_MACRO.hpp \
    statFile.hpp

SOURCES += PortSender.cpp \
    MusicMaker.cpp \
    statFile.cpp \
    Song.cpp \
    libTreater.cpp\
    main.cpp
