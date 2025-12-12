#include "menu.h"
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QMessageBox>

Menu::Menu(QObject *parent)
    : QGraphicsScene(parent)
{
    setSceneRect(0, 0, 800, 600);

    // Título
    QGraphicsTextItem *titulo = new QGraphicsTextItem("Menu Principal");
    titulo->setDefaultTextColor(Qt::white);
    titulo->setFont(QFont("Arial", 32, QFont::Bold));
    titulo->setPos(250, 40);
    addItem(titulo);

    // Botones
    crearBoton("Nivel 1", 150, 1);
    crearBoton("Nivel 2", 250, 2);
    crearBoton("Nivel 3", 350, 3);
    crearBoton("Salir",   450, 99);
}

void Menu::crearBoton(const QString &texto, int y, int nivel)
{
    // Rectángulo del botón
    QGraphicsRectItem *rect = new QGraphicsRectItem(250, y, 300, 60);
    rect->setBrush(Qt::darkGray);
    rect->setPen(QPen(Qt::white, 3));
    rect->setData(0, nivel);
    addItem(rect);

    // Texto centrado dentro del rectángulo
    QGraphicsTextItem *label = new QGraphicsTextItem(texto);
    label->setDefaultTextColor(Qt::white);
    label->setFont(QFont("Arial", 22));

    // Posición ABSOLUTA: dentro del rectángulo
    label->setPos(250 + 80, y + 12); // x = 250 (inicio rect) + margen, y = y + margen
    addItem(label); // ✅ Añadir directamente a la escena
}

void Menu::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pos = event->scenePos();
    QList<QGraphicsItem*> lista = items(pos);

    for (QGraphicsItem *item : lista)
    {
        QGraphicsRectItem *rect = qgraphicsitem_cast<QGraphicsRectItem*>(item);

        // Si fue texto, tomar el padre (rectángulo)
        if (!rect)
        {
            if (QGraphicsTextItem *txt = qgraphicsitem_cast<QGraphicsTextItem*>(item))
                rect = qgraphicsitem_cast<QGraphicsRectItem*>(txt->parentItem());
        }

        if (!rect)
            continue;

        int nivel = rect->data(0).toInt();

        if (nivel == 99)
        {
            QApplication::quit();
            return;
        }

        emit seleccionarNivel(nivel);
        return;
    }

    QGraphicsScene::mousePressEvent(event);
}
