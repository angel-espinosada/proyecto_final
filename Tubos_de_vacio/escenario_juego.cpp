#include "escenario_juego.h"

Escenario_juego::Escenario_juego(int x, int y, int w, int h, QColor color)
    : w(w), h(h), color(color)
{
    setPos(x, y);
}

QRectF Escenario_juego::boundingRect() const
{
    return QRectF(0, 0, w, h);
}

void Escenario_juego::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *,
                            QWidget *)
{
    painter->setBrush(color);
    painter->drawRect(0, 0, w, h);
}

QGraphicsRectItem *Escenario_juego::crearSuelo(int x, int y, int ancho, int alto)
{
    QGraphicsRectItem *suelo = new QGraphicsRectItem(x, y, ancho, alto);
    suelo->setBrush(QColor(139, 69, 19));   // café
    suelo->setPen(QPen(Qt::black, 2));
    return suelo;
}


