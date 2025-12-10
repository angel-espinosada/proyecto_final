#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include "tubo_caliente.h"
#include "tubo_frio.h"
#include "nivel_1.h"
#include "juego.h"
#include "menu.h"
#include "nivel_1.h"
#include "nivel_2.h"
#include "nivel_3.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Crear el menú
    Menu *menu = new Menu();
    ui->graphicsView->setScene(menu);

    // --- Conectar selección de niveles ---
    connect(menu, &Menu::seleccionarNivel, this, [this](int nivel){

        // Crear una nueva escena para el nivel
        QGraphicsScene *escena = new QGraphicsScene(this);
        escena->setSceneRect(0,0,800,600);
        ui->graphicsView->setScene(escena);

        Juego *juego = new Juego();

        if (nivel == 1) {
            nivel_1 *n1 = new nivel_1(escena);
            n1->cargarEscenario();
            n1->cargarSuelo();
            n1->cargarTubos();
            n1->cargarTecho();
            n1->cargarJugador(juego);
            n1->setJuego(juego);
            n1->cargarvida();
            n1->cargarFondo();
        }
        else if (nivel == 2) {
            nivel_2 *n2 = new nivel_2(escena);

            n2->cargarEscenario();
            n2->cargarFondo();
             qDebug() << "Fondo cargado";
            n2->cargarSuelo();
            n2->cargarTubos();
            n2->cargarObstaculos();
            n2->cargarJugador(juego);
            qDebug() << "Jugador cargado";


        }
        else if (nivel == 3) {
            nivel_3 *n3 = new nivel_3(escena);
            n3->inicializar();
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
