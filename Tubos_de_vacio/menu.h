#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

class Menu : public QGraphicsScene
{
    Q_OBJECT

public:
    Menu(QObject *parent = nullptr);

signals:
    void seleccionarNivel(int nivel);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void crearBoton(const QString &texto, int y, int nivel);
};

#endif // MENU_H
