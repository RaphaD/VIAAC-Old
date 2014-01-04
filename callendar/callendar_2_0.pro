TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += TimeHandler.cpp \
    TimeDB.cpp \
    Day.cpp \
    Activity.cpp \
    libFunc.cpp \
    Hour.cpp \
	CronTab.cpp \
	Event.cpp \
	DataBase.cpp \
	main.cpp

QMAKE_CXXFLAGS += -std=c++0x -g

HEADERS += \
    TimeHandler.hpp \
    TimeDB.hpp \
    Day.hpp \
    Activity.hpp \
    libFunc.hpp \
    Hour.hpp \
	CronTab.hpp \
	Event.hpp \
	DataBase.hpp \
	C_MACRO.hpp \

