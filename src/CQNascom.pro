TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += . ../include

# Input
SOURCES += \
CQNascom.cpp \
CNascom.cpp \
CQUtil.cpp \

HEADERS += \
CQNascom.h \
CNascom.h \
CNascomChars.h \
CNascomKeyMap.h \
CNascomScreenMap.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += ../include

unix:LIBS += \
-L$$LIB_DIR \
-lCArgs -lCZ80 -lCFile -lCOS -lCStrUtil
