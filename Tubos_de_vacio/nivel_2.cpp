#include "nivel_2.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsRectItem>
#include <QObject>
#include <QVector>
#include <QMessageBox>
#include "nivel_2.h"






void nivel_2::detenerNivel()
{
    // detiene todos los timers del nivel
    for (QObject *obj : this->children()) {
        if (QTimer *t = qobject_cast<QTimer*>(obj)) {
            t->stop();
        }
    }

    // detiene timers de la escena también
    for (QObject *obj : escena->children()) {
        if (QTimer *t = qobject_cast<QTimer*>(obj)) {
            t->stop();
        }
    }

    juegoTerminado = true;
}

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
    cargarInventarioFrio();
}

void nivel_2::cargarFondo()
{
    qDebug() << "  cargarFondo - IN";
    // carga la imagen de fondo del nivel 2
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
    if (juegoTerminado) return;
    // crea tres tubos calientes en diferentes posiciones con diferentes temperaturas iniciales
    // tubo inferior (más lento)
    TuboInfo t1;
    t1.caliente = new Tubo_caliente(700, 400, 50, 150);
    t1.frio = new Tubo_Frio(700, 400, 50, 150);
    t1.frio->setVisible(false);
    t1.temperatura = 80;
    escena->addItem(t1.caliente);
    escena->addItem(t1.frio);
    tubos.append(t1);

    // tubo superior izquierda (rápido)
    TuboInfo t2;
    t2.caliente = new Tubo_caliente(50, 50, 50, 150);
    t2.frio = new Tubo_Frio(50, 50, 50, 150);
    t2.frio->setVisible(false);
    t2.temperatura = 60;
    escena->addItem(t2.caliente);
    escena->addItem(t2.frio);
    tubos.append(t2);

    // tubo superior derecha (intermedio)
    TuboInfo t3;
    t3.caliente = new Tubo_caliente(750, 70, 50, 150);
    t3.frio = new Tubo_Frio(750, 70, 50, 150);
    t3.frio->setVisible(false);
    t3.temperatura = 50;
    escena->addItem(t3.caliente);
    escena->addItem(t3.frio);
    tubos.append(t3);

    // timer que aumenta la temperatura cada segundo
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this]() {
        for (TuboInfo &t : tubos) {
            if (t.temperatura < 100) {
                t.temperatura++;
            }
            // si el tubo llega a 100°c explota y se pierde una vida
            if (t.temperatura >= 100 && !t.cambiado) {
                qDebug() << "¡Tubo explotó! Perdiendo vida...";
                juego->restarVida();
                actualizarVidas(juego->getVidas());

                if (juego->haPerdido()) {
                    detenerNivel();

                    QMessageBox::critical(nullptr, "Game Over", "¡Perdiste!");

                    emit gameOver();
                    return;
                } else {
                    // reinicia el tubo después de explotar
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
    // crea obstáculos (cajas) que bloquean el camino del jugador
    QGraphicsRectItem* caja1 = escenario->crearObstaculo(300, 300, 30, 250);
    QGraphicsRectItem* caja2 = escenario->crearObstaculo(500, 200, 40, 350, Qt::darkRed);
    QGraphicsRectItem* caja3 = escenario->crearObstaculo(50, 180, 250, 30);
    escena->addItem(caja1);
    escena->addItem(caja2);
    escena->addItem(caja3);
}

void nivel_2::cargarJugador(Juego *j)
{


    // timer para física del jugador (gravedad y movimiento)
    QTimer *timerFisica = new QTimer(this);
    connect(timerFisica, &QTimer::timeout, this, &nivel_2::actualizarFisica);
    timerFisica->start(16);

    //
    juego = j;

    jugador = new Jugador();

    jugador->setModoTopDown(true);  // vista cenital

    jugador->setPos(200, 400);
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

    // verifica si todos los tubos fueron enfriados (victoria)
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
    // muestra el tiempo en consola
    qDebug() << "Tiempo restante:" << tiempoRestante;
}

void nivel_2::verificarCambioTubos()
{
    if (!jugador) return;

    for (TuboInfo &t : tubos) {
        if (t.cambiado) continue;

        if (jugador->collidesWithItem(t.caliente)) {
            // enfría el tubo 10 grados al tocarlo
            t.temperatura = qMax(0, t.temperatura - 10);
            qDebug() << "❄️ Enfriado. Nueva temp:" << t.temperatura;

            // si llega a 0°c se completa
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
    if (tubo.cambiado) return; // ya fue resuelto

    qDebug() << "¡Tubo explotó! Perdiendo una vida...";
    juego->restarVida();
    actualizarVidas(juego->getVidas());

    if (juego->haPerdido()) {
        QMessageBox::critical(nullptr, "Game Over", "¡Has perdido todas tus vidas!");
        return;
    }

    // reinicia el tubo
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
    // muestra las 3 vidas iniciales
    escenario->cargarVidas(escena, 3);
}

void nivel_2::actualizarVidas(int vidas)
{
    // actualiza el contador visual de vidas
    escenario->actualizarVidas(escena, vidas);
}



bool nivel_2::jugadorTocaTuboCaliente(int &indiceTubo)
{
    if (!jugador)
        return false;

    QVector<QGraphicsItem*> colisiones = jugador->collidingItems();

    // detecta qué tubo caliente está tocando el jugador
    for (int i = 0; i < tubos.size(); i++)
    {
        if (colisiones.contains(tubos[i].caliente))
        {
            indiceTubo = i;
            return true;
        }
    }

    return false;
}
QPointF ultimaPosicionJugador;

void nivel_2::actualizarFisica()
{
    if (!jugador) return;
    // guarda la última posición antes de mover (para revertir si choca)
    ultimaPosicionJugador = jugador->pos();

    // aplica física solo cuando el jugador está saltando
    if (jugador->activarFisica) {

        // paso inicial del salto (impulso extra)
        if (jugador->pasoInicialSalto) {
            jugador->setY(jugador->y() - 25);
            jugador->setX(jugador->x() + 8);
            jugador->pasoInicialSalto = false;
        }

        // aplica gravedad
        jugador->velocidadY += jugador->gravedad;

        // mueve verticalmente
        jugador->setY(jugador->y() + jugador->velocidadY);

        // avanza horizontalmente durante el salto
        if (jugador->saltando) {
            jugador->setX(jugador->x() + 4);
        }

        // detecta si tocó el piso
        float piso = 400;

        if (jugador->y() >= piso) {
            jugador->setY(piso);
            jugador->velocidadY = 0;

            jugador->enElSuelo = true;
            jugador->saltando = false;

            jugador->activarFisica = false;  // termina el salto
        }
    }

    // evita que el jugador salga de los límites de la pantalla
    int anchoJugador = jugador->boundingRect().width();

    // límite izquierdo
    if (jugador->x() < 0)
        jugador->setX(0);

    // límite derecho
    if (jugador->x() > escena->width() - anchoJugador)
        jugador->setX(escena->width() - anchoJugador);



    // detecta colisiones con obstáculos
    QVector<QGraphicsItem*> colisiones = jugador->collidingItems();

    for (QGraphicsItem* item : colisiones) {

        if (dynamic_cast<QGraphicsRectItem*>(item)) {
            jugador->setPos(ultimaPosicionJugador);
            qDebug() << "Jugador tocó un OBSTÁCULO";
        }

        if (dynamic_cast<QGraphicsRectItem*>(item)) {
            // revierte la posición al chocar
            jugador->setPos(ultimaPosicionJugador);
            jugador->velocidadY = 0;
            jugador->saltando = false;
            jugador->activarFisica = false;

            qDebug() << "Jugador BLOQUEADO por un OBSTÁCULO";

            return;
        }
    }

    intentarRecogerTuboFrio();
    intentarColocarTuboFrio();
}

void nivel_2::saltar()
{
    if (!jugador) return;
    if (jugador->saltando) return;  // evita doble salto

    jugador->saltando = true;
    jugador->enElSuelo = false;

    jugador->velocidadY = jugador->impulsoSalto; // impulso hacia arriba

    jugador->activarFisica = true;  // activa la física durante el salto
}

void nivel_2::cargarInventarioFrio()
{
    inventarioFrio.clear();

    int baseX = 50;
    int baseY = 450;

    // crea 3 tubos fríos en el inventario para recoger
    for (int i = 0; i < 3; i++) {

        Tubo_Frio *frio = new Tubo_Frio(baseX + (i * 70), baseY, 50, 150);

        frio->setZValue(5);
        frio->setVisible(true);

        escena->addItem(frio);
        inventarioFrio.append(frio);
    }

    qDebug() << "Inventario de tubos fríos creado con" << inventarioFrio.size() << "tubos.";

}

void nivel_2::intentarRecogerTuboFrio()
{
    // verifica si el jugador puede recoger un tubo frío del inventario
    if (!jugador || jugador->estaLlevandoTuboFrio())
        return;

    for (int i = 0; i < inventarioFrio.size(); i++)
    {
        Tubo_Frio* frio = inventarioFrio[i];

        if (jugador->collidesWithItem(frio))
        {
            qDebug() << "Jugador recogió un tubo frío del inventario.";

            // oculta el tubo del inventario
            frio->setVisible(false);

            // lo asigna al jugador
            jugador->setLlevandoTuboFrio(true);
            jugador->setTuboEnEspalda(frio);

            // lo hace seguir al jugador visualmente
            frio->setParentItem(jugador);
            frio->setPos(-10, -40); // atrás del jugador

            inventarioFrio.removeAt(i);

            break;
        }
    }
}


void nivel_2::intentarColocarTuboFrio()
{
    // intenta colocar el tubo frío que lleva en un tubo caliente
    if (!jugador || !jugador->estaLlevandoTuboFrio())
        return;

    bool colocoTubo = false;

    for (TuboInfo &t : tubos)
    {
        if (!t.cambiado && jugador->collidesWithItem(t.caliente))
        {
            qDebug() << "el jugador coloca el tubo frío en el tubo caliente";

            Tubo_Frio* frio = jugador->getTuboEnEspalda();
            if (!frio) return;

            // reemplaza el tubo caliente por el frío
            t.caliente->setVisible(false);

            frio->setParentItem(nullptr);
            QPointF posCaliente = t.caliente->pos();
            frio->setPos(posCaliente);
            frio->setVisible(true);

            t.cambiado = true;
            t.frio = frio;
            t.temperatura = 0;

            jugador->setLlevandoTuboFrio(false);
            jugador->setTuboEnEspalda(nullptr);

            colocoTubo = true;
            break;
        }
    }

    if (!colocoTubo) return;

    // verifica si todos los tubos fueron enfriados (victoria)
    bool todos = true;
    for (const TuboInfo &x : tubos) {
        if (!x.cambiado) {
            todos = false;
            break;
        }
    }

    if (todos) {
        detenerNivel();
        QMessageBox::information(nullptr, "victoria", "todos los tubos están fríos");
        emit nivelCompletado();
    }
}
