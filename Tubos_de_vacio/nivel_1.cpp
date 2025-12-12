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
    escenario = new Escenario_juego(0, 0, 800, 600, Qt::lightGray);
    escena->addItem(escenario);
}

void nivel_1::cargarvida()
{
    escenario->cargarVidas(escena, 3);

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
    // Evita que el nivel siga ejecutando lógica después de ganar/perder
    if (juegoTerminado) return;

    // ----- VICTORIA -----
    if (tuboCaliente && tuboCaliente->getTemperatura() <= 50 && !victoriaMostrada) {
        victoriaMostrada = true;
        juegoTerminado = true;     // detener más lógica

        detenerNivel();            // detiene timers y actualizaciones

        QMessageBox::information(nullptr, "¡Victoria!", "¡Nivel 1 completado!");
        emit nivelCompletado();
        return;
    }

    // ----- DETECCIÓN DE COLISIÓN (solo aviso) -----
    if (jugador) {
        for (QGraphicsItem *item : jugador->collidingItems()) {
            if (dynamic_cast<Tubo_caliente*>(item)) {
                qDebug() << "Colisión con tubo caliente!";
            }
        }
    }

    // ----- SOBRECALENTAMIENTO DEL TUBO -----
    if (tuboCaliente && tuboCaliente->getTemperatura() >= 100) {

        qDebug() << "Tubo llegó a 100°C! Perdiendo una vida...";

        juego->restarVida();
        actualizarVidas(juego->getVidas());

        if (!juego->haPerdido()) {
            tuboCaliente->reiniciarTemperatura(80);
            return;
        }

        // ----- GAME OVER -----
        juegoTerminado = true;
        detenerNivel();     // <- clave para evitar repeticiones

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
    // y = 550 piso - 75 (alto jugador) = 475
    jugador->setPos(100, 475);
    this->juego = j; //guardar en la variable miembro
    j->setNivel(this);
     escena->addItem(jugador);
}

void nivel_1::actualizarVidas(int vidas)
{
    if (escenario)
        escenario->actualizarVidas(escena, vidas);
}

void nivel_1::setJuego(Juego *j)
{
    this->juego = j; //guardar en la variable miembro
    j->setNivel(this);
}

void nivel_1::enfriarTubo()
{
    if (!jugador || !tuboCaliente)
        return;

    // 1. Revisar si el jugador tiene carga
    if (!jugador->tieneCarga()) {
        qDebug() << "No hay carga para enfriar. Presione R para recargar.";
        return;
    }

    // 2. Verificar si está tocando el tubo caliente
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

    // 3. Enfriar 10 grados
    tuboCaliente->enfriar(25);
    qDebug() << "❄ Enfriado → Temperatura:" << tuboCaliente->getTemperatura();

    // 4. Gastar la carga
    jugador->usarCarga();
    qDebug() << "Carga usada. Ahora está en 0.";

    // 5. Retroceso forzado del jugador
    jugador->setX(jugador->x() - 40);
}

void nivel_1::detenerNivel()
{
    for (QObject *obj : escena->children()) {
        if (QTimer *t = qobject_cast<QTimer*>(obj)) {
            t->stop();
        }
    }
}

