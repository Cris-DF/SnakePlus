#include <iostream>
#include <SFML/Graphics.hpp>
#include<fstream>


using namespace std;
//aca inclui solo el archivo de serpiente, porque en serpiente ya esta el #include de alimento y en alimento el de bloque
#include "string.h"
#include "Bloque.h"
#include "Serpiente.h"
#include "Alimento.cpp"
#include "records.h"

int verTeclas(int tecla=0);
int jugar(sf::RenderWindow &window, int matriz[13][24] , char *nombre, bool infinito=true, int puntaje=10,int nivel=1);
bool verificarRecordInfinito(char*nombre,int puntos,sf::RenderWindow &window);
void MostrarRecord( char*nombre, int puntos, sf::RenderWindow &window);


#include "niveles.h"
#include "menu.h"


int main()
{

    char nombre[20];

    cout<<"    Por favor antes de jugar ingrese su nombre"<<endl;

    cin.getline(nombre,19);



    //configurar la pantalla. Con 960*560 pixeles
    sf::RenderWindow window(sf::VideoMode(960,560 ), "SNAKE++");


    //constantes que representan la matriz que hace un nivel en el juego
    /*const int filas=13;
    const int columnas=24;*/

    sf::Sprite cursor;
    sf::Texture imgCursor;
    setCursor(cursor,imgCursor);


    sf::Text textoMenu;
    sf::Font font;
    setTextoMenu(textoMenu,font);





    int opcion=1, tecla=1;

    sf::Clock clock;

    Niveles niveles;


    //char nombre[20];  PedirNombre(nombre, window);


       while (window.isOpen())
    {

        //este es el evento para ver que la ventana este abierta
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }


        if(clock.getElapsedTime().asSeconds()>0.15f){
             clock.restart();



             tecla=menuPrincipal(window,cursor,opcion,textoMenu);

            if(tecla==5 ){
                switch(opcion){
                case 1:
                    jugar(window,niveles.nivel1,nombre); break;

                case 2:
                    setTextoMenuNiveles(textoMenu,font);
                    menuNiveles(window,cursor,opcion,textoMenu,nombre);
                    setTextoMenu(textoMenu,font);
                    break;
                case 3:  MostrarPosiciones(window);
                    break;
                case 4:  if(bkpRecordsPuntos()) cout<<"Backup Exitoso"<<endl;
                    break;
                default: break;
                }
                tecla=1;
            }

            }






    }


    return 0;
}



