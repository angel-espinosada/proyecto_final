#include "juego.h"
#include "nivel_1.h"
#include "nivel_2.h"


Juego::Juego()
{

    vidas = 3;
    progreso = 0;
    progreso_necesario = 100;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Juego::actualizar);
    timer->start(16); // 60 veces por segundo
}

void Juego::restarVida()
{
    if(vidas>0)
    vidas--;
}

void Juego::sumarProgreso(int cantidad)
{
    progreso+=cantidad;
}

bool Juego::haGanado() const
{
    return progreso>=progreso_necesario;
}

bool Juego::haPerdido() const
{
    return vidas<=0;
}
int Juego::getVidas() const { return vidas; }
int Juego::getProgreso() const { return progreso; }

void Juego::setNivel(nivel_1 *nivel)
{
    this->nivelActual = nivel;
}


void Juego::actualizar()
{
    if (nivelActual && nivelActual->jugador) {
        nivelActual->verificarCollicion();
    }

}
