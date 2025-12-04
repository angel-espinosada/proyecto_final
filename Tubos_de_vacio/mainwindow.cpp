#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include "tubo_caliente.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   QGraphicsScene *escenario = new QGraphicsScene(this);
    escenario->setSceneRect(0,0,600,400);
    ui->graphicsView->setScene(escenario);
    QGraphicsRectItem *cuadrado = new QGraphicsRectItem(150, 100, 10, 100);
    QGraphicsRectItem *cuadrado1 = new QGraphicsRectItem(200, 100, 10, 100);
    cuadrado->setBrush(Qt::red);
    cuadrado1->setBrush(Qt::green);
    escenario->addItem(cuadrado);
    escenario->addItem(cuadrado1);
    //int x=ui->le_X->text().toInt();
    //int y=ui->le_Y->text().toInt();
    mituboCaliente= new Tubo_caliente(120,120,50,50);
    escenario->addItem(mituboCaliente);
}

MainWindow::~MainWindow()
{
    delete ui;
}
