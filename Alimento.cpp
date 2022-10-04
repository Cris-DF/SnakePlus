#include "Bloque.h"


class Alimento
{
private:
    //int valorN; //valor nutricional
    int x, y;//posicion
    sf::Sprite fruta;
    sf::Texture texture;
public:
    Alimento(){//constructor
        texture.loadFromFile("media/manzana.png");
        fruta.setTexture(texture);
        }
    sf::Sprite getFruta(){return fruta;}

    int getX(){return x;}
    int getY(){return y;}

    void generarComida(){
        x= rand() % 24;
        y= rand() % 13;
        fruta.setPosition( (40*x),(40* y) );

       }

};


