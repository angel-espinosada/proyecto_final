#ifndef NIVEL_1_H
#define NIVEL_1_H
#include <QGraphicsScene>
#include "escenario_juego.h"
#include "tubo_caliente.h"
#include "tubo_frio.h"
#include "jugador.h"

class nivel_1
{
    private:
    QGraphicsScene *escena;
    Escenario_juego *escenario;


public:
nivel_1(QGraphicsScene *escena);

void cargarEscenario();
void cargarSuelo();
void cargarTubos();
void cargarJugador();
};

#endif // NIVEL_1_H
