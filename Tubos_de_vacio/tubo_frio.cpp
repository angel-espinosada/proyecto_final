#include "tubo_frio.h"

#include <QPixmap>
#include <QDebug>

Tubo_Frio::Tubo_Frio(int x, int y, int w, int h):Tubo(x, y, w, h, 10, 100)
{
    ancho = w;
    alto = h;
    setPos(x, y);  // ← Posicionar el item en la escena

    qDebug() << "Tubo frio creado en:" << x << y << "Tamaño:" << w << "x" << h;
}

QRectF Tubo_Frio::boundingRect() const
{
    // Retornar el rectángulo en coordenadas LOCALES
    return QRectF(0, 0, ancho, alto);
}

void Tubo_Frio::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap(":/imagenes/Tubo vacio frio.PNG");
    painter->drawPixmap(boundingRect(), pixmap, pixmap.rect());
}
void Tubo_Frio::actualizar()
{
    Tubo::actualizar();
}

void Tubo_Frio::bajarTemperatura()
{
    if (temperatura +10<= temperaturaMax)
        temperatura -= 10;
}

bool Tubo_Frio::estadoTemperatura()
{
return temperatura <= 50;
}

bool Tubo_Frio::estaExplotado() const
{
return explotado;
}
