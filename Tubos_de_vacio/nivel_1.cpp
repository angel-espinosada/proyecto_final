#include "nivel_1.h"



nivel_1::nivel_1(QGraphicsScene *escena)
{
    this->escena = escena;
}

void nivel_1::cargarEscenario()
{
    escenario = new Escenario_juego(0, 0, 800, 600, Qt::lightGray);
    escena->addItem(escenario);
}

void nivel_1::cargarSuelo()
{
    QGraphicsRectItem *suelo = escenario->crearSuelo(0, 550, 800, 50);
    escena->addItem(suelo);
}

void nivel_1::cargarTubos()
{
    //Temporarar para calcular Y
    int alturaSuelo = 550;
    int altoTubo = 150;
    int y = alturaSuelo - altoTubo; // 400 → justo sobre el suelo
    Tubo_caliente *t1 = new Tubo_caliente(730, y, 50, 150);
    escena->addItem(t1);

    Tubo_Frio *t2 = new Tubo_Frio(660, y, 50, 150);
    escena->addItem(t2);
}

void nivel_1::cargarJugador()
{
    Jugador *jug = new Jugador();

    // y = 550 piso - 75 (alto jugador) = 475
    jug->setPos(100, 475);

    escena->addItem(jug);
}
