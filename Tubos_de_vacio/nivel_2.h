#ifndef NIVEL_2_H
#define NIVEL_2_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "jugador.h"
#include "tubo_caliente.h"
#include "tubo_frio.h"
#include "escenario_juego.h"
#include "juego.h"
#include <QVector>

struct TuboInfo {
    Tubo_caliente* caliente = nullptr;
    Tubo_Frio*     frio     = nullptr;
    bool cambiado = false;
    int temperatura = 50;      //
    int temperaturaMax = 100;  //
    QTimer *timerCalentamiento = nullptr; // para calentar solo este tubo
    int posX = 0;
    int posY = 0;


};

class nivel_2 : public QObject
{
    Q_OBJECT
private:
    QGraphicsScene *escena;
    Escenario_juego *escenario;

    Tubo_caliente *tuboCaliente = nullptr;
    Tubo_Frio *tuboFrio = nullptr;
    Tubo_caliente *tuboSuperiorIzq = nullptr;
    Tubo_caliente *tuboSuperiorDer = nullptr;

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
    QVector<TuboInfo> tubos;
    //Fisica
    float velocidadX = 0;
    float velocidadXSalto = 0.0f;
    bool estaSaltando = false;
    bool enSalto = false;

public:
    nivel_2(QGraphicsScene *escena);

    void cargarEscenario();
    void cargarFondo();
    void cargarTubos();
    void cargarObstaculos();
    void cargarJugador(Juego *juego);
    void setJuego(Juego *j);
    void cargarvida();
    void actualizarVidas(int vidas);
    void verificarCollicion();
    bool jugadorTocaTuboCaliente(int &indiceTubo);

    void actualizarFisica();
    void saltar();
public slots:
    void actualizar();
    void verificarCambioTubos();
   void tuboExplotado(TuboInfo &tubo);

};

#endif // NIVEL_2_H
