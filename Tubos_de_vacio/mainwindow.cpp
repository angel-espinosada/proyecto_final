#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include "tubo_caliente.h"
#include "tubo_frio.h"
#include "nivel_1.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   QGraphicsScene *escenario = new QGraphicsScene(this);
    escenario->setSceneRect(0,0,1000,600);
    ui->graphicsView->setScene(escenario);
    nivel_1 *nivel1 = new nivel_1(escenario);

    nivel1->cargarEscenario();
    nivel1->cargarSuelo();
    nivel1->cargarTubos();

    /*QGraphicsRectItem *cuadrado = new QGraphicsRectItem(150, 100, 10, 100);
    QGraphicsRectItem *cuadrado1 = new QGraphicsRectItem(200, 100, 10, 100);
    cuadrado->setBrush(Qt::red);
    cuadrado1->setBrush(Qt::green);
    escenario->addItem(cuadrado);
    escenario->addItem(cuadrado1);*/
    /*
    mituboCaliente= new Tubo_caliente(120,120,50,150);
    escenario->addItem(mituboCaliente);
    mitubofrio=new Tubo_Frio(140,140,50,150);
    escenario->addItem(mitubofrio);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
