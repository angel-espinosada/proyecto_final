#ifndef ESCENARIO_JUEGO_H
#define ESCENARIO_JUEGO_H

#include <QGraphicsItem>
#include <QPainter>
#include <QColor>
class Escenario_juego : public QGraphicsItem
{
private:
    int w, h;
    QColor color;

public:
    Escenario_juego(int x, int y, int w, int h, QColor color);

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
};


#endif // ESCENARIO_JUEGO_H
