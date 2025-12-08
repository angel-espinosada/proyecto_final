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

}

QGraphicsRectItem *Escenario_juego::crearSuelo(int x, int y, int ancho, int alto)
{
    QGraphicsRectItem *suelo = new QGraphicsRectItem(x, y, ancho, alto);
    suelo->setBrush(QColor(139, 69, 19));   // café
    suelo->setPen(QPen(Qt::black, 2));
    return suelo;
}

QGraphicsRectItem *Escenario_juego::crearTecho(int x, int y, int ancho, int alto)
{
    QGraphicsRectItem *techo = new QGraphicsRectItem(x, y, ancho, alto);
    techo->setBrush(QColor(13, 69, 19));   // café
    techo->setPen(QPen(Qt::black, 2));
    return techo;
}

QGraphicsPixmapItem *Escenario_juego::crearFondo(const QString &rutaImagen, int x, int y, int w, int h)
{
    QPixmap fondoPixmap(rutaImagen);

    // Se el fondo al tamaño del escenario
    QPixmap fondoEscalado = fondoPixmap.scaled(w, h, Qt::IgnoreAspectRatio,
                                               Qt::SmoothTransformation);

    QGraphicsPixmapItem *fondo = new QGraphicsPixmapItem(fondoEscalado);
    fondo->setPos(x, y);
    fondo->setZValue(-100);  // Poner fondo atras

    return fondo;
}


