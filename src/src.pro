include(../defaults.pri)

QT       += core network xml widgets webenginewidgets
TEMPLATE  = lib
CONFIG    += warn_on lib c++11 stl

#Comment the next line in when use QTMultimedia
CONFIG    += support_qtav

support_qtav {
    DEFINES += SUPPORT_QTAV
    QT      += avwidgets
} else {
    QT += multimedia multimediawidgets
}



TARGET = garlic
DESTDIR = ../lib
LIBS += -L../ext -lquazip -lz

SOURCES += \
    smilparser/head.cpp \
    smilparser/media.cpp \
    smilparser/image.cpp \
    smilparser/seq.cpp \
    smilparser/video.cpp \
    smilparser/web.cpp \
    smilparser/audio.cpp \
    smilparser/body.cpp \
    smilparser/par.cpp \
    smilparser/excl.cpp \
    files/downloader.cpp \
    smilparser/timings/timing.cpp \
    smilparser/timings/clock_value.cpp \
    smilparser/priorityclass.cpp \
    smilparser/factory.cpp \
    smilparser/container.cpp \
    smilparser/base.cpp \
    smilparser/base_timing.cpp \
    tools/configuration.cpp \
    files/file_manager.cpp \
    smilparser.cpp \
    smilparser/prefetch.cpp \
    smilparser/tools/shuffle.cpp \
    files/index.cpp \
    tools/mediadecoderwrapper.cpp \
    tools/mediaviewwrapper.cpp
HEADERS += tools/configuration.h \
    smilparser.h \
    smilparser/head.h \
    smilparser/image.h \
    smilparser/media.h \
    smilparser/seq.h \
    smilparser/video.h \
    smilparser/web.h \
    smilparser/audio.h \
    smilparser/body.h \
    smilparser/par.h \
    smilparser/excl.h \
    files/downloader.h \
    smilparser/timings/timing.h \
    smilparser/timings/clock_value.h \
    smilparser/priorityclass.h \
    smilparser/factory.h \
    smilparser/container.h \
    smilparser/base.h \
    smilparser/base_timing.h \
    files/file_manager.h \
    smilparser/prefetch.h \
    smilparser/tools/shuffle.h \
    files/index.h \
    tools/mediadecoderwrapper.h \
    tools/mediaviewwrapper.h

