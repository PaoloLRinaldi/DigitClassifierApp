
QT           += core gui
QT           += printsupport
CONFIG       += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET        = ButtonHelloWorld
TEMPLATE      = app

HEADERS       = mainwindow.h \
                scribblearea.h \
                arr_scale.h \
                neural_web.h
SOURCES       = main.cpp \
                mainwindow.cpp \
                scribblearea.cpp \
                neural_web.h

# install target.path = $$[QT_INSTALL_EXAMPLES]/touch/fingerpaint sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS fingerpaint.pro sources.path = $$[QT_INSTALL_EXAMPLES]/touch/fingerpaint INSTALLS += target sources  symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri) maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)  symbian: warning(This example might not fully work on Symbian platform) maemo5: warning(This example might not fully work on Maemo platform) simulator: warning(This example might not fully work on Simulator platform)
