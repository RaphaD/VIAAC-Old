######################################################################
# Automatically generated by qmake (2.01a) Sat Dec 14 17:13:53 2013
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .

include(/usr/include/qextserialport/src/qextserialport.pri) #for qextserialport !

# Input
QMAKE_CXXFLAGS += -std=c++0x -g
LIBS += -lfmod -pthread
HEADERS += PortSender.hpp \
    MusicMaker.hpp \
    Song.hpp

SOURCES += main.cpp PortSender.cpp \
    MusicMaker.cpp \
    statFile.cpp \
    Song.cpp \
    libTreater.cpp
