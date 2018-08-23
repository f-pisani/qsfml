#-------------------------------------------------
#
# Project created by QtCreator 2015-07-20T21:31:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QSfml
TEMPLATE = app


SOURCES +=  main.cpp\
            MainWindow.cpp \
            QSFML.cpp \
            RenderWindow.cpp

HEADERS +=  MainWindow.hpp \
            QSFML.hpp \
            RenderWindow.hpp

FORMS   +=  MainWindow.ui

LIBS    +=  -LI:/SFML-2.3/lib

CONFIG  +=  C++11
CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH +=  I:/SFML-2.3/include
DEPENDPATH  +=  I:/SFML-2.3/include
