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

    bool juegoTerminado = false;
    void detenerNivel();

    static const int filas = 8;
    static const int columnas = 8;

    int tablero[filas][columnas];
    int filaJugador = 0;
    int colJugador = 0;
    int tamCelda = 60;
    int offsetX = 80;   // ajustar según imagen
    int offsetY = 60;   // ajustar según imagen

    int margenCelda = 6;
    int tableroPixAncho = 0;
    int tableroPixAlto  = 0;

    QVector<QGraphicsRectItem*> minasVisuales;


public:
    nivel_3(QGraphicsScene *escena);
    void inicializar();
    void cargarEscenario();
    void cargarFondo();
    void cargarvida();
    void cargarJugador(Juego *juego);
   void moverJugador(int df, int dc);
    void actualizarVidas(int vidas);
   void dibujarMinas();
    void dibujarGrilla();
   void dibujarTablero();
};

#endif // NIVEL_3_H
