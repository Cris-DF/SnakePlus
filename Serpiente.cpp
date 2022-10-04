#include "Serpiente.h"
#include "Alimento.cpp"

///funcion que mueve la cola reemplazando el bloque que estaba en ese lugar


Serpiente::Serpiente(int x,int y,int dir)
    {
        cabeza.setTexture("media/cabeza.png"); //Sprites por defecto
        cola.setTexture("media/cola.png");

        crecer=false;

        //seteamos las partes del cuerpo en una posicion inical
         nacer(x,y);

    }





    Bloque Serpiente::getCabeza()
    {
        return cabeza;
    }


    int  Serpiente::setCola()
    {
        //La cola avanza en la direccion que esta mirando
        cola.mover(cola.getDireccion());

        //luego gira mirando hacia el proximo bloque
        cola.girar(mapacuerpo[cola.getY()][cola.getX()].getDireccion());

        //por ultimo se elimina el bloque del cuerpo que fue reemplazado
        mapacuerpo[cola.getY()][cola.getX()].setVisible(false);

        return 1;
    }



    void Serpiente::nacer(int x, int y){
        cabeza.posicionar(x,y,ARRIBA); //posicion de inicio de la cabeza

        mapacuerpo[y+1][x]=ARRIBA;  //posicion de inicio del cuerpo que une la cola con la cabeza

        cola.posicionar(x,y+2,ARRIBA); //posicion de inicio de la cola
    }


    ///movemos la cabeza en la posicion indicada
    int Serpiente::mover(int &nDir)
    {
        int direc=cabeza.getDireccion();
        int giro=false;

        //comprobamos la direccion porque no puede dar media vuelta en un solo movimiento
        if((nDir==ARRIBA && direc!=ABAJO)||(nDir==ABAJO && direc!=ARRIBA)
                || (nDir==DERECHA && direc!=IZQUIERDA)||(nDir==IZQUIERDA && direc!=DERECHA))
        {
            //si estamos realizando movimiento distinto al anterior es un giro
            if (nDir!=direc){
                    giro=true;
                    direc=nDir;
            }
        }




        //creamos un nuevo bloque para reemplazar la cabeza
        mapacuerpo[cabeza.getY()][cabeza.getX()].setVisible(true);
        mapacuerpo[cabeza.getY()][cabeza.getX()].posicionar(cabeza.getX(),cabeza.getY(),direc);

        //si giramos o comemos el bloque del cuerpo es un nodo, sino es el cuerpo Horizontal
         if (giro ||crecer) mapacuerpo[cabeza.getY()][cabeza.getX()].setTexture("media/cuerpo.png");
         else mapacuerpo[cabeza.getY()][cabeza.getX()].setTexture("media/cuerpoH.png");

        //mueve la cola a su proxima posicion
        if(crecer){
            crecer=false;
        }
        else setCola();

        //movemos la cabeza en la direccion actual
        cabeza.mover(direc);

        //cabeza.girar(direc); //apunta el sprite a la direccion
        return direc;
    }


    void Serpiente::dibujar(sf::RenderWindow &window)
    {

        window.draw(cabeza.getSprite());

        window.draw(cola.getSprite());

        //dibujamos el cuerpo en cada direccion activa
        for(int y=0;y<13;y++){
            for(int x=0;x<24;x++){
                if(mapacuerpo[y][x].getVisible()==true){
                        window.draw(mapacuerpo[y][x].getSprite());
                }
            }
        }

    }


    bool Serpiente::colisiona(int x,int y,bool ignorarCabeza){


    if(mapacuerpo[y][x].getVisible()==true)return true;
    if(cola.getX()==x && cola.getY()==y) return true;
    if(! ignorarCabeza && cabeza.getX()==x && cabeza.getY()==y)return true;

    return false;

    }




