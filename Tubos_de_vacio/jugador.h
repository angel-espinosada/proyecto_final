#ifndef JUGADOR_H
#define JUGADOR_H
#include <QGraphicsItem>
#include "tubo_caliente.h"
#include "tubo_frio.h"


class Jugador: public QGraphicsItem
{
    int ancho, alto;
    int velocidad;
    void moverIzquierda();
    void moverDerecha();
    void chequearLimites();
   Tubo_caliente *tuboCerca = nullptr;


public:
    Jugador();
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QPainterPath shape() const override;

    void keyPressEvent(QKeyEvent *event) override;
};

#endif // JUGADOR_H
