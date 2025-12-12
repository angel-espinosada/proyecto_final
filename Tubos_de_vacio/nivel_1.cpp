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
    // ----- MOSTRAR INSTRUCCIONES -----
    if (mostrarInstruccionesInicio) {
        if (textoInstrucciones == nullptr) {
            textoInstrucciones = new QGraphicsTextItem(
                "Usa A / D para moverte\n"
                "Presiona R en la esquina para recargar\n"
                "Presiona E junto al tubo para enfriarlo"
                );
            textoInstrucciones->setDefaultTextColor(Qt::white);
            textoInstrucciones->setPos(200, 80);
            textoInstrucciones->setZValue(1000);
            escena->addItem(textoInstrucciones);
        }

        framesInstrucciones++;

        if (framesInstrucciones > 360) {
            escena->removeItem(textoInstrucciones);
            delete textoInstrucciones;
            textoInstrucciones = nullptr;
            mostrarInstruccionesInicio = false;
        }
    }
    // ----- VICTORIA -----
    if (tuboCaliente && tuboCaliente->getTemperatura() <= 50 && !victoriaMostrada) {
        victoriaMostrada = true;

        QMessageBox::information(nullptr, "¡Victoria!", "¡Nivel 1 completado!");

        emit nivelCompletado();
        return;
    }

    // ----- DETECCIÓN DE COLISIÓN CON TUBO CALIENTE -----
    if (jugador) {
        for (QGraphicsItem* item : jugador->collidingItems()) {
            if (dynamic_cast<Tubo_caliente*>(item)) {
                qDebug() << "Colisión con tubo caliente!";
                // Aquí enfriaremos después
            }
        }
    }

    // ----- SOBRECALENTAMIENTO DEL TUBO -----
    if (tuboCaliente && tuboCaliente->getTemperatura() >= 100) {
        qDebug() << "Tubo llegó a 100°C! Perdiendo una vida...";

        // Restar vida
        this->juego->restarVida();
        actualizarVidas(this->juego->getVidas());

        if (!this->juego->haPerdido()) {
            // Reiniciar temperatura a un valor seguro
            tuboCaliente->reiniciarTemperatura(80);
            qDebug() << "Tubo reiniciado. Vidas restantes:" << this->juego->getVidas();
        } else {
            QMessageBox msg(QMessageBox::Critical,
                            "Game Over",
                            "¡Has perdido todas tus vidas!\nInténtalo de nuevo.",
                            QMessageBox::Ok);

            msg.exec();   // ✔ muestra y espera que cierren

            emit gameOver(); // ✔ vuelve al menú
            qDebug() << "Juego terminado! No se reinicia el tubo.";
        }
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

