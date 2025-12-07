#ifndef NIVEL_1_H
#define NIVEL_1_H
#include <QGraphicsScene>
#include "escenario_juego.h"
#include "tubo_caliente.h"
#include "tubo_frio.h"

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
};

#endif // NIVEL_1_H
