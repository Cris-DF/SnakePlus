#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

int menuPrincipal(sf::RenderWindow &window,sf::Sprite &cursor,int &opcion,sf::Text text){

        window.clear();



        int tecla=verTeclas();


        if(tecla==1 && opcion>1){
            opcion--;
            cursor.move(0,-50);
        }
        else if(tecla==3 && opcion<4){
            opcion++;
            cursor.move(0,50);
        }


        window.draw(text);
        window.draw(cursor);
        window.display();

        return tecla;
}


void menuNiveles(sf::RenderWindow &window,sf::Sprite &cursor,int &opcion,sf::Text text,  char *nombre){
int puntosGanar[4]={4,4,4,4};
Niveles niveles;
sf::Clock clock;
int tecla=1;
    while (window.isOpen() && tecla!=6)
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



        window.clear();

        tecla=verTeclas();

        if(tecla==1 && opcion>1){
            opcion--;
            cursor.move(0,-50);
        }
        else if(tecla==3 && opcion<5){
            opcion++;
            cursor.move(0,50);
        }


        window.draw(text);
        window.draw(cursor);
        window.display();


        if(tecla==5){

            switch(opcion){
            case 1:  if( !jugar(window,niveles.nivel1,nombre,false,puntosGanar[opcion-1]) ){
                            break;
                        }
            case 2:if( !jugar(window,niveles.nivel2,nombre,false,puntosGanar[opcion-1]) ){
                            break;
                        }
            case 3:if( !jugar(window,niveles.nivel3,nombre,false,puntosGanar[opcion-1]) ){
                            break;
                        }
            case 4: jugar(window,niveles.nivel4,nombre,false,puntosGanar[opcion-1]) ;  break;
            case 5: tecla=6;
            default:
                break;
            }

        }

        }
    }
}


void MostrarPosiciones(sf::RenderWindow &window){


    char texto1[100],texto2[100],texto3[100];

    strcpy(texto1, "1er Puesto  ");
    strcpy(texto2, "2do Puesto  ");
    strcpy(texto3, "3er Puesto  ");

    RecordsPuntos registro[3];
    for(int i=0;i<3;i++){
            registro[i].leerDeDisco(i);
    }

    strcat(texto1,registro[0].getNombre());
    strcat(texto2,registro[1].getNombre());
    strcat(texto3,registro[2].getNombre());

    strcat(texto1,"  \n\n\t\t\tPuntos: ");
    strcat(texto2,"  \n\n\t\t\tPuntos: ");
    strcat(texto3,"  \n\n\t\t\tPuntos: ");


    sf::Clock clock;

    sf::Text text;
    sf::Font font;

    font.loadFromFile("media/fuente.ttf");
    text.setFont(font);
    text.setPosition(100,200);
    text.setCharacterSize(16);



    while (window.isOpen())
    {

        //este es el evento para ver que la ventana este abierta
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }


        if(verTeclas()==6){
            break;
        }

        if(clock.getElapsedTime().asSeconds() >=0.6f)
        {
            clock.restart(); //reiniciamos este reloj

            window.clear();

            text.setPosition(100,100);
            text.setString(texto1 + to_string(registro[0].getPuntos()));
            window.draw(text);

            text.setPosition(100,200);
            text.setString(texto2+ to_string(registro[1].getPuntos()));
            window.draw(text);

            text.setPosition(100,300);
            text.setString(texto3+ to_string(registro[2].getPuntos()));
            window.draw(text);

            text.setPosition(100,500);
            text.setString("\t\t\t\t\t\tPresione Esc para continuar");
            window.draw(text);


            window.display();
        }


        }
}



void setCursor(sf::Sprite &cursor,sf::Texture &imgCursor){

    imgCursor.loadFromFile("media/manzana.png");
    cursor.setTexture(imgCursor);
    cursor.setPosition(200,120);

}


void setTextoMenu(sf::Text &text,sf::Font  &font){


    font.loadFromFile("media/fuente.ttf");
    text.setFont(font);

    text.setPosition(240,130);
    text.setCharacterSize(17);
    text.setString("Iniciar Juego \n\n\nNiveles\n\n\nPosiciones\n\n\nCrear Backup de Records");


}

void setTextoMenuNiveles(sf::Text &text,sf::Font  &font){


    font.loadFromFile("media/fuente.ttf");
    text.setFont(font);

    text.setPosition(240,130);
    text.setCharacterSize(17);
    text.setString("Nivel 1 \n\n\nNivel 2\n\n\nNivel 3\n\n\nNivel 4\n\n\n Salir al menu" );


}

#endif // MENU_H_INCLUDED
