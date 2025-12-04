#ifndef TUBO_CALIENTE_H
#define TUBO_CALIENTE_H
#include "tubo.h"

class Tubo_caliente :public Tubo
{

public:
   Tubo_caliente(int x, int y, int w, int h);

    void actualizar();          // sube temp y revisa explosión
    void subirTemperatura();    // aumenta calor
    bool estadoTemperatura();
    bool estaExplotado() const;
    void pinta_tubo(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr);
private:
    void cambiar_imagen();
};

#endif // TUBO_CALIENTE_H
