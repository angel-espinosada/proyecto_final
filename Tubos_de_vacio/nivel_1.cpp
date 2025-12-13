#include "nivel_1.h"
#include <QMessageBox>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

nivel_1::nivel_1(QGraphicsScene *escena)
{
    this->escena = escena;
}

void nivel_1::cargarEscenario()
{
    // crea el fondo base del nivel
    escenario = new Escenario_juego(0, 0, 800, 600, Qt::lightGray);
    escena->addItem(escenario);
}

void nivel_1::cargarvida()
{
    // muestra las 3 vidas iniciales
    escenario->cargarVidas(escena, 3);

}


void nivel_1::cargarSuelo()
{
    // crea el piso donde camina el jugador
    QGraphicsRectItem *suelo = escenario->crearSuelo(0, 550, 800, 50);
    escena->addItem(suelo);
}

void nivel_1::cargarFondo()
{
    // carga la imagen de fondo del nivel 1
    QGraphicsPixmapItem *fondo = escenario->crearFondo(
        ":/imagenes/fondo_nivel1.png",
        0, 0,
        800, 600
        );

    escena->addItem(fondo);
}

void nivel_1::cargarTubos()
{
    // calcula la posición del tubo sobre el suelo
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
    // crea el límite superior del nivel
    QGraphicsRectItem *techo = escenario->crearTecho(0, 0, 800, 50);
    escena->addItem(techo);
}

void nivel_1::verificarCollicion()
{
    // evita ejecutar lógica después de ganar o perder
    if (juegoTerminado) return;

    // verifica si el tubo fue enfriado a 50°c o menos (victoria)
    if (tuboCaliente && tuboCaliente->getTemperatura() <= 50 && !victoriaMostrada) {
        victoriaMostrada = true;
        juegoTerminado = true;

        detenerNivel();

        QMessageBox::information(nullptr, "¡Victoria!", "¡Nivel 1 completado!");
        emit nivelCompletado();
        return;
    }

    // detecta colisiones del jugador (solo para debug)
    if (jugador) {
        for (QGraphicsItem *item : jugador->collidingItems()) {
            if (dynamic_cast<Tubo_caliente*>(item)) {
                qDebug() << "Colisión con tubo caliente!";
            }
        }
    }

    // verifica si el tubo se sobrecalentó a 100°c (perder vida)
    if (tuboCaliente && tuboCaliente->getTemperatura() >= 100) {

        qDebug() << "Tubo llegó a 100°C! Perdiendo una vida...";

        juego->restarVida();
        actualizarVidas(juego->getVidas());

        // si aún tiene vidas, reinicia la temperatura del tubo
        if (!juego->haPerdido()) {
            tuboCaliente->reiniciarTemperatura(80);
            return;
        }

        // game over cuando se acaban las vidas
        juegoTerminado = true;
        detenerNivel();

        QMessageBox msg(QMessageBox::Critical,
                        "Game Over",
                        "¡Has perdido todas tus vidas!\nInténtalo de nuevo.",
                        QMessageBox::Ok);
        msg.exec();

        emit gameOver();
        return;
    }
}


void nivel_1::cargarJugador(Juego *j)
{
    jugador= new Jugador();
    jugador->setNivel(this);
    // posiciona al jugador sobre el suelo: y = 550 - 75 (alto jugador) = 475
    jugador->setPos(100, 475);
    this->juego = j;
    j->setNivel(this);
    escena->addItem(jugador);
}

void nivel_1::actualizarVidas(int vidas)
{
    // actualiza el contador visual de vidas
    if (escenario)
        escenario->actualizarVidas(escena, vidas);
}

void nivel_1::setJuego(Juego *j)
{
    this->juego = j;
    j->setNivel(this);
}

void nivel_1::enfriarTubo()
{
    if (!jugador || !tuboCaliente)
        return;

    // verifica si el jugador tiene carga disponible
    if (!jugador->tieneCarga()) {
        qDebug() << "No hay carga para enfriar. Presione R para recargar.";
        return;
    }

    // verifica si el jugador está tocando el tubo caliente
    QList<QGraphicsItem*> items = jugador->collidingItems();
    bool tocando = false;

    for (QGraphicsItem* item : items) {
        if (item == tuboCaliente) {
            tocando = true;
            break;
        }
    }

    if (!tocando) {
        qDebug() << " No está tocando el tubo. No se puede enfriar.";
        return;
    }

    // enfría el tubo 25 grados
    tuboCaliente->enfriar(25);
    qDebug() << "❄ Enfriado → Temperatura:" << tuboCaliente->getTemperatura();

    // consume la carga del jugador
    jugador->usarCarga();
    qDebug() << "Carga usada. Ahora está en 0.";

    // empuja al jugador hacia atrás después de enfriar
    jugador->setX(jugador->x() - 40);
}

void nivel_1::detenerNivel()
{
    // detiene todos los timers activos en la escena
    for (QObject *obj : escena->children()) {
        if (QTimer *t = qobject_cast<QTimer*>(obj)) {
            t->stop();
        }
    }
}
