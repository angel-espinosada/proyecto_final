#ifndef NIVEL_1_H
#define NIVEL_1_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "escenario_juego.h"
#include "tubo_caliente.h"
#include "tubo_frio.h"
#include "jugador.h"
#include "juego.h"

class nivel_1
{
    private:
    QGraphicsScene *escena;
    Escenario_juego *escenario;
    QGraphicsPixmapItem *cor1;
    QGraphicsPixmapItem *cor2;
    QGraphicsPixmapItem *cor3;


public:
nivel_1(QGraphicsScene *escena);
Jugador* jugador = nullptr;
void cargarEscenario();
void cargarvida();
void cargarSuelo();
void cargarFondo();
void cargarTubos();
void cargarTecho();
Jugador* jugador = nullptr;
void verificarCollicion();
void cargarJugador(Juego *juego);
void actualizarVidas(int vidas);
void setJuego(Juego *juego);
};

#endif // NIVEL_1_H
