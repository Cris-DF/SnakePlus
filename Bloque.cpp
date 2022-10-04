
#include "Bloque.h"

//Clase base para cargar las imagenes y mover los objetos
Bloque::Bloque(int x,int y)
    {
        visible=false;
        setTexture();      //textura por defecto
        posicionar(x,y);    //posicion iniciall
        sprite.setOrigin(pixeles/2,pixeles/2);

    }


    void Bloque::setVisible(bool visib){visible=visib;}
    bool Bloque::getVisible(){return visible;}

    sf::Sprite Bloque::getSprite()
    {
        return sprite;
    }

    sf::Texture Bloque::getTexture()
    {
        return texture;
    }
    int Bloque::getX()
    {
        return posX;
    }
    int Bloque::getY()
    {
        return posY;
    }

    int Bloque::getDireccion(){
        return direc;
    }

    ///cambia la imagen del objeto
    void Bloque::setTexture(const char *imagen)
    {
        texture.loadFromFile(imagen);
        sprite.setTexture(texture);
    }

    ///movimiento en X e Y (se agrega a la posicion actual)
    void Bloque::mover(float x,float y)
    {
        sprite.move(x*pixeles,y*pixeles); //movemos el tamaño en pixeles* la distancia
        posX+=x;
        posY+=y;

        //esto es para anclar el movimiento al tamaño X,Y de la pantalla (y para aparecer en el otro extremo)
        if(posY<0)          posicionar(posX,12,direc);
        else if(posY>12) posicionar(posX,0,direc);
        else if(posX<0) posicionar(23,posY,direc);
        else if(posX>23) posicionar(0,posY,direc);
    }

    ///mover al objeto a una posicion determinada
    void Bloque::mover(int direccion)
    {
        int dis=1;
        switch(direccion)
        {
        case ARRIBA:
            mover(0,-dis);
            break;    //arriba
        case DERECHA:
            mover(dis,0);
            break;      //derecha
        case ABAJO:
            mover(0,dis);
            break;      //abajo
        case IZQUIERDA:
            mover(-dis,0);
            break;     //izquierda
        }

        girar(direccion);
    }

    ///mover al objeto a una posicion determinada
    void Bloque::posicionar(float x,float y, int direccion)
    {
        sprite.setPosition(x*pixeles+20,y*pixeles+20);
        posX=x;
        posY=y;


        girar(direccion);

    }

    void Bloque::girar(int giro)
    {
        sprite.setRotation(90.0f*giro);
        direc=giro;
    }


