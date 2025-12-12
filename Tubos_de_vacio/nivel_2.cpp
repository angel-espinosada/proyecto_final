#include "nivel_2.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QObject>
#include <QVector>
#include <QMessageBox>
#include "nivel_2.h"





nivel_2::nivel_2(QGraphicsScene *escena)
{
    this->escena = escena;

}

void nivel_2::cargarEscenario()
{

    escenario = new Escenario_juego(0, 0, 800, 600, Qt::darkGray);
    qDebug() << "Escenario creado";
    escena->addItem(escenario);
    qDebug() << " cargarEscenario ";
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

    tubos.clear();

    // Tubo inferior (más lento)
    TuboInfo t1;
    t1.caliente = new Tubo_caliente(700, 400, 50, 150);
    t1.frio = new Tubo_Frio(700, 400, 50, 150);
    t1.frio->setVisible(false);
    t1.temperatura = 70; // Más bajo
    escena->addItem(t1.caliente);
    escena->addItem(t1.frio);
    tubos.append(t1);

    // Tubo superior izquierda (rápido)
    TuboInfo t2;
    t2.caliente = new Tubo_caliente(50, 50, 50, 150);
    t2.frio = new Tubo_Frio(50, 50, 50, 150);
    t2.frio->setVisible(false);
    t2.temperatura = 80;
    escena->addItem(t2.caliente);
    escena->addItem(t2.frio);
    tubos.append(t2);

    // Tubo superior derecha (intermedio)
    TuboInfo t3;
    t3.caliente = new Tubo_caliente(750, 70, 50, 150);
    t3.frio = new Tubo_Frio(750, 70, 50, 150);
    t3.frio->setVisible(false);
    t3.temperatura = 75;
    escena->addItem(t3.caliente);
    escena->addItem(t3.frio);
    tubos.append(t3);

    // Timer único
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        for (TuboInfo &t : tubos) {
            if (t.temperatura < 100) {
                t.temperatura++;
            }
            // Verificar explosión INMEDIATA
            if (t.temperatura >= 100 && !t.cambiado) {
                qDebug() << "¡Tubo explotó! Perdiendo vida...";
                juego->restarVida();
                actualizarVidas(juego->getVidas());

                if (juego->haPerdido()) {
                    QMessageBox::critical(nullptr, "Game Over", "¡Perdiste!");
                } else {
                    // Reiniciar
                    t.temperatura = 80;
                    t.cambiado = false;
                    t.caliente->setVisible(true);
                    t.frio->setVisible(false);
                }
            }
        }
    });
    timer->start(1000);

}



void nivel_2::cargarObstaculos()
{
    QGraphicsRectItem* caja1 = escenario->crearObstaculo(300, 300, 30, 250);
    QGraphicsRectItem* caja2 = escenario->crearObstaculo(500, 200, 40, 350, Qt::darkRed);
    QGraphicsRectItem* caja3 = escenario->crearObstaculo(50, 180, 250, 30);
    escena->addItem(caja1);
    escena->addItem(caja2);
    escena->addItem(caja3);
}

void nivel_2::cargarJugador(Juego *j)
{


    //Fisica
    QTimer *timerFisica = new QTimer(this);
    connect(timerFisica, &QTimer::timeout, this, &nivel_2::actualizarFisica);
    timerFisica->start(16);

    //
    juego = j;

    jugador = new Jugador();

    jugador->setModoTopDown(true);  //  Vista cenital

    jugador->setPos(200, 400);      // Un punto visible
    escena->addItem(jugador);

    connect(jugador, &Jugador::pedirSalto, this, &nivel_2::saltar);
    qDebug() << "Jugador nivel 2 creado y agregado a la escena.";
}

