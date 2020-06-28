TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
QT += widgets
CONFIG += qt
QT += core

SOURCES += \
        ExtremePoints.cpp \
        main.cpp \
        renderarea.cpp \
        window.cpp

DISTFILES +=

HEADERS += \
    ExtremePoints.h \
    main.cpp.autosave \
    renderarea.h \
    window.h

RESOURCES += \
    Image.qrc \
    Image.qrc
