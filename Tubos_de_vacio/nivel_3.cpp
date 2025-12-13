#include "nivel_3.h"
#include <QDebug>
#include <QTimer>
#include <QMessageBox>
#include "agente_automata.h"

AgenteAutomata *agente = nullptr;

nivel_3::nivel_3(QGraphicsScene *escena, QObject *parent)
    : QObject(parent), escena(escena)
{
    qDebug() << "constructor nivel 3";
}


void nivel_3::inicializar()
{
    // inicializa todo el tablero con celdas seguras (valor 1)
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            tablero[i][j] = 1;
        }
    }

    // coloca minas de prueba en posiciones específicas (valor 0)
    tablero[2][3] = 0;
    tablero[4][5] = 0;
    tablero[6][1] = 0;
    qDebug() << "Nivel 3 cargado (placeholder).";
}

void nivel_3::cargarEscenario()
{
    // crea el fondo del juego
    escenario = new Escenario_juego(0, 0, 800, 600, Qt::darkGray);
    qDebug() << "Escenario creado";
    escena->addItem(escenario);
    qDebug() << " cargarEscenario ";
    inicializar();
    dibujarTablero();
    dibujarMinas();

}



void nivel_3::cargarvida()
{
    // muestra las 3 vidas iniciales en pantalla
    escenario->cargarVidas(escena, 3);
}

void nivel_3::cargarJugador(Juego *j)
{



    //
    juego = j;

    jugador = new Jugador();
    jugador->setNivel3Activo(true);
    jugador->setModoTopDown(true);  // vista cenital

    jugador->setPos(200, 400);
    escena->addItem(jugador);

    // posición inicial del jugador en el tablero
    filaJugador = 0;
    colJugador = 0;
    jugador->setPos(
        offsetX + colJugador * tamCelda + margenCelda,
        offsetY + filaJugador * tamCelda + margenCelda
        );

    qDebug() << "Jugador nivel 3 creado y agregado a la escena.";

    // conecta las teclas de movimiento del jugador
    jugador->disconnect();
    connect(jugador, &Jugador::pedirMoverArriba,
            this, [this](){ moverJugador(-1, 0); });

    connect(jugador, &Jugador::pedirMoverAbajo,
            this, [this](){ moverJugador(1, 0); });

    connect(jugador, &Jugador::pedirMoverIzquierda,
            this, [this](){ moverJugador(0, -1); });

    connect(jugador, &Jugador::pedirMoverDerecha,
            this, [this](){ moverJugador(0, 1); });

    // crea e inicia el agente autómata
    agente = new AgenteAutomata(this, this);
    agente->iniciar();
}

void nivel_3::moverJugador(int df, int dc)
{
    if (juegoTerminado) return;

    qDebug() << "moverJugador fue llamado";

    // calcula la nueva posición
    int nuevaFila = filaJugador + df;
    int nuevaCol  = colJugador + dc;

    // verifica que no salga del tablero
    if (nuevaFila < 0 || nuevaFila >= filas) return;
    if (nuevaCol < 0 || nuevaCol >= columnas) return;

    filaJugador = nuevaFila;
    colJugador  = nuevaCol;

    // actualiza la posición visual del jugador
    jugador->setPos(
        offsetX + colJugador * tamCelda + margenCelda,
        offsetY + filaJugador * tamCelda + margenCelda
        );

    // verifica si pisó una mina activa
    if (tablero[filaJugador][colJugador] == 0) {

        qDebug() << "MINA ACTIVADA en fila:" << filaJugador
                 << "col:" << colJugador;

        tablero[filaJugador][colJugador] = -1; // marca la mina como usada

        juego->restarVida();
        qDebug() << " Vida restada. Vidas actuales:"
                 << juego->getVidas();

        actualizarVidas(juego->getVidas());

        // verifica si perdió todas las vidas
        if (juego->getVidas() <= 0) {
            juegoTerminado = true;

            qDebug() << " GAME OVER - NIVEL 3";

            QMessageBox::critical(
                nullptr,
                "Game Over",
                "Has perdido todas las vidas"
                );

            return;
        }
    }
    else if (tablero[filaJugador][colJugador] == -1) {

        qDebug() << "Mina ya explotada en fila:"
                 << filaJugador << "col:" << colJugador;
    }
    else {

        qDebug() << " Celda segura fila:"
                 << filaJugador << "col:" << colJugador;
    }

    // verifica si ganó el nivel (todas las minas fueron activadas)
    if (!quedanMinas()) {

        juegoTerminado = true;

        qDebug() << "VICTORIA NIVEL 3";

        QMessageBox::information(
            nullptr,
            "Victoria",
            "¡Has superado el nivel 3!"
            );

        return;
    }
}

void nivel_3::actualizarVidas(int vidas)
{
    // actualiza el contador de vidas en pantalla
    if (escenario)
        escenario->actualizarVidas(escena, vidas);

}

void nivel_3::dibujarMinas()
{

    int tamCelda = 60;
    int tamMina  = 30;
    int margen   = (tamCelda - tamMina) / 2;

    // recorre el tablero y dibuja cuadros rojos donde hay minas
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

    // dibuja un tablero tipo ajedrez con colores alternados
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

bool nivel_3::quedanMinas()
{
    // verifica si todavía hay minas sin explotar en el tablero
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            if (tablero[f][c] == 0) {
                return true;
            }
        }
    }
    return false;
}


