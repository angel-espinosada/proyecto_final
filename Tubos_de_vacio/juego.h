#ifndef JUEGO_H
#define JUEGO_H

#include "jugador.h"
#include <QTimer>
#include <QObject>


class nivel_1;
class Juego:public QObject
{
    Q_OBJECT
private:

    QTimer *timer;
    int vidas;
    int progreso;
    int progreso_necesario;
     nivel_1 *nivelActual = nullptr;
public:
    Juego();

    void restarVida();
    void sumarProgreso(int cantidad);

    bool haGanado() const;
    bool haPerdido() const;

    int getVidas() const;
    int getProgreso() const;
    void setNivel(nivel_1 *nivel);
public slots:
    void actualizar();
};

#endif // JUEGO_H
