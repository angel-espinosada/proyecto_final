#ifndef JUEGO_H
#define JUEGO_H

#include "jugador.h"
#include <QTimer>
#include <QObject>


class nivel_1;
class nivel_2;
class Juego:public QObject
{
    Q_OBJECT
private:

    QTimer *timer;
    int vidas;
    int progreso;
    int progreso_necesario;
    int numeroNivelActual = 0; // 0 = ninguno, 1 = nivel_1, 2 = nivel_2
   nivel_1 *nivelActual = nullptr;

public:
   Juego();

    void restarVida();
    void sumarProgreso(int cantidad);
    void setNivel(nivel_1 *nivel);
    bool haGanado() const;
    bool haPerdido() const;

    int getVidas() const;
    int getProgreso() const;



public slots:
    void actualizar();

};

#endif // JUEGO_H
