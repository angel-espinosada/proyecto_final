#include "nivel_1.h"



nivel_1::nivel_1(QGraphicsScene *escena)
{
    this->escena = escena;
}

void nivel_1::cargarEscenario()
{
    escenario = new Escenario_juego(0, 0, 800, 600, Qt::lightGray);
    escena->addItem(escenario);
}

void nivel_1::cargarvida()
{
    QPixmap lleno(":/imagenes/vida.png");
    QPixmap vidaEscalada = lleno.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Escalar la imagen
    cor1 = new QGraphicsPixmapItem(vidaEscalada);
    cor2 = new QGraphicsPixmapItem(vidaEscalada);
    cor3 = new QGraphicsPixmapItem(vidaEscalada);

    // Z-order (adelante)
    cor1->setZValue(100);
    cor2->setZValue(100);
    cor3->setZValue(100);

    // Posiciones (derecha arriba)
    int ancho_escena = 800;
    int tamaño = 30;

    cor1->setPos(ancho_escena - tamaño - 10, 55);
    cor2->setPos(ancho_escena - tamaño * 2 - 20, 55);
    cor3->setPos(ancho_escena - tamaño * 3 - 30, 55);

    // Agregar
    escena->addItem(cor1);
    escena->addItem(cor2);
    escena->addItem(cor3);

}


void nivel_1::cargarSuelo()
{
    QGraphicsRectItem *suelo = escenario->crearSuelo(0, 550, 800, 50);
    escena->addItem(suelo);
}

void nivel_1::cargarFondo()
{
    QGraphicsPixmapItem *fondo = escenario->crearFondo(
        ":/imagenes/fondo_nivel1.png",
        0, 0,
        800, 600
        );

    escena->addItem(fondo);
}

void nivel_1::cargarTubos()
{
    //Temporarar para calcular Y
    int alturaSuelo = 550;
    int altoTubo = 150;
    int y = alturaSuelo - altoTubo; // 400 → justo sobre el suelo
    Tubo_caliente *t1 = new Tubo_caliente(730, y, 50, 150);
    escena->addItem(t1);

    Tubo_Frio *t2 = new Tubo_Frio(660, y, 50, 150);
    escena->addItem(t2);
}

void nivel_1::cargarTecho()
{
    QGraphicsRectItem *techo = escenario->crearTecho(0, 0, 800, 50);
    escena->addItem(techo);
}

void nivel_1::verificarCollicion()
{
    if (!jugador) return;

    QList<QGraphicsItem*> items = jugador->collidingItems();
    for (QGraphicsItem* item : items)
    {
        if (dynamic_cast<Tubo_caliente*>(item))
        {
            qDebug() << "🔥 Colisión con tubo CALIENTE!";
            // Aplicar daño, quitar vida, etc.
        }
        else if (dynamic_cast<Tubo_Frio*>(item))
        {
            qDebug() << "❄️ Colisión con tubo FRÍO!";
        }
    }
}

void nivel_1::cargarJugador(Juego *juego)
{
    jugador= new Jugador();

    // y = 550 piso - 75 (alto jugador) = 475
    jugador->setPos(100, 475);

    escena->addItem(jugador);

    QGraphicsRectItem *test = new QGraphicsRectItem(300, 475, 50, 75);
    test->setBrush(Qt::red);
    test->setZValue(200);  // para que quede encima si es necesario
    escena->addItem(test);
}

void nivel_1::actualizarVidas(int vidas)
{
    QPixmap lleno(":/imagenes/vida.png");
    QPixmap vacio(":/imagenes/vida_perdida.png");

    cor1->setPixmap(vidas >= 1 ? lleno : vacio);
    cor2->setPixmap(vidas >= 2 ? lleno : vacio);
    cor3->setPixmap(vidas >= 3 ? lleno : vacio);
}

void nivel_1::setJuego(Juego *juego)
{
juego->setNivel(this);
}
