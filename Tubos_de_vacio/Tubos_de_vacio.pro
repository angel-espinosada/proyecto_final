QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    enemigo.cpp \
    imagenes/imagenes.cpp \
    juego.cpp \
    jugador.cpp \
    main.cpp \
    mainwindow.cpp \
    nivel.cpp \
    nivel_1.cpp \
    tubo.cpp \
    tubo_caliente.cpp \
    tubo_frio.cpp

HEADERS += \
    enemigo.h \
    juego.h \
    jugador.h \
    mainwindow.h \
    nivel.h \
    nivel_1.h \
    tubo.h \
    tubo_caliente.h \
    tubo_frio.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
