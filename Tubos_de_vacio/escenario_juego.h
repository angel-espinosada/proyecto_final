#ifndef ESCENARIO_JUEGO_H
#define ESCENARIO_JUEGO_H

#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QColor>
class Escenario_juego : public QGraphicsItem
{
private:
    int w, h;
    QColor color;
    QGraphicsPixmapItem* cor1 = nullptr;
    QGraphicsPixmapItem* cor2 = nullptr;
    QGraphicsPixmapItem* cor3 = nullptr;

public:
    Escenario_juego(int x, int y, int w, int h, QColor color);

    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
    QGraphicsRectItem* crearSuelo(int x, int y, int ancho, int alto);
    QGraphicsRectItem* crearTecho(int x, int y, int ancho, int alto);
    QGraphicsPixmapItem* crearFondo(const QString &rutaImagen, int x, int y, int w, int h);
    QGraphicsRectItem* crearObstaculo(int x, int y, int ancho, int alto, const QColor& color = QColor(139, 69, 19));
    void cargarVidas(QGraphicsScene* escena, int vidas = 3);
    void actualizarVidas(QGraphicsScene* escena, int vidas);
};


#endif // ESCENARIO_JUEGO_H
