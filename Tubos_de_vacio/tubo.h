#ifndef TUBO_H
#define TUBO_H
#include <QGraphicsPixmapItem>

class Tubo: public QGraphicsObject
{
    int x,y,w,h;
protected:
    int temperatura;
    int temperaturaMax;
    bool explotado;

public:
    Tubo(int x, int y,int w,int  h,int tempInicial, int tempMax);

    void actualizar();
    void bajarTemperatura(int cantidad);
    bool estaExplotado() const;
    QPainterPath shape() const override;
};
#endif // TUBO_H
