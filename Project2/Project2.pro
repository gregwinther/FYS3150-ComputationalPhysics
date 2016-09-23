TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib

SOURCES += main.cpp \
    jacobiMethod.cpp

LIBS += -llapack -lblas -larmadillo

HEADERS += \
    jacobimethod.h
