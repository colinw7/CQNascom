TEMPLATE = app

QT += widgets

TARGET = CQNascom

DEPENDPATH += .

MOC_DIR = .moc

INCLUDEPATH += . ../include

QMAKE_CXXFLAGS += -std=c++11

CONFIG += debug

# Input
SOURCES += \
CQNascom.cpp \
CNascom.cpp \

HEADERS += \
CQNascom.h \
CNascom.h \
CNascomChars.h \
CNascomKeyMap.h \
CNascomScreenMap.h \

DESTDIR     = ../bin
OBJECTS_DIR = ../obj
LIB_DIR     = ../lib

INCLUDEPATH += \
. ../include \
../../CQUtil/include \
../../CZ80/include \
../../CArgs/include \
../../CFont/include \
../../CImageLib/include \
../../CFile/include \
../../COS/include \
../../CUtil/include \
../../CMath/include \
../../CStrUtil/include \

unix:LIBS += \
-L$$LIB_DIR \
-L../../CQUtil/lib \
-L../../CFont/lib \
-L../../CImageLib/lib \
-L../../CConfig/lib \
-L../../CArgs/lib \
-L../../CZ80/lib \
-L../../CFile/lib \
-L../../COS/lib \
-L../../CStrUtil/lib \
-L../../CRegExp/lib \
-lCQUtil -lCFont -lCImageLib -lCConfig \
-lCArgs -lCZ80 -lCFile -lCOS -lCStrUtil -lCRegExp \
-lpng -ljpeg -ltre
