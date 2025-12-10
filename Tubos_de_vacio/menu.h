#ifndef MENU_H
#define MENU_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsView>

class Menu:public QGraphicsScene
{
    Q_OBJECT

private:
    void crearBoton(QString texto, int y, int nivel);
public:
    Menu(QObject *parent =nullptr);

signals:
    void seleccionarNivel(int nivel);
};

#endif // MENU_H
