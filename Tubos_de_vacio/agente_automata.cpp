#include "agente_automata.h"
#include "nivel_3.h"
#include <QDebug>

AgenteAutomata::AgenteAutomata(nivel_3 *nivel, QObject *parent)
    : QObject(parent), nivel(nivel)
{
}

void AgenteAutomata::iniciar()
{
    if (timer) return;

    qDebug() << "🤖 Agente automata iniciado";

    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this]() {

        if (!nivel) return;

        // Movimiento tipo serpiente
        if (direccionDerecha) {

            if (nivel->getColJugador() < nivel->getColumnas() - 1) {
                nivel->moverJugador(0, 1);   // →
            } else {
                direccionDerecha = false;
                nivel->moverJugador(1, 0);   // ↓
            }

        } else {

            if (nivel->getColJugador() > 0) {
                nivel->moverJugador(0, -1);  // ←
            } else {
                direccionDerecha = true;
                nivel->moverJugador(1, 0);   // ↓
            }
        }
    });

    timer->start(700);
}

void AgenteAutomata::detener()
{
    if (timer) {
        timer->stop();
        timer->deleteLater();
        timer = nullptr;
        qDebug() << "Agente automata detenido";
    }
}
