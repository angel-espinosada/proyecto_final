#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador
{
    int vidas;
    double tiempo;
    int liquido_enfriado;

public:
    Jugador();
    bool ganar();
    void perder_vida();
    void enfriar();

};

#endif // JUGADOR_H
