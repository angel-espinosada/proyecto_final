QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    enemigo.cpp \
    escenario_juego.cpp \
    imagenes/imagenes.cpp \
    juego.cpp \
    jugador.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    nivel.cpp \
    nivel_1.cpp \
    nivel_2.cpp \
    nivel_3.cpp \
    tubo.cpp \
    tubo_caliente.cpp \
    tubo_frio.cpp

HEADERS += \
    enemigo.h \
    escenario_juego.h \
    juego.h \
    jugador.h \
    mainwindow.h \
    menu.h \
    nivel.h \
    nivel_1.h \
    nivel_2.h \
    nivel_3.h \
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

DISTFILES += \
    imagenes/fondo_nivel2.PNG
