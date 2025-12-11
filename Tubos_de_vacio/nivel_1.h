#ifndef NIVEL_1_H
#define NIVEL_1_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "escenario_juego.h"
#include "tubo_caliente.h"
#include "tubo_frio.h"
#include "jugador.h"
#include "juego.h"
#include <QObject>

class nivel_1 : public QObject
{
    Q_OBJECT
    private:
    QGraphicsScene *escena;
    Escenario_juego *escenario;
    QGraphicsPixmapItem *cor1;
    QGraphicsPixmapItem *cor2;
    QGraphicsPixmapItem *cor3;
    Tubo_caliente *tuboCaliente = nullptr;
    Juego *juego = nullptr;
    //Para Mostrar los mensajes de instrucciones
    QGraphicsTextItem *textoInstrucciones = nullptr;
    int framesInstrucciones = 0;
    bool mostrarInstruccionesInicio = true;
    bool gameOverMostrado = false;
    bool victoriaMostrada = false;


public:
nivel_1(QGraphicsScene *escena);
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
void reiniciarTemperatura(int temp);
void enfriarTubo();

signals:
void nivelCompletado();
     void gameOver();
};

#endif // NIVEL_1_H
