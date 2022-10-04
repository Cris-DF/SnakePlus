#ifndef SERPIENTE_H_INCLUDED
#define SERPIENTE_H_INCLUDED

#include <iostream>
#include "Bloque.h"



class Serpiente
{
private:

    Bloque cabeza;
    Bloque cola;
    //int tama;
    Bloque mapacuerpo[13][24]={}; // 13 y 24 el tamaño del mapa de nivel(deberia ser dinamico);

    bool crecer;

    //funcion para actualizar la posicion de la cola
    int setCola();

public:
    Serpiente(int x=5,int y=5,int dir=ARRIBA);
    bool getCrecer(){return crecer;}
    Bloque getCabeza();




    void setCrecer(bool c){crecer=c;}

    ///Seteamos la configuracion de inicio del la serpiente en el mapa
    void nacer(int x,int y);

    ///movemos la cabeza en la posicion  indicada
    int mover(int &nDir);

    ///dibujamos los elementos de la serpiente en una ventana
    void dibujar(sf::RenderWindow &window);

    ///compara si la serpiente esta colisionando en una posicion
    bool colisiona(int x,int y, bool ignorarCabeza=false);

};

#endif // SERPIENTE_H_INCLUDED
