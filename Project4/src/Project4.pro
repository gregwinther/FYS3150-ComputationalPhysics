TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib

SOURCES += main.cpp \
	ising.cpp

HEADERS += ising.h

LIBS += -llapack -lblas -larmadillo
