
QT       += core gui
QT += printsupport
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ButtonHelloWorld
TEMPLATE = app


SOURCES = main.cpp\
        mainwindow.cpp \
    neural_web.cpp \
  scribblearea.cpp

HEADERS = mainwindow.h \ 
scribblearea.h \
neural_web.h \
arr_scale.h

  # install target.path = $$[QT_INSTALL_EXAMPLES]/touch/fingerpaint sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS fingerpaint.pro sources.path = $$[QT_INSTALL_EXAMPLES]/touch/fingerpaint INSTALLS += target sources symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri) maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri) symbian: warning(This example might not fully work on Symbian platform) maemo5: warning(This example might not fully work on Maemo platform) simulator: warning(This example might not fully work on Simulator platform)

DISTFILES += \
    best_weights.txt

DEPENDPATH = /home/fp/Android/Sdk/ndk-bundle/sources/cxx-stl/gnu-libstdc++/4.9/include

# - setup the 'make install' step
samples.path = /assets
samples.files += /best_weights.txt
samples.depends += FORCE

INSTALLS += samples

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

RESOURCES += \
    weights.qrc



INCLUDEPATH += .
