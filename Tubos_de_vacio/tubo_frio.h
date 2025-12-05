#ifndef TUBO_FRIO_H
#define TUBO_FRIO_H
#include "tubo.h"
#include "QGraphicsItem"
#include "QPainter"
#include <QPixmap>

class Tubo_Frio:public Tubo
{private:
    int ancho, alto;

public:
    Tubo_Frio(int x, int y, int w, int h);

    void actualizar();          // Revisa y baja la temperatura
    void bajarTemperatura();    // aumenta el frio
    bool estadoTemperatura();
    bool estaExplotado() const;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

};

#endif // TUBO_FRIO_H
