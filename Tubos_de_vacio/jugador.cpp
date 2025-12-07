#include "jugador.h"
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsScene>

void Jugador::moverIzquierda()
{
     setX(x() - velocidad);
}

void Jugador::moverDerecha()
{
     setX(x() + velocidad);
}

void Jugador::chequearLimites()
{
    if (!scene()) return;

    int minX = 0;
    int maxX = scene()->width() - ancho;

    if (x() < minX)
        setX(minX);

    if (x() > maxX)
        setX(maxX);
}

Jugador::Jugador() {

    velocidad = 8;
    ancho = 50;
    alto = 75;

    // Para recibir eventos de teclado
    setFlag(ItemIsFocusable);
    setFocus();
}

QRectF Jugador::boundingRect() const
{
    return QRectF(0, 0, ancho, alto);
}

void Jugador::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::blue);

    QPolygonF triangulo;
    triangulo << QPointF(ancho / 2, 0)          // punta arriba
              << QPointF(0, alto)               // esquina inferior izquierda
              << QPointF(ancho, alto);          // esquina inferior derecha

    painter->drawPolygon(triangulo);
}

void Jugador::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A)
        moverIzquierda();

    if (event->key() == Qt::Key_D)
        moverDerecha();

    chequearLimites();
}
