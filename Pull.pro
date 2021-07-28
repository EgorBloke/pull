QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Ball.cpp \
    Coord.cpp \
    Cue.cpp \
    MyScene.cpp \
    Player.cpp \
    Pocket.cpp \
    Point.cpp \
    Table.cpp \
    Track.cpp \
    V.cpp \
    main.cpp \
    mainwindow.cpp \
    mygraphicsview.cpp

HEADERS += \
    Ball.h \
    Coord.h \
    Cue.h \
    MyScene.h \
    Player.h \
    Pocket.h \
    Point.h \
    Table.h \
    Track.h \
    V.h \
    mainwindow.h \
    mygraphicsview.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
