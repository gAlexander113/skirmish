TARGET = Cars_race
TEMPLATE = app
QT += opengl widgets



SOURCES += \
    main.cpp \
    skirmish.cpp \
    road.cpp \
    car.cpp \
    textureloader.cpp

HEADERS += \
    skirmish.h \
    road.h \
    car.h \
    share.h \
    textureloader.h \


INCLUDEPATH += $$PWD/lib/DevIl
DEPENDPATH += $$PWD/lib/DevIl

win32: LIBS += -L$$PWD/lib/DevIl/ -lDevIL \
    -L$$PWD/lib/DevIl/ -lILU \
    -L$$PWD/lib/DevIl/ -lILUT

win32: PRE_TARGETDEPS += $$PWD/lib/DevIl/DevIL.lib \
    $$PWD/lib/DevIl/ILU.lib \
    $$PWD/lib/DevIl/ILUT.lib \


