#ifndef BLOQUE_H_INCLUDED
#define BLOQUE_H_INCLUDED

#include <SFML/Graphics.hpp>

enum direcciones {ARRIBA=1,DERECHA,ABAJO,IZQUIERDA};

class Bloque
{
protected:
    sf::Sprite sprite;//para cargar y posicionar la imagen

    bool visible;
    int posX,posY,direc; //posiciones (no en pixeles de pantalla sino en el nivel)

    sf::Texture texture;//aca se carga el archivo de la imagen, tiene que ser una propiedad porque si lo creamos dentro de una funcion el sprite pierde la referencia

    static const int pixeles=40;//pixeles de las imagenes

public:
    Bloque(int x=0,int y=0);

    void setVisible(bool visib);
    bool getVisible();
    sf::Sprite getSprite();
    sf::Texture getTexture();
    int getX();
    int getY();
    int getDireccion();

    ///cambia la imagen del objeto
    void setTexture(const char *imagen="media/bloque.png");

    ///movimiento en X e Y (se agrega a la posicion actual)
    void mover(float x,float y);

    ///mueve apuntando a una direccion
    void mover(int direccion);

    ///mover al objeto a una posicion determinada
    void posicionar(float x,float y,int direccion=ARRIBA);

    ///girar el sprite
    void girar(int giro);
};

#endif // BLOQUE_H_INCLUDED
