#include "nivel_1.h"



nivel_1::nivel_1(QGraphicsScene *escena)
{
    this->escena = escena;
}

void nivel_1::cargarEscenario()
{
    escenario = new Escenario_juego(0, 0, 800, 400, Qt::lightGray);
    escena->addItem(escenario);
}

void nivel_1::cargarSuelo()
{
    QGraphicsRectItem *suelo = escenario->crearSuelo(0, 350, 800, 50);
    escena->addItem(suelo);
}

void nivel_1::cargarTubos()
{
    Tubo_caliente *t1 = new Tubo_caliente(120, 200, 50, 150);
    escena->addItem(t1);

    Tubo_Frio *t2 = new Tubo_Frio(200, 200, 50, 150);
    escena->addItem(t2);
}
