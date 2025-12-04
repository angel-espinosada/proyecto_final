#include "tubo_caliente.h"
#include <QPixmap>
#include <QDebug>

Tubo_caliente::Tubo_caliente(int x, int y, int w, int h)
    : Tubo(x, y, w, h, 10, 100)  // temp inicial = 10, tempMax = 100
{
    ancho = w;
    alto = h;
    setPos(x, y);  // ← Posicionar el item en la escena

    qDebug() << "Tubo caliente creado en:" << x << y << "Tamaño:" << w << "x" << h;
}

QRectF Tubo_caliente::boundingRect() const
{
    // Retornar el rectángulo en coordenadas LOCALES
    return QRectF(0, 0, ancho, alto);
}

void Tubo_caliente::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap(":/imagenes/Tubo caliente.PNG");
    painter->drawPixmap(boundingRect(), pixmap, pixmap.rect());
}
void Tubo_caliente::actualizar()
{
    // Tu código
}

void Tubo_caliente::subirTemperatura()
{
    // Tu código
}

bool Tubo_caliente::estadoTemperatura()
{
    return false;
}

bool Tubo_caliente::estaExplotado() const
{
    return false;
}
