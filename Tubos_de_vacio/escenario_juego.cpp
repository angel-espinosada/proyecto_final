#include "escenario_juego.h"

Escenario_juego::Escenario_juego(int x, int y, int w, int h, QColor color)
    : w(w), h(h), color(color)
{
    setPos(x, y);
}

QRectF Escenario_juego::boundingRect() const
{
    return QRectF(0, 0, w, h);
}

void Escenario_juego::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *,
                            QWidget *)
{

}

QGraphicsRectItem *Escenario_juego::crearSuelo(int x, int y, int ancho, int alto)
{
    QGraphicsRectItem *suelo = new QGraphicsRectItem(x, y, ancho, alto);
    suelo->setBrush(QColor(139, 69, 19));   // café
    suelo->setPen(QPen(Qt::black, 2));
    return suelo;
}

QGraphicsRectItem *Escenario_juego::crearTecho(int x, int y, int ancho, int alto)
{
    QGraphicsRectItem *techo = new QGraphicsRectItem(x, y, ancho, alto);
    techo->setBrush(QColor(13, 69, 19));   // café
    techo->setPen(QPen(Qt::black, 2));
    return techo;
}

QGraphicsPixmapItem *Escenario_juego::crearFondo(const QString &rutaImagen, int x, int y, int w, int h)
{
    QPixmap fondoPixmap(rutaImagen);

    // Se el fondo al tamaño del escenario
    QPixmap fondoEscalado = fondoPixmap.scaled(w, h, Qt::IgnoreAspectRatio,
                                               Qt::SmoothTransformation);

    QGraphicsPixmapItem *fondo = new QGraphicsPixmapItem(fondoEscalado);
    fondo->setPos(x, y);
    fondo->setZValue(-100);  // Poner fondo atras

    return fondo;
}

QGraphicsRectItem *Escenario_juego::crearObstaculo(int x, int y, int ancho, int alto, const QColor &color)
{
    QGraphicsRectItem* obstaculo = new QGraphicsRectItem(x, y, ancho, alto);
    obstaculo->setBrush(color);
    return obstaculo; // el nivel lo añadirá a la escena
}

void Escenario_juego::cargarVidas(QGraphicsScene *escena, int vidas)
{
    QPixmap lleno(":/imagenes/vida.png");
    QPixmap vidaEscalada = lleno.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Si ya existen, eliminarlos primero (evita duplicados)
    if (cor1) { escena->removeItem(cor1); delete cor1; }
    if (cor2) { escena->removeItem(cor2); delete cor2; }
    if (cor3) { escena->removeItem(cor3); delete cor3; }

    cor1 = new QGraphicsPixmapItem(vidaEscalada);
    cor2 = new QGraphicsPixmapItem(vidaEscalada);
    cor3 = new QGraphicsPixmapItem(vidaEscalada);

    cor1->setZValue(100);
    cor2->setZValue(100);
    cor3->setZValue(100);

    int ancho_escena = 800;
    int tamaño = 30;
    cor1->setPos(ancho_escena - tamaño - 10, 55);
    cor2->setPos(ancho_escena - tamaño * 2 - 20, 55);
    cor3->setPos(ancho_escena - tamaño * 3 - 30, 55);

    escena->addItem(cor1);
    escena->addItem(cor2);
    escena->addItem(cor3);

    actualizarVidas(escena, vidas);

}

void Escenario_juego::actualizarVidas(QGraphicsScene *escena, int vidas)
{
    QPixmap lleno(":/imagenes/vida.png");
    QPixmap vacio(":/imagenes/vida_perdida.png");
    QPixmap llenoEscalado = lleno.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap vacioEscalado = vacio.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    if (cor1) cor1->setPixmap(vidas >= 1 ? llenoEscalado : vacioEscalado);
    if (cor2) cor2->setPixmap(vidas >= 2 ? llenoEscalado : vacioEscalado);
    if (cor3) cor3->setPixmap(vidas >= 3 ? llenoEscalado : vacioEscalado);
}


