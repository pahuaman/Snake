#include <iostream>
#include <sstream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//DEFINIMOS TECLAS
#define  ARRIBA    72
#define  IZQUIERDA 75
#define  DERECHA   77
#define  ABAJO     80
#define  ESC       27
#define  ENTER     13

using namespace std;

//VARIABLES GLOBALES
char Tecla;
int  Cuerpo [200][2];
int  n         = 1;
int  Tam       = 4;
int  x         = 10, y = 12;
int  Dir       = 3;
int  xc        = 30, yc = 15;
int  Velocidad = 100, h = 1;
int  Score     = 0;
int  Pos       = 1;

void gotoxy(int x, int y) //FUNCION QUE POSICIONA
{
    HANDLE hCon;
    COORD  dwPos;

    dwPos.X = x;
    dwPos.Y = y;

    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hCon,dwPos);

}

//MATRIZ PARA PODER DIBUJAR EL MENU
char inicio[50][100] =
    {
    "                                                                      ",
    "       A A           AAAA AA   A AAAA A A   AAAA                      ",
    "        A            A    A A  A A  A AAA   A                         ",
    "        A            A    A  A A AAAA A  A  AAA                       ",
    "      AAAAA          A    A   AA A  A A   A A                         ",
    "     A AAA A     AAAAA    A   AA A  A A   A AAAA                      ",
    "    AAAAAAAAA                                                         ",
    "    AAAAAAAAA                                                         ",
    "     AAAAAAA           AAAAAAAAAAA               AAAAAAAAAAAAAAAA     ",
    "     AAAAAAA          AAAAAAAAAAAAAA            AAAAAAAAAAAAAAAAAA    ",
    "      AAAAAAA        AAAAAAAAAAAAAAAA          AAAAAAAAAAAAAAAAAA     ",
    "       AAAAAAA      AAAAAA     AAAAAAA        AAAAAAA                 ",
    "        AAAAAAA    AAAAAA       AAAAAAA      AAAAAA                   ",
    "         AAAAAAAAAAAAAAA         AAAAAAAAAAAAAAAAA                    ",
    "          AAAAAAAAAAAAA           AAAAAAAAAAAAAAA                     ",
    "           AAAAAAAAAAA             AAAAAAAAAAAAA                      ",
    "                                                                      ",


    };

void Menu_Inicial()
{
        for(int i = 0 ; i< 17 ; i++)
        {
            for(int j = 0 ; j < 71 ; j++)
            {
                if(inicio[i][j] == 'A')
                {
                    gotoxy(j+5,i+5); printf("*");
                }//if
            }//for anidado
        }//for

        Tecla = getch();

        for(int i = 0 ; i< 17 ; i++)
        {
            for(int j = 0 ; j < 71 ; j++)
            {
                if(inicio[i][j] == 'A')
                {
                    gotoxy(j+5,i+5); printf(" ");
                }//if
            }//for anidado
        }//for
}//menu inicial

void Pintar()
{
    //LINEAS HORIZONTALES
    for(int i=2; i<78; i++)
    {
        gotoxy(i,3);  printf("%c",205);
        gotoxy(i,23); printf("%c",205);
    }//for

    //LINEAS VERTICALES
    for(int i=4; i<23; i++)
    {
        gotoxy(2,i);  printf("%c",186);
        gotoxy(77,i); printf("%c",186);
    }//for

    //ESQUINAS
    gotoxy(2,3); printf("%c",201);
    gotoxy(2,23); printf("%c",200);
    gotoxy(77,3); printf("%c",187);
    gotoxy(77,23); printf("%c",188);

}//pintar

void Guardar_Posicion()
{
    Cuerpo[n][0] = x;
    Cuerpo[n][1] = y;
    n++;

    if(n == Tam){ n = 1; }

}//guardar posicion

void Pintar_Cuerpo()
{
    for(int i=1; i<Tam; i++)
    {
        gotoxy(Cuerpo[i][0], Cuerpo[i][1]); printf("*");

    }//for
}//Pintar cuerpo

void Borrar_Cuerpo()
{
    for(int i=1; i<Tam; i++)
    {
        gotoxy(Cuerpo[i][0], Cuerpo[i][1]); printf(" ");

    }//for
}//Borrar cuerpo

