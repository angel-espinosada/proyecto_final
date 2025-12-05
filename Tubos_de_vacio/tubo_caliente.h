#ifndef TUBO_CALIENTE_H
#define TUBO_CALIENTE_H
#include "tubo.h"
#include "QGraphicsItem"
#include "QPainter"
#include <QPixmap>

class Tubo_caliente :public Tubo
{
private:
    int ancho, alto;

public:
   Tubo_caliente(int x, int y, int w, int h);

    void actualizar();          // sube temp y revisa explosión
    void subirTemperatura();    // aumenta calor
    bool estadoTemperatura();
    bool estaExplotado() const;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

};
#endif // TUBO_CALIENTE_H
