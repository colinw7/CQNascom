TEMPLATE = app

QT += widgets

TARGET = CQNascom

DEPENDPATH += .

MOC_DIR = .moc

INCLUDEPATH += . ../include

QMAKE_CXXFLAGS += \
-std=c++17 \
-DCQUTIL_IMAGE \

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
../../CQZ80Dbg/include \
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
-L../../CUtil/lib \
-L../../CArgs/lib \
-L../../CZ80/lib \
-L../../CQZ80Dbg/lib \
-L../../CFile/lib \
-L../../CFileUtil/lib \
-L../../CMath/lib \
-L../../COS/lib \
-L../../CStrUtil/lib \
-L../../CRegExp/lib \
-lCQUtil -lCFont -lCImageLib -lCConfig -lCUtil \
-lCArgs -lCZ80 -lCQZ80Dbg -lCFile -lCFileUtil -lCMath -lCOS -lCStrUtil -lCRegExp \
-lpng -ljpeg -ltre
