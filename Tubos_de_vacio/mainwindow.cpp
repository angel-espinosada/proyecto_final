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
    menu = new Menu();
    ui->graphicsView->setScene(menu);

    // --- Conectar selección de niveles ---
    connect(menu, &Menu::seleccionarNivel, this, [this](int nivel){
        if (nivel == 99) {
            QApplication::quit();
            return;
        }
        // Crear una nueva escena para el nivel
        QGraphicsScene *escena = new QGraphicsScene(this);
        escena->setSceneRect(0,0,800,600);
        ui->graphicsView->setScene(escena);

        Juego *juego = new Juego();

        if (nivel == 1) {
            nivel_1 *n1 = new nivel_1(escena);

            connect(n1, &nivel_1::gameOver, this, [this, escena]() {
                ui->graphicsView->setScene(menu);
                ui->graphicsView->resetTransform();
                escena->deleteLater();
            });
            connect(n1, &nivel_1::nivelCompletado, this, [this, escena]() {
                ui->graphicsView->setScene(menu);   // primero cambiás la escena
                ui->graphicsView->resetTransform(); // luego limpiás la vista
                escena->deleteLater();              // último: destruir escena
            });
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

            connect(n2, &nivel_2::gameOver, this, [this, escena]() {
                ui->graphicsView->setScene(menu);
                ui->graphicsView->resetTransform();
                escena->deleteLater();
            });

            connect(n2, &nivel_2::nivelCompletado, this, [this, escena]() {
                ui->graphicsView->setScene(menu);
                ui->graphicsView->resetTransform();
                escena->deleteLater();
            });

            n2->cargarEscenario();
            n2->cargarFondo();
            n2->cargarvida();
            n2->cargarTubos();
            n2->cargarObstaculos();
            n2->cargarJugador(juego);
            n2->setJuego(juego);
        }




        else if (nivel == 3) {
            nivel_3 *n3 = new nivel_3(escena);
            n3->inicializar();
            n3->cargarEscenario();

            n3->cargarvida();
            n3->cargarJugador(juego);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
