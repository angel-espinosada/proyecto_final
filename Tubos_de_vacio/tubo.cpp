#include "tubo.h"
#include <QPixmap>

Tubo::Tubo(int x, int y,int w, int h,int tempInicial, int tempMax)
{
    setPos(x, y);
    temperatura = tempInicial;
    temperaturaMax = tempMax;
    explotado = false;
}

void Tubo::actualizar()
{
    temperatura += 1;
    if (temperatura >= temperaturaMax)
        explotado = true;
}


void Tubo::bajarTemperatura(int cantidad)
{
    temperatura -= cantidad;
    if (temperatura < 0)
        temperatura = 0;
}

bool Tubo::estaExplotado() const
{
    return explotado;
}

QPainterPath Tubo::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
