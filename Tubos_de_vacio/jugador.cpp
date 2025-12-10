#include "jugador.h"
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>
#include "tubo_caliente.h"
#include "tubo_frio.h"
#include "nivel_1.h"

void Jugador::moverIzquierda()
{
     setX(x() - velocidad);
}

void Jugador::moverDerecha()
{
     setX(x() + velocidad);
}

void Jugador::chequearLimites()
{
    if (!scene()) return;

    int minX = 0;
    int maxX = scene()->width() - ancho;

    if (x() < minX)
        setX(minX);

    if (x() > maxX)
        setX(maxX);
}

Jugador::Jugador() {

    velocidad = 8;
    ancho = 50;
    alto = 75;

    // Para recibir eventos de teclado
    setFlag(ItemIsFocusable);
    setFocus();
}

QRectF Jugador::boundingRect() const
{
    return QRectF(0, 0, ancho, alto);
}

void Jugador::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (modoTopDown) {
        painter->setBrush(Qt::blue);
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(-15, -15, 60, 60);
        return;
    }


    painter->setBrush(Qt::blue);

    QPolygonF triangulo;
    triangulo << QPointF(ancho / 2, 0)          // punta arriba
              << QPointF(0, alto)               // esquina inferior izquierda
              << QPointF(ancho, alto);          // esquina inferior derecha

    painter->drawPolygon(triangulo);
}

QPainterPath Jugador::shape() const
{
    QPainterPath path;

    QPolygonF triangulo;
    triangulo << QPointF(ancho / 2, 0)
              << QPointF(0, alto)
              << QPointF(ancho, alto);

    path.addPolygon(triangulo);
    return path;
}

void Jugador::keyPressEvent(QKeyEvent *event)
{
    // --- MODO TOP DOWN (Nivel 2) ---
    if (modoTopDown)
    {
        int paso = 10;

        if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
            setY(y() - paso);

        if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
            setY(y() + paso);

        if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
            setX(x() - paso);

        if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
            setX(x() + paso);
        update();
        return;  // Muy importante

    }

    // LÓGICA DEL NIVEL 1 (mover izquierda/derecha) ---
    if (event->key() == Qt::Key_A)
        moverIzquierda();

    if (event->key() == Qt::Key_D)
        moverDerecha();

    chequearLimites();

    // Recargar
    if (event->key() == Qt::Key_R) {
        carga = 10;
        qDebug() << "Recargado: carga = 10";
    }

    // Enfriar
    if (event->key() == Qt::Key_E) {
        if (nivel)
            nivel->enfriarTubo();
    }
}
