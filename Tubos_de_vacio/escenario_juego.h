#ifndef ESCENARIO_JUEGO_H
#define ESCENARIO_JUEGO_H
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QColor>

// clase que maneja todos los elementos visuales del escenario (fondo, suelo, vidas, etc)
class Escenario_juego : public QGraphicsItem
{
private:
    int w, h;  // ancho y alto del escenario
    QColor color;  // color de fondo del escenario

    // corazones que representan las vidas del jugador
    QGraphicsPixmapItem* cor1 = nullptr;  // corazón vida 1
    QGraphicsPixmapItem* cor2 = nullptr;  // corazón vida 2
    QGraphicsPixmapItem* cor3 = nullptr;  // corazón vida 3

public:
    // constructor: crea el escenario con posición (x,y), dimensiones (w,h) y color
    Escenario_juego(int x, int y, int w, int h, QColor color);

    // métodos requeridos por QGraphicsItem
    QRectF boundingRect() const override;  // define el área del escenario
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;  // dibuja el fondo del escenario

    // métodos para crear elementos del nivel
    QGraphicsRectItem* crearSuelo(int x, int y, int ancho, int alto);  // crea el piso donde camina el jugador
    QGraphicsRectItem* crearTecho(int x, int y, int ancho, int alto);  // crea el límite superior
    QGraphicsPixmapItem* crearFondo(const QString &rutaImagen, int x, int y, int w, int h);  // carga imagen de fondo
    QGraphicsRectItem* crearObstaculo(int x, int y, int ancho, int alto, const QColor& color = QColor(139, 69, 19));  // crea cajas/obstáculos

    // métodos para gestionar las vidas visuales
    void cargarVidas(QGraphicsScene* escena, int vidas = 3);  // muestra los corazones iniciales
    void actualizarVidas(QGraphicsScene* escena, int vidas);  // actualiza cuántos corazones se muestran
};
#endif // ESCENARIO_JUEGO_H
