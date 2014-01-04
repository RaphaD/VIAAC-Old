######################################################################
# Automatically generated by qmake (2.01a) Mon Dec 30 13:25:52 2013
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . callendar music
INCLUDEPATH += . callendar music

include(/usr/include/qextserialport/src/qextserialport.pri) #for qextserialport !
# Input
QMAKE_CXXFLAGS += -std=c++0x -g
LIBS += -lfmod

# Input
HEADERS += callendar/Activity.hpp \
           callendar/Day.hpp \
           callendar/Hour.hpp \
           callendar/libFunc.hpp \
           callendar/TimeDB.hpp \
           callendar/TimeHandler.hpp \
           music/libTreater.hpp \
           music/MusicMaker.hpp \
           music/PortSender.hpp \
           music/Song.hpp \
    callendar/CronTab.hpp \
    callendar/Event.hpp \
    callendar/DataBase.hpp \
    callendar/C_MACRO.hpp \
    music/statFile.hpp
SOURCES += main.cpp \
           callendar/Activity.cpp \
           callendar/Day.cpp \
           callendar/Hour.cpp \
           callendar/libFunc.cpp \
           callendar/TimeDB.cpp \
           callendar/TimeHandler.cpp \
           music/MusicMaker.cpp \
           music/PortSender.cpp \
           music/Song.cpp \
           music/statFile.cpp \
    music/libTreater.cpp \
    callendar/CronTab.cpp \
    callendar/Event.cpp \
    callendar/DataBase.cpp