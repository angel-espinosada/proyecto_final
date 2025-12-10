#ifndef NIVEL_2_H
#define NIVEL_2_H
#include <QGraphicsScene>
#include "jugador.h"
#include "tubo_caliente.h"
#include "tubo_frio.h"
#include "escenario_juego.h"
#include "juego.h"

class nivel_2 : public QObject
{
    Q_OBJECT
private:
    QGraphicsScene *escena;
    Escenario_juego *escenario;

    Tubo_caliente *tuboCaliente = nullptr;
    Tubo_Frio *tuboFrio = nullptr;

    Jugador *jugador = nullptr;
    Juego *juego = nullptr;

    int tiempoRestante = 300;

public:
    nivel_2(QGraphicsScene *escena);

    void cargarEscenario();
    void cargarFondo();
    void cargarTubos();
    void cargarObstaculos();
    void cargarJugador(Juego *juego);
    void setJuego(Juego *j);
public slots:
    void actualizar();

};

#endif // NIVEL_2_H
