#ifndef JUGADOR_H
#define JUGADOR_H
#include <QGraphicsItem>
#include "tubo_caliente.h"
#include "tubo_frio.h"

class nivel_1;
class Jugador: public QGraphicsItem
{

    int ancho, alto;
    int velocidad;
    void moverIzquierda();
    void moverDerecha();
    void chequearLimites();
     int carga = 0;
     nivel_1* nivel = nullptr;
   Tubo_caliente *tuboCerca = nullptr;
     bool modoTopDown = false;



public:
    Jugador();
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QPainterPath shape() const override;

    void keyPressEvent(QKeyEvent *event) override;
    void recargar() { carga = 15; }
    bool tieneCarga() const { return carga > 0; }
    void usarCarga() { if (carga > 0) carga = 0; }
    int getCarga() const { return carga; }
     void setNivel(nivel_1* n) { nivel = n; }
     void setModoTopDown(bool v) { modoTopDown = v; }
};

#endif // JUGADOR_H
