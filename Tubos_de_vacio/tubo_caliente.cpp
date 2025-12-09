#include "tubo_caliente.h"
#include <QPixmap>
#include <QDebug>
#include <QTimer>


Tubo_caliente::Tubo_caliente(int x, int y, int w, int h)
    : Tubo(x, y, w, h, 80, 100)  // temp inicial = 80, tempMax = 100
{
    ancho = w;
    alto = h;
    setPos(x, y);  // Posicionar el item en la escena

    qDebug() << "Tubo caliente creado en:" << x << y << "Tamaño:" << w << "x" << h;
    timerCalentamiento = new QTimer(this);
    connect(timerCalentamiento, &QTimer::timeout, this, &Tubo_caliente::subirTemperatura);
    timerCalentamiento->start(1000); // cada 1000 ms = 1 segundo

    qDebug() << "Tubo creado | Temp:" << temperatura;
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

    // Dibujar el boundingRect para depurar
    painter->setPen(QPen(Qt::red, 2));
    painter->drawRect(boundingRect());

    // Dibujar el shape
    painter->setPen(QPen(Qt::green, 1));
    painter->drawPath(shape());
}


void Tubo_caliente::actualizar()
{
    Tubo::actualizar();
}

void Tubo_caliente::subirTemperatura()
{

    if (temperatura < temperaturaMax){
        temperatura ++;
    qDebug() << "Tubo caliente: temperatura =" << temperatura;
}
}

bool Tubo_caliente::estadoTemperatura()
{
    return temperatura >= 50;
}

void Tubo_caliente::reiniciarTemperatura(int temp)
{
    temperatura = temp;
    qDebug() << "Tubo reiniciado a:" << temperatura << "°C";
}

void Tubo_caliente::enfriar(int cantidad)
{
    temperatura -= cantidad;
    if (temperatura < 0) {
        temperatura = 0;
    }
    qDebug() << "❄️ Tubo enfriado a:" << temperatura << "°C";
}

bool Tubo_caliente::estaExplotado() const{


    return explotado;

}
