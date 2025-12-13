#ifndef AGENTE_AUTOMATA_H
#define AGENTE_AUTOMATA_H
#include <QObject>
#include <QTimer>
class nivel_3;

// agente que mueve al jugador automáticamente en el nivel 3
class AgenteAutomata : public QObject
{
    Q_OBJECT
public:
    explicit AgenteAutomata(nivel_3 *nivel, QObject *parent = nullptr);
    void iniciar();
    void detener();

private:
    nivel_3 *nivel = nullptr;
    QTimer *timer = nullptr;  // timer para movimiento automático
    bool direccionDerecha = true;  // controla la dirección del movimiento
};
#endif // AGENTE_AUTOMATA_H