void nivel_2::verificarCollicion()
{
    if (!jugador) return;

    for (TuboInfo &t : tubos) {
        if (t.cambiado) continue; // ya es frío

        if (jugador->collidesWithItem(t.caliente)) {
            qDebug() << " ¡Tubo reemplazado por frío!";
            t.caliente->setVisible(false);
            t.frio->setVisible(true);
            t.cambiado = true;
        }
    }

    // Verificar victoria: ¿todos los tubos son fríos?
    bool todosCompletados = true;
    for (const TuboInfo &t : tubos) {
        if (!t.cambiado) {
            todosCompletados = false;
            break;
        }
    }
    if (todosCompletados) {
        QMessageBox::information(nullptr, "¡Victoria!", "¡Todos los tubos están fríos!");
    }
}

void nivel_2::actualizar()
{
    tiempoRestante--;
    verificarCambioTubos();
    // Por ahora solo lo vemos en consola:
    qDebug() << "Tiempo restante:" << tiempoRestante;
}

void nivel_2::verificarCambioTubos()
{
    if (!jugador) return;

    for (TuboInfo &t : tubos) {
        if (t.cambiado) continue;

        if (jugador->collidesWithItem(t.caliente)) {
            // Enfriar el tubo (ajusta la cantidad según quieras)
            t.temperatura = qMax(0, t.temperatura - 10);
            qDebug() << "❄️ Enfriado. Nueva temp:" << t.temperatura;

            // Verificar victoria (temp ≤ 0)
            if (t.temperatura <= 0) {
                t.caliente->setVisible(false);
                t.frio->setVisible(true);
                t.cambiado = true;
                qDebug() << "Tubo" << &t << "completado";
            }
        }
    }
}
void nivel_2::tuboExplotado(TuboInfo &tubo)
{
    if (tubo.cambiado) return; // Ya fue resuelto

    qDebug() << "¡Tubo explotó! Perdiendo una vida...";
    juego->restarVida();
    actualizarVidas(juego->getVidas());

    if (juego->haPerdido()) {
        QMessageBox::critical(nullptr, "Game Over", "¡Has perdido todas tus vidas!");
        return;
    }

    // Reiniciar el tubo
    tubo.temperatura = 50;
    tubo.cambiado = false;
    tubo.frio->setVisible(false);
    tubo.caliente->setVisible(true);
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



bool nivel_2::jugadorTocaTuboCaliente(int &indiceTubo)
{
    if (!jugador)
        return false;

    QVector<QGraphicsItem*> colisiones = jugador->collidingItems();

    for (int i = 0; i < tubos.size(); i++)
    {
        if (colisiones.contains(tubos[i].caliente))
        {
            indiceTubo = i;      // ← devolvemos qué tubo tocó
            return true;
        }
    }

    return false;
}

void nivel_2::actualizarFisica()
{



    if (!jugador) return;

    // Si la física no está activa, no mover nada
    if (!jugador->activarFisica)
        return;

    // PASO INICIAL DEL SALTO
    if (jugador->pasoInicialSalto) {
        jugador->setY(jugador->y() - 25);  // sube un poquito
        jugador->setX(jugador->x() + 8);   // avanza para pasar obstáculos
        jugador->pasoInicialSalto = false;
    }

    // APLICAR GRAVEDAD
    jugador->velocidadY += jugador->gravedad;

    // MOVER EN Y
    jugador->setY(jugador->y() + jugador->velocidadY);

    // SI ESTÁ SALTANDO, AVANZA EN X
    if (jugador->saltando) {
        jugador->setX(jugador->x() + 4);
    }

    // Piso
    float piso = 400;

    // DETECCIÓN DE PISO
    if (jugador->y() >= piso)
    {
        jugador->setY(piso);
        jugador->velocidadY = 0;

        jugador->enElSuelo = true;
        jugador->saltando = false;

        // DESACTIVAR FÍSICA
        jugador->activarFisica = false;
    }
}


void nivel_2::saltar()
{
    if (!jugador) return;
    if (jugador->saltando) return;  // no doble salto

    jugador->saltando = true;
    jugador->enElSuelo = false;

    jugador->velocidadY = jugador->impulsoSalto; // impulso hacia arriba

    jugador->activarFisica = true;  // activar física durante el salto
}
