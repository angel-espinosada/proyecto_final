#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QGraphicsScene>
#include <QMainWindow>
#include "tubo_caliente.h"
#include "tubo_frio.h"
#include "menu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Menu *menu;
    Tubo_caliente *mituboCaliente;
    Tubo_Frio *mitubofrio;
    QGraphicsScene *escenario;
};
#endif // MAINWINDOW_H
