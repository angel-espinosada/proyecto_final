#ifndef TUBO_CALIENTE_H
#define TUBO_CALIENTE_H
#include "tubo.h"
#include "QPainter"
#include <QTimer>
#include <QPixmap>
#include <QDebug>

class Tubo_caliente :public Tubo

{
    Q_OBJECT
private:
    int ancho, alto;
    QTimer *timerCalentamiento = nullptr;

public:
   Tubo_caliente(int x, int y, int w, int h);
    int getTemperatura() const { return temperatura; }
    void actualizar();          // sube temp y revisa explosión
    void subirTemperatura();    // aumenta calor
    bool estadoTemperatura();
    void reiniciarTemperatura(int temp);
    void enfriar(int cantidad);
    bool estaExplotado() const;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;

  //~Tubo_caliente();

};
#endif // TUBO_CALIENTE_H
