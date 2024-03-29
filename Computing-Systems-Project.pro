TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
	main.cpp \
    Administrator.cpp \
    Course.cpp \
    Date.cpp \
    Degree.cpp \
    FDP.cpp \
    Mark.cpp \
    Professor.cpp \
    Resource.cpp \
    Seminar.cpp \
    Student.cpp \
    VirtualCampus.cpp \
    ArrayList.tpp \
    Link_us_res.cpp \
    User.cpp \
    Link_stu_res.cpp \
    Link_prof_res.cpp \
    Utilities.cpp \
    Menu.tpp

HEADERS += \
    Administrator.h \
    Course.h \
    Date.h \
    Degree.h \
    FDP.h \
    Mark.h \
    Professor.h \
    Resource.h \
    Seminar.h \
    Student.h \
    VirtualCampus.h \
    ArrayList.h \
    Link_us_res.h \
    User.h \
    Utilities.h \
    Link_stu_res.h \
    Link_prof_res.h \
    Menu.h