void Teclear()
{
    //ATRAPAMOS LA TECLA
        if(kbhit())
        {
            Tecla = getch();
            switch(Tecla)
            {
            case ARRIBA:
                if(Dir != 2)
                    Dir = 1;
            break;

            case ABAJO:
                if(Dir != 1)
                    Dir = 2;
            break;

            case DERECHA:
                if(Dir != 4)
                    Dir = 3;
            break;

            case IZQUIERDA:
                if(Dir != 3)
                    Dir = 4;
            break;
            }//switch
        }//if

}//Teclear

void Cambiar_Velocidad()
{
   if(Score == h*20)
   {
       Velocidad -= 10;
       h++;
   }//if
}//cambiar velocidad

void Comida()
{
    if(x == xc && y == yc)
    {
        xc = (rand()%73)+4;
        yc = (rand()%19)+4;

        Tam++;
        Score += 10;
        gotoxy(xc, yc); printf("%c",3);

        Cambiar_Velocidad();
    }//if
}//comida

bool Game_Over()
{
    if(y == 3 || y == 23 || x == 2 || x == 77) return false;
        for(int j = Tam - 1; j > 0; j--)
        {
            if(Cuerpo[j][0] == x && Cuerpo[j][1] == y)
                return false;
        }//for
        return true;
}//Game Over

void Puntos()
{
    gotoxy(3,1); printf("Score %d",Score);
}//puntos

int Menu_Final(void)
{

        if(kbhit())
        {
            Tecla = getch();
            if(Tecla == ARRIBA)
            {
                gotoxy(30,12); printf("%c   JUGAR DE NUEVO",16);
                gotoxy(30,15); printf("     SALIR DEL JUEGO");
                Pos = 1;
            }//if anidado

            if(Tecla == ABAJO)
            {
                gotoxy(30,12); printf("     JUGAR DE NUEVO");
                gotoxy(30,15); printf("%c   SALIR DEL JUEGO",16);
                Pos = 0;
            }//if

            if(Tecla == ENTER)
               return 1;
        }//if
        return 0;
}//menu final

void Interacion_Menu_Final()
{
        Borrar_Cuerpo();
        gotoxy(xc,yc); printf(" ");

        gotoxy(35,1); printf("      PRESS ENTER");
        gotoxy(30,12); printf("%c   JUGAR DE NUEVO",16);
        gotoxy(30,15); printf("     SALIR DEL JUEGO");
        do{

          Menu_Final();
        }while (!Menu_Final());
        gotoxy(35,1); printf("            ");
        gotoxy(30,12); printf("                    ");
        gotoxy(30,15); printf("                    ");

}//interaccion menu final

void Iniciar_Datos()
{
         for(int j = Tam ; j > 0  ; j--) // Borramos el cuerpo de la partida anterior
         {
             gotoxy(Cuerpo[j][0],Cuerpo[j][1]); printf(" ");
         }//for

         for(int j = 0 ; j <= Tam  ; j++) // reseteamos las espacios de la matriz cuerpo
         {
             for(int i = 0 ; i < 2 ; i++)
             {
                   Cuerpo[j][i] = '\0';
             }//for anidado

         }//for

         Score = 0;
         x = 10 ; y = 12 ; Tam = 4; Dir = 3; Velocidad = 100; h=1; n = 0;
         Comida(); Puntos();


}//iniciar datos

int main()
{
    system("color A");
    srand(time(NULL));
    Pintar();
    Menu_Inicial();
    do{
       Pintar();
       //Iniciar_Datos();
       gotoxy(xc,yc); printf("%c",3);
       do{
           Puntos();
           Comida();
           Cambiar_Velocidad();

           Borrar_Cuerpo();
           Guardar_Posicion();
           Pintar_Cuerpo();
           //dibujar_cuerpo();

           Sleep(Velocidad);
           Teclear();
           Teclear();
           Teclear();

           if(Dir == 3) x++;
           if(Dir == 1) y--;
           if(Dir == 4) x--;
           if(Dir == 2) y++;

           if(Tecla != ESC && !Game_Over())
           {
               Interacion_Menu_Final();
               Iniciar_Datos();
               gotoxy(xc, yc); printf("%c",3);
           }//if

    }while(Pos);// FIN DEL WHILE
    //Interacion_Menu_Final();
    system("pause>null");
    return 0;
    }while(Tecla != ESC && Game_Over());
    return 0;

}//main
