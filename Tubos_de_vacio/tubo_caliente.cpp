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

QPainterPath Tubo_caliente::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Tubo_caliente::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap(":/imagenes/Tubo caliente.PNG");
    painter->drawPixmap(boundingRect(), pixmap, pixmap.rect());

    // ✅ Dibujar el boundingRect para depurar
    painter->setPen(QPen(Qt::red, 2));
    painter->drawRect(boundingRect());

    // ✅ Dibujar el shape (opcional)
    painter->setPen(QPen(Qt::green, 1));
    painter->drawPath(shape());
}


void Tubo_caliente::actualizar()
{
    Tubo::actualizar();
}

void Tubo_caliente::subirTemperatura()
{

    if (temperatura +10<= temperaturaMax)
        temperatura += 10;
}

bool Tubo_caliente::estadoTemperatura()
{
    return temperatura >= 50;;
}

bool Tubo_caliente::estaExplotado() const{


    return explotado;

}
