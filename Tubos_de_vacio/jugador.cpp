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

void Jugador::moverArriba()
{
    setY(y() - velocidad);
}

void Jugador::moverAbajo()
{
    setY(y() + velocidad);
}

void Jugador::chequearLimites()
{

    if (!scene()) return;

    // Obtener dimensiones de la escena
    int anchoEscena = scene()->width();
    int altoEscena = scene()->height();

    if (modoTopDown) {
        int minY = -300;
        int maxY = altoEscena - 25;

        if (y() < minY) setY(minY);
        if (y() > maxY) setY(maxY);
    }
    else {
        // Modo nivel 1: solo izquierda/derecha
        int minX = 0;
        int maxX = anchoEscena - ancho;

        if (x() < minX) setX(minX);
        if (x() > maxX) setX(maxX);
}
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

{   if (modoTopDown) {return QRectF(-25, -35, 50, 50); // margen extra para seguridad
    }

    return QRectF(0, 0, ancho, alto);
}

void Jugador::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (modoTopDown) {
        painter->setBrush(Qt::darkGray);
        painter->setPen(Qt::black);
        painter->drawEllipse(-15, -15, 30, 30);

        // Torreta (frente del robot)
        painter->setBrush(Qt::gray);
        painter->drawRect(-8, -25, 16, 10);

        // Sensores ojos
        painter->setBrush(Qt::green);
        painter->drawEllipse(-10, -5, 6, 6);
        painter->drawEllipse(4, -5, 6, 6);

        // Antena
        painter->setBrush(Qt::red);
        painter->drawEllipse(-3, -30, 6, 6);

        // Ruedas
        painter->setBrush(Qt::black);
        painter->drawRect(-20, -5, 6, 20);
        painter->drawRect(14, -5, 6, 20);

        // Panel frontal
        painter->setBrush(QColor(255, 200, 0));
        painter->drawRect(-10, 8, 20, 8);


        /*
        painter->setBrush(Qt::blue);
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(-15, -15, 60, 60);
*/
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
    // (Nivel 2)
    if (modoTopDown)
    {
        if (!saltando)
        {
            if (event->key() == Qt::Key_W) moverArriba();
            if (event->key() == Qt::Key_S) moverAbajo();
        }

        if (event->key() == Qt::Key_A) moverIzquierda();
        if (event->key() == Qt::Key_D) moverDerecha();

        if (event->key() == Qt::Key_Space) {
            activarFisica = true;       // activar física
            pasoInicialSalto = true;    // dar pasito al inicio
            emit pedirSalto();          // saltar
        }
        return;

    }

    // Nivel 1 (mover izquierda/derecha) ---
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
