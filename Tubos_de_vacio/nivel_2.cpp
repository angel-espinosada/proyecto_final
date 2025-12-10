#include "nivel_2.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QObject>
#include <QMessageBox>


nivel_2::nivel_2(QGraphicsScene *escena)
{
    this->escena = escena;
    qDebug() << "Constructor nivel_2 - INICIO";
}

void nivel_2::cargarEscenario()
{
    qDebug() << "cargarEscenario - INICIO";
    escenario = new Escenario_juego(0, 0, 800, 600, Qt::darkGray);
    qDebug() << "Escenario creado";
    escena->addItem(escenario);
    qDebug() << " cargarEscenario - FIN";
}

void nivel_2::cargarFondo()
{
    qDebug() << "  cargarFondo - IN";
    // usa el mismo formato del nivel 1
    QGraphicsPixmapItem *fondo = escenario->crearFondo(
        ":/imagenes/fondo_nivel2.PNG",
        0, 0, 800, 600
        );
    fondo->setZValue(-10);
    escena->addItem(fondo);
     qDebug() << " cargarFondo - finnnn";
}



void nivel_2::cargarTubos()
{
    int alturaSuelo = 550;
    int altoTubo = 150;

    tuboCaliente = new Tubo_caliente(700, alturaSuelo - altoTubo, 50, 150);
    escena->addItem(tuboCaliente);

    tuboFrio = new Tubo_Frio(700, alturaSuelo - altoTubo, 50, 150);
    tuboFrio->setVisible(false);   // empieza oculto
    escena->addItem(tuboFrio);

    tuboSuperiorIzq = new Tubo_caliente(0, 0, 50, 150);
    escena->addItem(tuboSuperiorIzq);

    tuboSuperiorDer = new Tubo_caliente(750, 0, 50, 150);
    escena->addItem(tuboSuperiorDer);
}


void nivel_2::cargarObstaculos()
{
    QGraphicsRectItem* caja1 = escenario->crearObstaculo(300, 300, 30, 250);
    QGraphicsRectItem* caja2 = escenario->crearObstaculo(500, 200, 40, 350, Qt::darkRed);
    QGraphicsRectItem* caja3 = escenario->crearObstaculo(100, 300, 30, 250);
    escena->addItem(caja1);
    escena->addItem(caja2);
    escena->addItem(caja3);
}

void nivel_2::cargarJugador(Juego *j)
{
    juego = j;

    jugador = new Jugador();

    jugador->setModoTopDown(true);  //  Vista cenital

    jugador->setPos(200, 400);      // Un punto visible
    escena->addItem(jugador);

    qDebug() << "Jugador nivel 2 creado y agregado a la escena.";
}

void nivel_2::actualizar()
{
    tiempoRestante--;

    // Por ahora solo lo vemos en consola:
    qDebug() << "Tiempo restante:" << tiempoRestante;
}

void nivel_2::setJuego(Juego *j)
{
    this->juego = j;
}

void nivel_2::cargarvida()
{
    escenario->cargarVidas(escena, 3);
}

void nivel_2::actualizarVidas(int vidas)
{
    escenario->actualizarVidas(escena, vidas);
}

void nivel_2::verificarCollicion()
{
    if (mostrarInstruccionesInicio) {
        if (textoInstrucciones == nullptr) {
            // Crear el texto la primera vez
            textoInstrucciones = new QGraphicsTextItem(
                "Usa A / D para moverte\n"
                "Presiona R en la esquina para recargar\n"
                " Presiona E junto al tubo para enfriarlo"
                );
            textoInstrucciones->setDefaultTextColor(Qt::white);
            textoInstrucciones->setPos(200, 80);
            textoInstrucciones->setZValue(1000);
            escena->addItem(textoInstrucciones);
        }

        framesInstrucciones++;
        // 360 frames ≈ 6 segundos (si tu juego corre a 60 FPS)
        if (framesInstrucciones > 360) {
            escena->removeItem(textoInstrucciones);
            delete textoInstrucciones;
            textoInstrucciones = nullptr;
            mostrarInstruccionesInicio = false; // no volver a mostrar
        }
    }

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
        }

        else {
            QMessageBox::critical(nullptr, "Game Over", "¡Has perdido todas tus vidas!\nInténtalo de nuevo.");
            qDebug() << "Juego terminado! No se reinicia el tubo."; }
    }
    if (tuboCaliente && tuboCaliente->getTemperatura() <= 50) {
        QMessageBox::information(nullptr, "¡Victoria!", "¡Enfriaste el tubo completamente!\n¡Nivel 1 completado!");
    }
}

