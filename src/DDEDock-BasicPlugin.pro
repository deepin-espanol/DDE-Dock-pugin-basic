#-------------------------------------------------
#
# Project created by QtCreator 2020-12-01T23:40:21
#
#-------------------------------------------------

QT       += widgets
QT       += core

# la compilacion fallara, debe mover el archivo libbasicplugin.so a la siguiente ruta /usr/lib/dde-dock/plugins/

CONFIG   += plugin

# Nombre del archivo del plugin, tentra la inicial "lib" seguida del nombre escrito en (TARGET = "")
TARGET = basicplugin
TEMPLATE = lib

DEFINES += DDE_BASICDOCK_LIBRARY

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    basicpluginpopup.cpp \
    mainplugin.cpp \
    basicplugin.cpp

HEADERS += \
    basicpluginpopup.h \
    mainplugin.h \
    basicplugin.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    res.qrc

DISTFILES += \
    basicDock.json
