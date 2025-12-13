#include "nivel_3.h"
#include <QDebug>
#include <QTimer>

nivel_3::nivel_3(QGraphicsScene *escena)
{
    this->escena = escena;
}
void nivel_3::inicializar()
{
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            tablero[i][j] = 1;
        }
    }

    // minas de prueba
    tablero[2][3] = 0;
    tablero[4][5] = 0;
    tablero[6][1] = 0;
    qDebug() << "Nivel 3 cargado (placeholder).";
}

void nivel_3::cargarEscenario()
{
    escenario = new Escenario_juego(0, 0, 800, 600, Qt::darkGray);
    qDebug() << "Escenario creado";
    escena->addItem(escenario);
    qDebug() << " cargarEscenario ";
    inicializar();
    dibujarTablero();
    dibujarMinas();

}

void nivel_3::cargarFondo()
{/*
    qDebug() << "  cargarFondo - IN";
    // usa el mismo formato del nivel 1
    QGraphicsPixmapItem *fondo = escenario->crearFondo(
        ":/imagenes/tablero.png",
        0, 0, 800, 600
        );
    QPixmap px = fondo->pixmap();
    tableroPixAncho = px.width();
    tableroPixAlto  = px.height();
    fondo->setZValue(-10);
    escena->addItem(fondo);
    tamCelda = tableroPixAncho / columnas;
    inicializar();
    dibujarMinas();*/
    qDebug() << " cargarFondo - finnnn";
}

void nivel_3::cargarvida()
{
    escenario->cargarVidas(escena, 3);
}

void nivel_3::cargarJugador(Juego *j)
{



    //
    juego = j;

    jugador = new Jugador();

    jugador->setModoTopDown(true);  //  Vista cenital

    jugador->setPos(200, 400);      // Un punto visible
    escena->addItem(jugador);

    filaJugador = 0;
    colJugador = 0;
    jugador->setPos(
        offsetX + colJugador * tamCelda + margenCelda,
        offsetY + filaJugador * tamCelda + margenCelda
        );

    qDebug() << "Jugador nivel 3 creado y agregado a la escena.";

    jugador->disconnect(); // por seguridad


}

void nivel_3::moverJugador(int df, int dc)
{
    int nuevaFila = filaJugador + df;
    int nuevaCol  = colJugador + dc;

    if (nuevaFila < 0 || nuevaFila >= filas) return;
    if (nuevaCol < 0 || nuevaCol >= columnas) return;

    filaJugador = nuevaFila;
    colJugador  = nuevaCol;

    jugador->setPos(
        offsetX + colJugador * tamCelda + margenCelda,
        offsetY + filaJugador * tamCelda + margenCelda
        );

    if (tablero[filaJugador][colJugador] == 0) {
        qDebug() << "pisó mina";
        juego->restarVida();
        actualizarVidas(juego->getVidas());
    }
}

void nivel_3::actualizarVidas(int vidas)
{
    if (escenario)
        escenario->actualizarVidas(escena, vidas);

}

void nivel_3::dibujarMinas()
{

        int tamCelda = 60;
        int tamMina  = 30;
        int margen   = (tamCelda - tamMina) / 2;

        for (int f = 0; f < filas; f++) {
            for (int c = 0; c < columnas; c++) {

                if (tablero[f][c] == 0) {

                    QGraphicsRectItem *mina =
                        new QGraphicsRectItem(
                            offsetX + c * tamCelda + margen,
                            offsetY + f * tamCelda + margen,
                            tamMina,
                            tamMina
                            );

                    mina->setBrush(Qt::red);
                    mina->setZValue(2);
                    escena->addItem(mina);
                    minasVisuales.append(mina);
                }
            }
        }
    }

void nivel_3::dibujarTablero()
{
     int tamCelda = 60;
        offsetX = 50;
        offsetY = 50;

        QPen borde(Qt::darkGray);
        QBrush claro(QColor(245, 240, 230));
        QBrush oscuro(QColor(180, 190, 200));

        for (int f = 0; f < filas; f++) {
            for (int c = 0; c < columnas; c++) {

                QBrush &color = ((f + c) % 2 == 0) ? claro : oscuro;

                QGraphicsRectItem *celda =
                    new QGraphicsRectItem(
                        offsetX + c * tamCelda,
                        offsetY + f * tamCelda,
                        tamCelda,
                        tamCelda
                        );

                celda->setBrush(color);
                celda->setPen(borde);
                celda->setZValue(0);
                escena->addItem(celda);
            }
        }
    }






