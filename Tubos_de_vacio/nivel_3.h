#ifndef NIVEL_3_H
#define NIVEL_3_H
#include <QGraphicsScene>
#include "escenario_juego.h"
#include "jugador.h"
#include "juego.h"
class nivel_3
{
private:

    QGraphicsScene *escena;
    Escenario_juego *escenario;



    Jugador *jugador = nullptr;
    Juego *juego = nullptr;

    int tiempoRestante = 300;

    QGraphicsPixmapItem *cor1;
    QGraphicsPixmapItem *cor2;
    QGraphicsPixmapItem *cor3;

    QGraphicsRectItem *caja1 = nullptr;
    QGraphicsRectItem *caja2 = nullptr;
    QGraphicsRectItem *caja3 = nullptr;

    //Para Mostrar los mensajes de instrucciones
    QGraphicsTextItem *textoInstrucciones = nullptr;
    int framesInstrucciones = 0;
    bool mostrarInstruccionesInicio = true;

    //Fisica
    float velocidadX = 0;
    float velocidadXSalto = 0.0f;
    bool estaSaltando = false;
    bool enSalto = false;
    bool juegoTerminado = false;
    void detenerNivel();
public:

public:
    nivel_3(QGraphicsScene *escena);
    void inicializar();
    void cargarEscenario();
    void cargarFondo();
    void cargarvida();
    void cargarJugador(Juego *juego);
};

#endif // NIVEL_3_H
