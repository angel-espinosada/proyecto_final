#ifndef JUEGO_H
#define JUEGO_H
#include <QGraphicsScene>
#include "jugador.h"



class nivel_1;
class Juego
{
private:
    int vidas;
    int progreso;
    int progreso_necesario;
     nivel_1 *nivelActual;
public:
    Juego();

    void restarVida();
    void sumarProgreso(int cantidad);

    bool haGanado() const;
    bool haPerdido() const;

    int getVidas() const;
    int getProgreso() const;
    void setNivel(nivel_1 *nivel);
};

#endif // JUEGO_H
