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

        tubos.clear();// Limpiar

        // Tubo inferior
        TuboInfo t1;
        t1.caliente = new Tubo_caliente(700, 400, 50, 150);
        escena->addItem(t1.caliente);

        t1.frio = new Tubo_Frio(700, 400, 50, 150);
        t1.frio->setVisible(false);
        escena->addItem(t1.frio);

        tubos.append(t1);


        // Tubo superio Izquierda
        TuboInfo t2;
        t2.caliente = new Tubo_caliente(50, 50, 50, 150);
        escena->addItem(t2.caliente);

        t2.frio = new Tubo_Frio(50, 50, 50, 150);
        t2.frio->setVisible(false);
        escena->addItem(t2.frio);

        tubos.append(t2);


        // Tubo superior derecha
        TuboInfo t3;
        t3.caliente = new Tubo_caliente(750, 70, 50, 150);
        escena->addItem(t3.caliente);

        t3.frio = new Tubo_Frio(750, 70, 50, 150);
        t3.frio->setVisible(false);
        escena->addItem(t3.frio);

        tubos.append(t3);

        qDebug() << "Tubos nivel 2 cargados. Total:" << tubos.size();
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
    verificarCambioTubos();
    // Por ahora solo lo vemos en consola:
    qDebug() << "Tiempo restante:" << tiempoRestante;
}

void nivel_2::verificarCambioTubos()
{

    int indice = -1;

    if (jugadorTocaTuboCaliente(indice))
    {
        qDebug() << "Colisión con tubo caliente #" << indice;
    }
    if (!jugador) return;

    for (TuboInfo &t : tubos)
    {
        if (t.cambiado)
            continue;   // ya fue reemplazado, saltar

        // Detectar colisión
        if (jugador->collidesWithItem(t.caliente))
        {
            qDebug() << " Tubo reemplazado!";

            // Ocultar caliente
            t.caliente->setVisible(false);

            // Mostrar frío
            t.frio->setVisible(true);

            // Marcar completado
            t.cambiado = true;

            // Apagar calentamiento
            if (t.timer)
                t.timer->stop();
        }
    }
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
        for (TuboInfo &t : tubos) {
            if (t.caliente && jugador->collidesWithItem(t.caliente)) {
                qDebug() << "✅ ¡COLISIÓN CON TUBO CALIENTE!";
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

