#include "nivel_1.h"
#include <QMessageBox>


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
    tuboCaliente = new Tubo_caliente(730, y, 50, 150);
    escena->addItem(tuboCaliente);

    //Tubo_Frio *t2 = new Tubo_Frio(660, y, 50, 150);
    //escena->addItem(t2);
}

void nivel_1::cargarTecho()
{
    QGraphicsRectItem *techo = escenario->crearTecho(0, 0, 800, 50);
    escena->addItem(techo);
}

void nivel_1::verificarCollicion()
{
    if (jugador) {
        for (QGraphicsItem* item : jugador->collidingItems()) {
            if (dynamic_cast<Tubo_caliente*>(item)) {
                qDebug() << "Colisión con tubo caliente!";
                // Aquí enfriaremos después
            }
        }
    }
    if (tuboCaliente && tuboCaliente->getTemperatura() >= 100) {
        qDebug() << "Tubo llegó a 100°C! Perdiendo una vida...";

        // Restar vida
        this->juego->restarVida();
        actualizarVidas(this->juego->getVidas());

        if (!this->juego->haPerdido()) {
            tuboCaliente->reiniciarTemperatura(80);
            qDebug() << "Tubo reiniciado. Vidas restantes:" << this->juego->getVidas();
        } else {
             QMessageBox::critical(nullptr, "Game Over", "¡Has perdido todas tus vidas!\nInténtalo de nuevo.");
            qDebug() << "Juego terminado! No se reinicia el tubo."; }
    }
}

void nivel_1::cargarJugador(Juego *juego)
{
    jugador= new Jugador();

    // y = 550 piso - 75 (alto jugador) = 475
    jugador->setPos(100, 475);

    escena->addItem(jugador);
/*
    QGraphicsRectItem *test = new QGraphicsRectItem(300, 475, 50, 75);
    test->setBrush(Qt::red);
    test->setZValue(200);  // para que quede encima si es necesario
    escena->addItem(test);*/
}

void nivel_1::actualizarVidas(int vidas)
{
    QPixmap lleno(":/imagenes/vida.png");
    QPixmap vacio(":/imagenes/vida_perdida.png");

    // Escalar ambas
    QPixmap llenoEscalado = lleno.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QPixmap vacioEscalado = vacio.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    cor1->setPixmap(vidas >= 1 ? llenoEscalado : vacioEscalado);
    cor2->setPixmap(vidas >= 2 ? llenoEscalado : vacioEscalado);
    cor3->setPixmap(vidas >= 3 ? llenoEscalado : vacioEscalado);
}

void nivel_1::setJuego(Juego *j)
{
    this->juego = j; //guardar en la variable miembro
    j->setNivel(this);
}
