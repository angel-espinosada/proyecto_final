#include "menu.h"
#include <QGraphicsSimpleTextItem>
#include <QBrush>
#include <QFont>


void Menu::crearBoton(QString texto, int y, int nivel)
{
    QGraphicsRectItem *rect = new QGraphicsRectItem(250, y, 300, 60);
    rect->setBrush(QColor(70, 70, 70));
    rect->setPen(QPen(Qt::white, 2));
    addItem(rect);

    QGraphicsTextItem *label = new QGraphicsTextItem(texto);
    label->setDefaultTextColor(Qt::white);
    label->setFont(QFont("Arial", 20));
    label->setPos(340, y + 15);
    addItem(label);

    // Hacer clic
    rect->setFlag(QGraphicsItem::ItemIsSelectable);
    label->setFlag(QGraphicsItem::ItemIsSelectable);

    // Conexión
    connect(this, &QGraphicsScene::selectionChanged, [this, rect, nivel]() {
        if (rect->isSelected())
            emit seleccionarNivel(nivel);
    });
}

Menu::Menu(QObject *parent):QGraphicsScene(parent)
{
    setSceneRect(0,0,800,600);


    //fondo
    setBackgroundBrush(QColor(30,30,30));

    //Titulo

    QGraphicsTextItem *titulo = new QGraphicsTextItem("Tubos de vacio");
    titulo->setDefaultTextColor(Qt::white);
    titulo->setFont(QFont("Arial", 28, QFont::Bold));
    titulo->setPos(200, 50);
    addItem(titulo);

    // Botones
    crearBoton("Nivel 1", 200, 1);
    crearBoton("Nivel 2", 300, 2);
    crearBoton("Nivel 3", 400, 3);
    crearBoton("Cerrar", 500, 99);
}

