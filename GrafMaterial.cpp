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

void MainMenu() ///aici genereaza de fiecare data cand este apelata functia o pagina de tip main menu
{
    cleardevice();
    setcolor(WHITE);
    readimagefile("fundal.jpg",0,0,getmaxx(),getmaxy());
    int mx,my;
    mx=getmaxx();
    my=getmaxy();

    int midx=mx/2;
    int midy=my/2;

    xbutGN=midx;
    ybutGN=midy;
    xbutGO=midx;
    ybutGO=midy;
    setfillstyle(SOLID_FILL,COLOR(17,19,58));
    setcolor(WHITE);
    bar(xbutGN-500,ybutGN+100,xbutGN-150,ybutGN+200);
    rectangle(xbutGN-500,ybutGN+100,xbutGN-150,ybutGN+200);
    setcolor(WHITE);
    setbkcolor(COLOR(17,19,58));
    setfillstyle(SOLID_FILL,COLOR(17,19,58));
    char titlu[50]="Graf Neorientat";
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
    outtextxy(xbutGN-470,ybutGN+130,titlu);

    bar(xbutGO+150,ybutGO+100,xbutGO+500,ybutGO+200);
    rectangle(xbutGO+150,ybutGO+100,xbutGO+500,ybutGO+200);
    setcolor(WHITE);
    setbkcolor(COLOR(17,19,58));
    setfillstyle(SOLID_FILL,COLOR(17,19,58));
    strcpy(titlu,"Graf Orientat");
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
    outtextxy(xbutGN+210,ybutGN+130,titlu);
    setcolor(WHITE);


    bool gata=0;
    do
    {
        MainButtons();///fiecare buton posibil
    }
    while(!gata);

}



void Conexitate()
{
    cleardevice();
    readimagefile("conexitate.jpg",0,0,getmaxx(),getmaxy());

    bool gata=0;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            Materie();
        }
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            gradeO();
        }
    }
    while(!gata);

}

void Gcomp()
{
    cleardevice();
    readimagefile("grafcomplet.jpg",0,0,getmaxx(),getmaxy());

    bool gata=0;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            Conexitate();
        }
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);

            listaadiac();
        }
    }
    while(!gata);

}

void listaadiac()
{
    cleardevice();
    readimagefile("listaadiac.jpg",0,0,getmaxx(),getmaxy());
    bar(0,0,getmaxx(),100);
    bool gata=0;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            Gcomp();
        }
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            exMA();
        }
    }
    while(!gata);

}

void exMA()
{
    cleardevice();
    readimagefile("ex.matadiac.jpg",0,0,getmaxx(),getmaxy());

    bool gata=0;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            listaadiac();
        }
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            MA();
        }
    }
    while(!gata);

}

void MA()
{
    cleardevice();
    readimagefile("matadiac.jpg",0,0,getmaxx(),getmaxy());

    bool gata=0;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            exMA();
        }
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            Grad();
        }
    }
    while(!gata);

}

void Grad()
{
    cleardevice();
    readimagefile("Grad.jpg",0,0,getmaxx(),getmaxy());

    bool gata=0;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            MA();
        }
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            exempluN();
        }
    }
    while(!gata);

}

void exempluN()
{
    cleardevice();
    readimagefile("ExempluNeorientate.jpg",0,0,getmaxx(),getmaxy());

    bool gata=0;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            Grad();
        }
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            Neorientat();
        }
    }
    while(!gata);

}

void Neorientat()
{
    cleardevice();
    readimagefile("Neorientate.jpg",0,0,getmaxx(),getmaxy());

    bool gata=0;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            exempluN();
        }
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            Materie();
        }
    }
    while(!gata);

}

void gradeO()
{
    cleardevice();
    readimagefile("gradeO.jpg",0,0,getmaxx(),getmaxy());

    bool gata=0;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            Conexitate();
        }
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            Orientat();
        }
    }
    while(!gata);

}


void Orientat()
{
    cleardevice();
    readimagefile("Orientate.jpg",0,0,getmaxx(),getmaxy());

    bool gata=0;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            gradeO();
        }
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            Materie();
        }
    }
    while(!gata);

}

void DFS()
{
    cleardevice();
    readimagefile("DFS.jpg",0,0,getmaxx(),getmaxy());

    bool gata=0;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            Materie();
        }
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            Materie();
        }
    }
    while(!gata);

}

void BFS()
{
    cleardevice();
    readimagefile("BFS.jpg",0,0,getmaxx(),getmaxy());

    bool gata=0;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            Materie();
        }
        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            Materie();
        }
    }
    while(!gata);

}

void Materie()
{
    cleardevice();
    readimagefile("grafuri.jpg",0,0,getmaxx(),getmaxy());

    rectangle(0,0,130,40);/// MENU but
    setcolor(WHITE);
    char titlu[50]="MENU";
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
    outtextxy(10,10,titlu);

    bool gata=0;
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            int x=mousex(),y=mousey();
            if(x>=0 && x<=130 && y>=0 && y<=40)
                MainMenu();
            if(x>=398 && x<=694 && y>=281 && y<=426)
                Neorientat();
            if(x>=805 && x<=1102 && y>=279 && y<=429)
                Orientat();
            if(x>=700 && x<=797 && y>=457 && y<=504)
                DFS();
            if(x>=699 && x<=796 && y>=514 && y<=560)
                BFS();
            if(x>=676 && x<=821 && y>=569 && y<=640)
                Conexitate();
        }

        if(ismouseclick(WM_RBUTTONDOWN))
        {
            clearmouseclick(WM_RBUTTONDOWN);
            MainMenu();
        }
    }
    while(!gata);
}
