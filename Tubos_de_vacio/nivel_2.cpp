#include "nivel_2.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QObject>


nivel_2::nivel_2(QGraphicsScene *escena)
{
    this->escena = escena;
    qDebug() << "Constructor nivel_2 - INICIO";
}

void nivel_2::cargarEscenario()
{
    qDebug() << "cargarEscenario - INICIO";
    escenario = new Escenario_juego(0, 0, 800, 600, Qt::darkGray);
    qDebug() << "Escenario creado";
    escena->addItem(escenario);
    qDebug() << " cargarEscenario - FIN";
}

void nivel_2::cargarFondo()
{
    qDebug() << "  cargarFondo - IN";
    // usa el mismo formato del nivel 1
    QGraphicsPixmapItem *fondo = escenario->crearFondo(
        ":/imagenes/fondo_nivel2.PNG",
        0, 0, 800, 600
        );
    fondo->setZValue(-10);
    escena->addItem(fondo);
     qDebug() << " cargarFondo - finnnn";
}

void nivel_2::cargarSuelo()
{
    qDebug() << "cargarSuelo - INICIO";
    QGraphicsRectItem *suelo = escenario->crearSuelo(0, 550, 800, 50);
    escena->addItem(suelo);
}

void nivel_2::cargarTubos()
{
    int alturaSuelo = 550;
    int altoTubo = 150;

    tuboCaliente = new Tubo_caliente(700, alturaSuelo - altoTubo, 50, 150);
    escena->addItem(tuboCaliente);

    tuboFrio = new Tubo_Frio(700, alturaSuelo - altoTubo, 50, 150);
    tuboFrio->setVisible(false);   // empieza oculto
    escena->addItem(tuboFrio);
}

void nivel_2::cargarObstaculos()
{
     qDebug() << "cargarObstaculos - INICIO";
    QGraphicsRectItem *caja = new QGraphicsRectItem(300, 500, 60, 50);
    caja->setBrush(QColor(139,69,19));
    escena->addItem(caja);
}

void nivel_2::cargarJugador(Juego *j)
{
    juego = j;

    jugador = new Jugador();
    //jugador->setNivel2(this);  // ← luego lo hacemos, hoy no

    jugador->setPos(100, 475);
    escena->addItem(jugador);

    // Timer para actualizar el nivel
    QTimer *timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout, this, &nivel_2::actualizar);
    timer->start(50);   // 20 FPS
}

void nivel_2::actualizar()
{
    tiempoRestante--;

    // Por ahora solo lo vemos en consola:
    qDebug() << "Tiempo restante:" << tiempoRestante;
}

void nivel_2::setJuego(Juego *j)
{
    this->juego = j;
}