///Esto es para jugar un nivel entero
int jugar(sf::RenderWindow &window, int matriz[13][24] , char *nombre, bool infinito, int puntaje,int nivel )
{

//matriz del nivel
    const int filas=13;
    const int columnas=24;
    int tecla=1;
    int puntos=0;
    //bool choco=false;

    Serpiente serpiente;
    sf::Sprite ladrillo; //objeto para pintar las paredes representadas en la matriz del nivel
    sf::Texture imgLadrillo;
    Alimento alimento;


    int codBloque=1;


    sf::Clock clock;
    sf::Clock clockTotal;


    imgLadrillo.loadFromFile("media/bloque.png");
    ladrillo.setTexture(imgLadrillo);

    sf::Text text;
    sf::Font font;

    font.loadFromFile("media/fuente.ttf");
    text.setFont(font);
    text.setPosition(470,540);
    text.setCharacterSize(16);
    text.setString("Puntos: "+puntos);


    bool comible=false;

    do{
        alimento.generarComida();
        comible =  ( matriz[alimento.getY()][alimento.getX()]==1 || serpiente.colisiona(alimento.getX(),alimento.getY()) );
        }while(comible);

    //este es como un while(true), pero evita que el programa intente seguir ejecutandose luego de cerrar la ventana
    while (window.isOpen())
    {

        //este es el evento para ver que la ventana este abierta
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //cargamos el ingreso del teclado
        tecla=verTeclas(tecla);

        ///aca podriamos agregar animaciones para suavizar el movimiento de la cola y la cabeza usando alguna funcion de Serpiente

        //si paso un segundo vamos a actualizar el entorno
        if(clock.getElapsedTime().asSeconds() >=0.3f)
        {

            clock.restart(); //reiniciamos este reloj
            window.clear();//limpiamos la ventana

             if( ! infinito && puntos>=puntaje){
                return (int)clockTotal.getElapsedTime().asSeconds();
             }


            if(serpiente.colisiona(serpiente.getCabeza().getX(),serpiente.getCabeza().getY(),true)){
               if(infinito){
                verificarRecordInfinito(nombre,puntos,window);
                return puntos;
               }
                else
                return 0;
            }
            //dibujamos bloques en la posicion en donde haya un 1
            for(int x=0; x<columnas; x++)
            {
                for(int y=0; y<filas; y++)
                {
                    if(matriz[y][x]==codBloque)
                    {
                        ladrillo.setPosition(x*40,y*40);
                        window.draw(ladrillo);

                        if(serpiente.getCabeza().getX()==x && serpiente.getCabeza().getY()==y){

                            if(infinito){
                                 verificarRecordInfinito(nombre,puntos,window);
                                return puntos;

                            }
                                else
                                return 0;

                        }
                    }
                }
            }


            //la serpiente avanza en la direccion actual
            tecla=serpiente.mover(tecla);

            if(serpiente.getCabeza().getX()==alimento.getX() && serpiente.getCabeza().getY()==alimento.getY()){
                serpiente.setCrecer(true);

                do{
                alimento.generarComida();
                comible =  ( matriz[alimento.getY()][alimento.getX()]==1 || serpiente.colisiona(alimento.getX(),alimento.getY()) );
                }while(comible);

                puntos++;
                text.setString("Puntos: "+ to_string(puntos));
            }




            //dibujamos el texto y la serpiente

            window.draw(alimento.getFruta());
            serpiente.dibujar(window);
            window.draw(text);

            //mostramos lo dibujado en la pantalla
            window.display();
        }

    }
    verificarRecordInfinito(nombre,puntos,window);
    return puntos;

}


void MostrarRecord(sf::RenderWindow &window){

    int parpadeos=5;

    sf::Clock clock;
    sf::Clock totalClock;

    sf::Text text;
    sf::Font font;

    font.loadFromFile("media/fuente.ttf");
    text.setFont(font);
    text.setPosition(100,200);
    text.setCharacterSize(16);
    text.setString("FELICIDADES ES UN NUEVO RECORD");


    window.clear();

    while (window.isOpen() && parpadeos>0)
    {

        //este es el evento para ver que la ventana este abierta
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        if(clock.getElapsedTime().asSeconds() >=0.6f)
        {
            clock.restart(); //reiniciamos este reloj


            window.draw(text);
            window.display();
            parpadeos--;
        }


        }

}



bool verificarRecordInfinito(char *nombre,int puntos, sf::RenderWindow &window){

    bool record=false;
    int posicion=4;

    RecordsPuntos registro[3];
    RecordsPuntos auxiliar;

    for(int i=2;i>=0;i--){
            registro[i].leerDeDisco(i);
            if(puntos>registro[i].getPuntos())
                posicion=i;
    }

    if(posicion<3){
            record=true;
            MostrarRecord(window);

        int posAux=2;
        while(posAux>posicion){
            registro[posAux].setNombre(registro[posAux-1].getNombre());
            registro[posAux].setPuntos(registro[posAux-1].getPuntos());
            registro[posAux].modificarEnDisco(posAux);
            posAux--;
        }

            registro[posicion].setNombre(nombre);
            registro[posicion].setPuntos(puntos);
            registro[posicion].modificarEnDisco(posicion);

    }

    return record;
}


int verTeclas(int tecla)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) )
        tecla=1;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        tecla=2;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        tecla=3;
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        tecla=4;

    else if( sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        tecla=5;

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
             tecla=6;

    return tecla;
}









