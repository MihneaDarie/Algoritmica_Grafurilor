#include <iostream>
#include <cmath>
#include <fstream>
#include <winbgim.h>
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <cstdlib>
#include <ctime>
#include <time.h>

#include "functions.h"

#define INFINIT 999999999

void meniuGrafN() /// aceasta functie genereaza de fiecare data o pagina in care se prelugreaza grafuri neorientate
{
    setbkcolor(COLOR(17,19,58));
    setfillstyle(SOLID_FILL,COLOR(17,19,58));
    ry=100;
    consolex=17;
    consoley=95;
    linesnr=0;
    slider=9;
    speed=slider*50+50;
    cleardevice();
    setbkcolor(COLOR(17,19,58));
    resetmatrix(MatriceAdiac,ct);
    ct=0;

    rectangle(0,0,130,40);/// MENU but
    setcolor(WHITE);
    char titlu[50]="MENU";
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(10,10,titlu);

    rectangle(0,40,130,80); /// refresh but
    setcolor(WHITE);
    strcpy(titlu,"RESET");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(10,50,titlu);

    rectangle(130, 0, 1499, 80);/// topbar

    setfillstyle(SOLID_FILL,WHITE); ///loc pentru mai multe butoane(save,)
    bar(140,10,255,70);
    bar(270,10,520,70);
    readimagefile("2715724.jpg",145,15,195,65);
    readimagefile("1234.jpg",205,25,245,55);
    setfillstyle(SOLID_FILL,WHITE);
    bar(270,10,520,40);
    setcolor(BLACK);
    rectangle(270,10,520,40);
    setbkcolor(WHITE);
    strcpy(titlu,"Comenzi consola");
    outtextxy(305,15,titlu);
    line(270,40,520,40);
    setfillstyle(SOLID_FILL,YELLOW);
    bar(270,40,520,70);
    setcolor(BLACK);
    rectangle(270,10,520,40);
    setbkcolor(YELLOW);
    rectangle(270,40,520,70);
    strcpy(titlu,"Comenzi ecran");
    outtextxy(320,45,titlu);

    setbkcolor(COLOR(17,19,58));
    setcolor(WHITE);

    rectangle(200, 650, 1499, 749);///bottom bar


    setfillstyle(SOLID_FILL,DARKGRAY);
    rectangle(0, 80, 200, 749);/// consola
    floodfill(5,85,WHITE);


    strcpy(titlu,"OPERATII MUCHII");///titlu muchii
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(300,665,titlu);


    rectangle(220,710,385,735);///adugare muchie
    setcolor(WHITE);
    strcpy(titlu,"adauga muchie");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(225,712,titlu);

    rectangle(447, 710, 612, 735);///stergere muchie
    setcolor(WHITE);
    strcpy(titlu,"sterge muchie");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(458,712,titlu);


    line(633,650,633,749); /// linie stanga jos
    setcolor(WHITE);
    strcpy(titlu,"OPERATII NODURI");///titlu muchii
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(735,665,titlu);

    rectangle(653,710,818,735);///adugare nod
    setcolor(WHITE);
    strcpy(titlu,"adauga nod");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(675,712,titlu);

    rectangle(880, 710, 1045, 735);///stergere nod
    setcolor(WHITE);
    strcpy(titlu,"sterge nod");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(909,712,titlu);

    line(1066,650,1066,749);  /// linie dreapta jos
    setcolor(WHITE);
    strcpy(titlu,"OPERATII COSTURI");///titlu costuri
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1170,665,titlu);

    rectangle(1086,710,1251,735);///adugare cost
    setcolor(WHITE);
    strcpy(titlu,"adauga cost");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1110,712,titlu);

    rectangle(1313, 710, 1478, 735);///stergere cost
    setcolor(WHITE);
    strcpy(titlu,"sterge cost");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1340,712,titlu);

    rectangle(1200, 80, 1499, 650);///lista comenzilor
    ///line(1200, 150, 1499, 150);///line titlu
    setcolor(WHITE);
    ///rectangle(200, 80, 1200, 650);
    line(1200,0,1200,80);
    strcpy(titlu,"COMENZI");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1295,35,titlu);
    setcolor(YELLOW);
    strcpy(titlu,"Grafuri Neorientate");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
    outtextxy(695,25,titlu);
    setcolor(WHITE);
    ///line(1349, 150, 1349, 650);///linie imaginara mijloc

    rectangle(1250, 90, 1450, 130);
    setcolor(WHITE);
    strcpy(titlu,"M.ADIACENTA");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1260,100,titlu);

    rectangle(1230, 140, 1470, 180);
    setcolor(WHITE);
    strcpy(titlu,"NR.MAX.MUCHII");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1250,150,titlu);

    rectangle(1310, 190, 1385, 230);
    setcolor(WHITE);
    strcpy(titlu,"DFS");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1325,200,titlu);

    rectangle(1310, 250, 1385, 290);
    setcolor(WHITE);
    strcpy(titlu,"BFS");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1325,260,titlu);

    rectangle(1250, 310, 1450, 350);
    setcolor(WHITE);
    strcpy(titlu,"CONEXITATE");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1270,320,titlu);

    rectangle(1250, 370, 1450, 410);
    setcolor(WHITE);
    strcpy(titlu,"COMPONENTE");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1265,380,titlu);

    rectangle(1295, 430, 1405, 470);
    setcolor(WHITE);
    strcpy(titlu,"EULER");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1310,440,titlu);

    rectangle(1310, 490, 1390, 530);
    setcolor(WHITE);
    strcpy(titlu,"PRIM");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1319,500,titlu);

    rectangle(1280, 550, 1425, 590);
    setcolor(WHITE);
    strcpy(titlu,"KRUSKAL");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1295,560,titlu);

    setcolor(WHITE);///slider
    rectangle(1240, 610, 1465, 630);
    line(1250,620,1455,620);

    /*rectangle(1270, 610, 1435, 645);
    setcolor(WHITE);
    strcpy(titlu,"HAMILTON");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1285,620,titlu);

    rectangle(1280, 430, 1425, 470);
    strcpy(titlu,"DIJKSTRA");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1295,440,titlu);*/

    /*strcpy(titlu,"COMENZI");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(1295,110,titlu);*/

    setfillstyle(SOLID_FILL,WHITE);
    rectangle(200, 80, 1200, 650); /// play board
    floodfill(205, 85, WHITE);

    ClearSlider(slider);

    fscroll= fopen("scrlo","w");
    fclose(fscroll);

    bool gata=0;
    do
    {
        GNButtons();
    }
    while(!gata);
}
