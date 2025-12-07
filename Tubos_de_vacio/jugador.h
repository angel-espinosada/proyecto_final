#ifndef JUGADOR_H
#define JUGADOR_H
#include <QGraphicsItem>

class Jugador: public QGraphicsEllipseItem
{
    int ancho, alto;
    int velocidad;
    void moverIzquierda();
    void moverDerecha();
    void chequearLimites();


public:
    Jugador();
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // JUGADOR_H
