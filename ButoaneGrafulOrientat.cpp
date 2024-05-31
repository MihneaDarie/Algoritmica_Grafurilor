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

void GOButtons() /// aceasta functie inregistreaza toate apasaturile de mouse si toate butoanele posibile de pe o pagina cu GO
{
    ///am nevoie de ajutor
    setactivepage(0);
    int x,y,j;

    int x1,y1,mem1;
    int x2,y2,p;

    fscroll= fopen("scrlo","r");

    if(kbhit()!=0)
    {
        int var=getch();
        if(var==0 || var==224 )
        {
            var=getch();
            if(var==72)///up
            {
                if(scroll>1) scroll--;
                consx=consolex=17;
                consy=95;
                if(consoley>105) consoley-=25;
                ClearConsole(scroll);

            }
            if(var==80)///down
            {
                scroll++;
                consx=consolex=17;
                consoley+=25;
                consy=95;
                ClearConsole(scroll);
            }
            if(var==75)
            {   if(slider>=1)
                {   slider--;
                    ClearSlider(slider);
                    speed=slider*50+50;
                }
            }
            if(var==77)
            {   if(slider<=18)
                {   slider++;
                    ClearSlider(slider);
                    speed=slider*50+50;
                }
            }
        }

    }
    fclose(fscroll);

    if(ismouseclick(WM_RBUTTONDOWN))
    {
        ClearPlayBO(0);
        clearmouseclick(WM_RBUTTONDOWN);
        x=mousex();
        y=mousey();

        mem1=-5;
        for(j=1; j<=ct; j++)
            if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R)
            {
                mem1=j;
                x1=a[j].x;
                y1=a[j].y;

                for(int leroy=1; leroy<=nrmuchii; leroy++)
                    for(int i=1; i<=nrmuchii; i++)
                    {

                        if(mmij[i][1]==a[j].val)
                            for(int yny=1; yny<=ct; yny++)
                                if(yny!=a[j].val && MatriceAdiac[yny][a[j].val]!=0)
                                {
                                    mmij[i][3]=(x1+a[yny].x)/2;
                                    mmij[i][4]=(y1+a[yny].y)/2;
                                    mmij[i][5]=((x1+a[yny].x)/2+x1)/2;
                                    mmij[i][6]=((y1+a[yny].y)/2+y1)/2;
                                    mmij[i][7]=((x1+a[yny].x)/2+a[yny].x)/2;
                                    mmij[i][8]=((y1+a[yny].y)/2+a[yny].y)/2;
                                }

                    }
                break;
            }
        if(mem1!=-5)
        {
            setactivepage(1);
            putimage(0,0,poza,0);
            setvisualpage(0);
            POINT poz;
            while(1)
            {
                setactivepage(page);
                setvisualpage(1-page);
                ClearPlayBO(mem1);

                GetCursorPos(&poz);
                ///rectangle(200, 80, 1200, 650);
                if(poz.x>=230 && poz.x<=1170 && poz.y>=110 && poz.y<=620)
                {
                    setcolor(DARKGRAY);
                    circle(poz.x,poz.y,R);
                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                    floodfill(poz.x,poz.y,DARKGRAY);


                    setcolor(WHITE);
                    setbkcolor(COLOR(17,19,58));
                    char nr[5];
                    sprintf(nr,"%d",mem1);
                    outtextxy(poz.x-7, poz.y-10,nr);

                    setcolor(BLACK);
                    int i=mem1;
                    a[i].x=poz.x;
                    a[i].y=poz.y;
                    for(j=i; j<=ct; j++)

                                        {
                                            if(MatriceAdiac[i][j]!=0 && i!=p && j!=p && MatriceAdiac[j][i]==0)
                                            {
                                                int calx1,caly1,calx2,caly2,mijx,mijy,drpy,drpx, mijlx, mijly;
                                                double dist;
                                                setcolor(BLACK);
                                                if(maximul(a[i].x-a[j].x,a[j].x-a[i].x)>maximul(a[i].y-a[j].y,a[j].y-a[i].y))
                                                {
                                                    calx2=(((a[i].x+a[j].x)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2;
                                                    caly2=(((a[i].y+R-3+a[j].y+R-3)/2+((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))/2)/2+((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))/2)/2;
                                                    calx1=((((a[i].x+a[j].x)/2+a[j].x)/2+a[j].x)/2+a[j].x)/2;
                                                    caly1=((((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))/2+a[j].y+R-3)/2+a[j].y+R-3)/2;
                                                    line(a[i].x,a[i].y+R-3,a[j].x,a[j].y+R-3);
                                                    ///setcolor(DARKGRAY);
                                                    ///line(calx2, caly2, calx1, caly1);
                                                    ///calx2=(calx2+calx1)/2;
                                                    ///caly2=(caly2+caly1)/2;
                                                    ///line(calx1, caly1, calx1, caly2);
                                                    ///line(calx1, caly1, calx2, caly1);
                                                    mijx=(calx1+calx2)/2;
                                                    mijy=(caly1+caly2)/2;
                                                    dist=sqrt((calx1-mijx)*(calx1-mijx)+(caly1-mijy)*(caly1-mijy));
                                                    dist/=2;
                                                    drpy=((((a[i].y+15*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, drpx, ((((a[i].y-10*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);
                                                    ///line(drpx, drpy, drpx, ((((a[i].y-10*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);

                                                    mijlx=(calx1+drpx+drpx)/3;
                                                    mijly=(caly1+drpy+((((a[i].y-10*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2)/3;

                                                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    ///floodfill(mijlx, mijly+3, DARKGRAY);
                                                    ///floodfill(mijlx, mijly-3, DARKGRAY);

                                                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    ///floodfill(drpx+1, drpy-25, BLACK);

                                                    ///line(mijx, mijy, calx1+dist, mijy);
                                                    ///line(mijx, mijy, calx2-dist, mijy);
                                                    ///line(calx1, caly1, mijx, mijy+dist);
                                                    ///line(calx1, caly1, mijx, mijy-dist);
                                                }
                                                else
                                                {
                                                    line(a[i].x+R-3,a[i].y,a[j].x+R-3,a[j].y);
                                                    caly2=(((a[i].y+a[j].y)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2;
                                                    calx2=(((a[i].x+R-3+a[j].x+R-3)/2+((a[i].x+R-3+a[j].x+R-3)/2+ a[j].x+R-3)/2)/2+((a[i].x+R-3+a[j].x+R-3)/2+ a[j].x+R-3)/2)/2;
                                                    calx1=((((a[i].x+R-3+a[j].x+R-3)/2+(a[j].x+R-3))/2+a[j].x+R-3)/2+a[j].x+R-3)/2;
                                                    caly1=((((a[i].y+a[j].y)/2+a[j].y)/2+a[j].y)/2+a[j].y)/2;
                                                    ///line(calx2, caly2, calx1, caly1);

                                                    drpy=((((a[i].y+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x+15*R-3+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, ((((a[i].x-10*R-3+calx1)/2+calx1)/2+calx1)/2+calx1)/2, drpy);
                                                }

                                                if(suntcosturi==1)
                                                {

                                                    setbkcolor(DARKGRAY);
                                                    setbkcolor(COLOR(17,19,58));

                                                    setfillstyle(SOLID_FILL,DARKGRAY);
                                                    setcolor(WHITE);

                                                    char nr[5];
                                                    sprintf(nr, "%d", MatriceAdiac[i][j]);

                                                    if(MatriceAdiac[i][j]>0)
                                                        outtextxy((a[i].x+a[j].x)/2, (a[i].y+a[j].y)/2, nr);

                                                    setcolor(BLACK);
                                                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    setcolor(WHITE);
                                                }
                                            }
                                            else if(MatriceAdiac[i][j]!=0 && i!=p && j!=p && MatriceAdiac[j][i]!=0)
                                            {
                                                int calx1,caly1,calx2,caly2,mijx,mijy,drpy,drpx,mijlx, mijly;
                                                double dist;
                                                setcolor(BLACK);
                                                if(maximul(a[i].x-a[j].x,a[j].x-a[i].x)>maximul(a[i].y-a[j].y,a[j].y-a[i].y))
                                                {
                                                    calx2=(((a[i].x+a[j].x)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2;
                                                    caly2=(((a[i].y+R-3+a[j].y+R-3)/2+((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))/2)/2+((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))/2)/2;
                                                    calx1=((((a[i].x+a[j].x)/2+ a[j].x)/2+a[j].x)/2+a[j].x)/2;
                                                    caly1=((((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))/2+a[j].y+R-3)/2+a[j].y+R-3)/2;
                                                    line(a[i].x,a[i].y+R-3,a[j].x,a[j].y+R-3);
                                                    line(a[i].x,a[i].y-R+3,a[j].x,a[j].y-R+3);
                                                    ///setcolor(DARKGRAY);
                                                    ///line(calx2, caly2, calx1, caly1);
                                                    ///calx2=(calx2+calx1)/2;
                                                    ///caly2=(caly2+caly1)/2;
                                                    ///line(calx1, caly1, calx1, caly2);
                                                    ///line(calx1, caly1, calx2, caly1);
                                                    mijx=(calx1+calx2)/2;
                                                    mijy=(caly1+caly2)/2;
                                                    dist=sqrt((calx1-mijx)*(calx1-mijx)+(caly1-mijy)*(caly1-mijy));
                                                    dist/=2;
                                                    drpy=((((a[i].y+15*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, drpx, ((((a[i].y-10*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);
                                                    ///line(drpx, drpy, drpx, ((((a[i].y-10*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);

                                                    mijlx=(calx1+drpx+drpx)/3;
                                                    mijly=(caly1+drpy+((((a[i].y-10*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2)/3;

                                                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    ///floodfill(mijlx, mijly+3, DARKGRAY);
                                                    ///floodfill(mijlx, mijly-3, DARKGRAY);

                                                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    ///floodfill(drpx+1, drpy-25, BLACK);

                                                    ///line(mijx, mijy, calx1+dist, mijy);
                                                    ///line(mijx, mijy, calx2-dist, mijy);
                                                    ///line(calx1, caly1, mijx, mijy+dist);
                                                    ///line(calx1, caly1, mijx, mijy-dist);
                                                    swape(i,j);
                                                    setcolor(BLACK);
                                                    calx2=(((a[i].x+a[j].x)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2;
                                                    caly2=(((a[i].y-R+3+a[j].y-R+3)/2+((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))/2)/2+((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))/2)/2;
                                                    calx1=((((a[i].x+a[j].x)/2+ a[j].x)/2+a[j].x)/2+a[j].x)/2;
                                                    caly1=((((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))/2+a[j].y-R+3)/2+a[j].y-R+3)/2;
                                                    mijy=(caly1+caly2)/2;
                                                    dist=sqrt((calx1-mijx)*(calx1-mijx)+(caly1-mijy)*(caly1-mijy));
                                                    dist/=2;
                                                    drpy=((((a[i].y-15*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    ///setcolor(DARKGRAY);
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, drpx, ((((a[i].y+10*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);
                                                    ///line(drpx, drpy, drpx, ((((a[i].y+10*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);

                                                    mijlx=(calx1+drpx+drpx)/3;
                                                    mijly=(caly1+drpy+((((a[i].y+10*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2)/3;

                                                    ///setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    ///floodfill(mijlx, mijly+4, DARKGRAY);
                                                    ///floodfill(mijlx, mijly-3, DARKGRAY);


                                                    swape(i,j);
                                                    ClearPlayBO(0);
                                                }
                                                else
                                                {
                                                    line(a[i].x+R-3,a[i].y,a[j].x+R-3,a[j].y);
                                                    line(a[i].x-R+3,a[i].y,a[j].x-R+3,a[j].y);
                                                    caly2=(((a[i].y+a[j].y)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2;
                                                    calx2=(((a[i].x+R-3+a[j].x+R-3)/2+((a[i].x+R-3+a[j].x+R-3)/2+ a[j].x+R-3)/2)/2+((a[i].x+R-3+a[j].x+R-3)/2+ a[j].x+R-3)/2)/2;
                                                    calx1=((((a[i].x+R-3+a[j].x+R-3)/2+(a[j].x+R-3))/2+a[j].x+R-3)/2+a[j].x+R-3)/2;
                                                    caly1=((((a[i].y+a[j].y)/2+a[j].y)/2+a[j].y)/2+a[j].y)/2;
                                                    ///line(calx2, caly2, calx1, caly1);

                                                    drpy=((((a[i].y+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x+15*R-3+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, ((((a[i].x-10*R-3+calx1)/2+calx1)/2+calx1)/2+calx1)/2, drpy);

                                                    swape(i,j);
                                                    caly2=(((a[i].y+a[j].y)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2;
                                                    calx2=(((a[i].x-R+3+a[j].x-R+3)/2+((a[i].x-R+3+a[j].x-R+3)/2+ a[j].x-R+3)/2)/2+((a[i].x-R+3+a[j].x-R+3)/2+ a[j].x-R+3)/2)/2;
                                                    calx1=((((a[i].x-R+3+a[j].x-R+3)/2+(a[j].x-R+3))/2+a[j].x-R+3)/2+a[j].x-R+3)/2;
                                                    caly1=((((a[i].y+a[j].y)/2+a[j].y)/2+a[j].y)/2+a[j].y)/2;
                                                    ///line(calx2, caly2, calx1, caly1);

                                                    drpy=((((a[i].y+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x-15*R+3+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, ((((a[i].x+10*R+3+calx1)/2+calx1)/2+calx1)/2+calx1)/2, drpy);
                                                    swape(i,j);
                                                }

                                                if(suntcosturi==1)
                                                {

                                                    setbkcolor(DARKGRAY);
                                                    setbkcolor(COLOR(17,19,58));

                                                    setfillstyle(SOLID_FILL,DARKGRAY);
                                                    setcolor(WHITE);

                                                    char nr[5];
                                                    sprintf(nr, "%d", MatriceAdiac[i][j]);

                                                    if(MatriceAdiac[i][j]>0)
                                                        outtextxy((a[i].x+a[j].x)/2, (a[i].y+a[j].y)/2, nr);

                                                    setcolor(BLACK);
                                                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    setcolor(WHITE);
                                                }
                                                ClearPlayBO(0);

                                            }
                                            else if(MatriceAdiac[i][j]==0 && i!=p && j!=p && MatriceAdiac[j][i]!=0)
                                            {
                                                int calx1,caly1,calx2,caly2,mijx,mijy,drpy,drpx, mijlx, mijly;
                                                double dist;
                                                setcolor(BLACK);
                                                if(maximul(a[i].x-a[j].x,a[j].x-a[i].x)>maximul(a[i].y-a[j].y,a[j].y-a[i].y))
                                                {
                                                    swape(i,j);
                                                    setcolor(BLACK);
                                                    calx2=(((a[i].x+a[j].x)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2;
                                                    caly2=(((a[i].y-R+3+a[j].y-R+3)/2+((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))/2)/2+((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))/2)/2;
                                                    calx1=((((a[i].x+a[j].x)/2+ a[j].x)/2+a[j].x)/2+a[j].x)/2;
                                                    caly1=((((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))/2+a[j].y-R+3)/2+a[j].y-R+3)/2;
                                                    mijy=(caly1+caly2)/2;
                                                    dist=sqrt((calx1-mijx)*(calx1-mijx)+(caly1-mijy)*(caly1-mijy));
                                                    dist/=2;
                                                    drpy=((((a[i].y-15*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    ///setcolor(DARKGRAY);

                                                    line(a[i].x,a[i].y-R+3,a[j].x,a[j].y-R+3);
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, drpx, ((((a[i].y+10*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);
                                                    ///line(drpx, drpy, drpx, ((((a[i].y+10*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);

                                                    mijlx=(calx1+drpx+drpx)/3;
                                                    mijly=(caly1+drpy+((((a[i].y+10*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2)/3;

                                                    ///setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    ///floodfill(mijlx, mijly+4, DARKGRAY);
                                                    ///floodfill(mijlx, mijly-3, DARKGRAY);


                                                    swape(i,j);
                                                }
                                                else
                                                {
                                                    swape(i,j);
                                                    line(a[i].x+R-3,a[i].y,a[j].x+R-3,a[j].y);
                                                    caly2=(((a[i].y+a[j].y)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2;
                                                    calx2=(((a[i].x+R-3+a[j].x+R-3)/2+((a[i].x+R-3+a[j].x+R-3)/2+ a[j].x+R-3)/2)/2+((a[i].x+R-3+a[j].x+R-3)/2+ a[j].x+R-3)/2)/2;
                                                    calx1=((((a[i].x+R-3+a[j].x+R-3)/2+(a[j].x+R-3))/2+a[j].x+R-3)/2+a[j].x+R-3)/2;
                                                    caly1=((((a[i].y+a[j].y)/2+a[j].y)/2+a[j].y)/2+a[j].y)/2;
                                                    ///line(calx2, caly2, calx1, caly1);

                                                    drpy=((((a[i].y+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x+15*R-3+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, ((((a[i].x-10*R-3+calx1)/2+calx1)/2+calx1)/2+calx1)/2, drpy);
                                                    swape(i,j);
                                                }

                                                if(suntcosturi==1)
                                                {

                                                    setbkcolor(DARKGRAY);
                                                    setbkcolor(COLOR(17,19,58));

                                                    setfillstyle(SOLID_FILL,DARKGRAY);
                                                    setcolor(WHITE);

                                                    char nr[5];
                                                    sprintf(nr, "%d", MatriceAdiac[i][j]);

                                                    if(MatriceAdiac[i][j]>0)
                                                        outtextxy((a[i].x+a[j].x)/2, (a[i].y+a[j].y)/2, nr);

                                                    setcolor(BLACK);
                                                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    setcolor(WHITE);
                                                }
                                                ClearPlayBO(0);

                                            }
                                            else
                                                ClearPlayBO(0);

                                        }
                }

                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    butonas=0;
                    break;
                }
                page=1-page;

            }
            a[mem1].x=poz.x;
            a[mem1].y=poz.y;

        }
        else ClearPlayBO(0);
        setactivepage(0);
        setvisualpage(0);
        ClearPlayBO(0);
    }



    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();

        if(x>=0 && x<=100 && y>=0 && y<=40)
        {
            suntcosturi=0;
            for(int i=1; i<=ct; i++)
                for(int j=1; j<=ct; j++)
                    MatriceAdiac[i][j]=0;
            ct=0;
            OptiuneComenziuwu=2;
            butonas=0;
            MainMenu();
        }
        if(x>=0 && x<=130 && y>=40 && y<=80)
        {
            suntcosturi=0;
            for(int i=1; i<=ct; i++)
                for(int j=1; j<=ct; j++)
                    MatriceAdiac[i][j]=0;
            ct=0;
            OptiuneComenziuwu=2;
            butonas=0;
            meniuGrafO();

        }


        if(x>=145 && x<=195 && x>=15 && y<=65)
        {
            saveFilePath();
            SaveFile(CaleSave);
        }

        ///rectangle(1250, 370, 1450, 410);///COMPONENTE
        /// readimagefile("2715724.jpg",145,15,195,65);
        /// readimagefile("1234.jpg",205,25,245,55);

        if(x>=205 && x<=245 && y>=25 && y<=55)
        {
            openFile();
            BuildSave(CaleOpen);
            ClearPlayBO(0);
        }


        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();

        if(x>=270 && x<=520 && y>=10 && y<=40)
        {
            OptiuneComenziuwu=1;
            setfillstyle(SOLID_FILL,YELLOW);
            bar(270,10,520,40);
            setcolor(BLACK);
            setbkcolor(YELLOW);
            char titlu[40];
            strcpy(titlu,"Comenzi consola");
            outtextxy(305,15,titlu);
            setcolor(BLACK);
            rectangle(270,10,520,40);
            setfillstyle(SOLID_FILL,WHITE);
            bar(270,41,520,70);
            setcolor(BLACK);
            setbkcolor(WHITE);
            strcpy(titlu,"Comenzi ecran");
            outtextxy(320,45,titlu);
            setcolor(BLACK);
            rectangle(270,41,520,70);
        }
        if(x>=270 && x<=520 && y>=41 && y<=70)
        {
            OptiuneComenziuwu=2;
            setfillstyle(SOLID_FILL,WHITE);
            bar(270,10,520,40);
            setcolor(BLACK);
            setbkcolor(WHITE);
            char titlu[40];
            strcpy(titlu,"Comenzi consola");
            outtextxy(305,15,titlu);
            setcolor(BLACK);
            rectangle(270,10,520,40);
            setfillstyle(SOLID_FILL,YELLOW);
            bar(270,41,520,70);
            setcolor(BLACK);
            setbkcolor(YELLOW);
            strcpy(titlu,"Comenzi ecran");
            outtextxy(320,45,titlu);
            setcolor(BLACK);
            rectangle(270,41,520,70);
        }

        setbkcolor(COLOR(17,19,58));
        setcolor(WHITE);

        if(x>=653 && x<=818 && y>=710 && y<=735)///activare buton creare nod
            if(butonas!=1)
            {
                butonas=1;

            }

        if(x>=880 && x<=1045 && y>=710 && y<=735)///activare buton stergere nod
            if(butonas!=2)
            {
                butonas=2;

            }
        if(x>=220 && x<=385 && y>=710 && y<=735)///activare buton creare muchii
            if(butonas!=3)
            {
                if(craiova==0)
                    craiova=1;
                butonas=3;

            }

        if(x>=447 && x<=612 && y>=710 && y<=735)///activare buton stergere muchii
            if(butonas!=4)
            {
                butonas=4;

            }

        if(x>=1086 && x<=1251 && y>=710 && y<=735)///activare buton creare cost
            if(butonas!=5)
            {
                butonas=5;

            }

        if(x>=1313 && x<=1478 && y>=710 && y<=735)///activare buton stergere cost
            if(butonas!=6)
            {
                butonas=6;

            }

        if(x>=1310 && x<=1385 && y>=190 && y<=230)
            if(butonas!=7) ///BUTONUL DE DFS
            {   ClearPlayBO(0);
                butonas=7;

            }

        ///rectangle(1310, 250, 1385, 290);
        if(x>=1310 && x<=1385 && y>=250 && y<=290)
            if(butonas!=8)
            {   ClearPlayBO(0);
                butonas=8;

            }

        ///rectangle(1250, 310, 1450, 350);
        if(x>=1250 && x<=1450 && y>=310 && y<=350)
            if(butonas!=9)
            {
                butonas=9;

            }

        ///rectangle(1250, 370, 1450, 410);
        if(x>=1250 && x<=1450 && y>=370 && y<=410)
            if(butonas!=10)
            {
                butonas=10;

            }

        ///rectangle(1295, 430, 1405, 470);
        if(x>=1295 && x<=1405 && y>=430 && y<=470)
            if(butonas!=11)
            {
                butonas=11;

            }

        ///rectangle(1270, 490, 1435, 530);
        if(x>=1270 && x<=1435 && y>=490 && y<=530)
            if(butonas!=12)
            {
                butonas=12;

            }

        ///rectangle(1280, 550, 1425, 590);
        ///rectangle(1250, 140, 1450, 180);
        if(x>=1250 && x<=1450 && y>=90 && y<=130)
            if(butonas!=13)
            {
                butonas=13;

            }

        if (x>=1250 && x<=1450 && y>=140 && y<=180)
            if(butonas!=15)
            {
                butonas=15;
            }
        ///aici las restul de butonase
        if(OptiuneComenziuwu==2)
        {
            ///1
            if(x>=225 && x<=1175 && y>=105 && y<=625 && butonas==3)
            {
                p=-1;
                x1=-5;
                y1=-5;
                x=mousex();
                y=mousey();
                for(j=1; j<=ct; j++)
                    if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R)
                    {
                        mem1=j;
                        x1=a[j].x;
                        y1=a[j].y;
                        combm=1;
                        break;
                    }

                if(x1!=-5 && y1!=-5)
                {
                    ClearPlayBO(0);
                    setactivepage(1);
                    putimage(0,0,poza,0);
                    setvisualpage(0);
                    POINT poz;
                    while(1)
                    {
                        setactivepage(page);
                        setvisualpage(1-page);
                        ClearPlayBO(0);
                        GetCursorPos(&poz);
                        poz.y-=30;
                        setcolor(BLACK);
                        if(poz.x>230 && poz.x<1170 && poz.y>110 && poz.y<620)
                            line(x1, y1, poz.x, poz.y);
                        setcolor(WHITE);
                        if(ismouseclick(WM_LBUTTONDOWN)) break;
                        page=1-page;
                    }
                    {
                        clearmouseclick(WM_LBUTTONDOWN);
                        x=mousex();
                        y=mousey();
                        for(j=1; j<=ct; j++)
                        {
                            if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R && x1!=x && y1!=y && MatriceAdiac[mem1][j]==0)
                            {
                                x2=a[j].x;
                                y2=a[j].y;

                                if(mem1<=ct && j<=ct )
                                {
                                    MatriceAdiac[mem1][j]=1;
                                    mmij[++nrmuchii][1]=a[mem1].val;
                                    mmij[nrmuchii][2]=a[j].val;
                                    mmij[nrmuchii][3]=(x1+x2)/2;
                                    mmij[nrmuchii][4]=(y1+y2)/2;
                                    mmij[nrmuchii][5]=((x1+x2)/2+x1)/2;
                                    mmij[nrmuchii][6]=((y1+y2)/2+y1)/2;
                                    mmij[nrmuchii][7]=((x1+x2)/2+x2)/2;
                                    mmij[nrmuchii][8]=((y1+y2)/2+y2)/2;

                                }
                                setcolor(WHITE);
                                setbkcolor(COLOR(17,19,58));
                                char nr[5];
                                sprintf(nr,"%d",a[j].val);
                                if(a[j].val>=100)  outtextxy(x2-15, y2-10,nr);
                                else if(a[j].val>=10) outtextxy(x2-11, y2-10,nr);
                                else outtextxy(x2-7, y2-10,nr);
                                sprintf(nr,"%d",a[mem1].val);
                                if(a[mem1].val>=100)  outtextxy(x1-15, y1-10,nr);
                                else if(a[mem1].val>=10) outtextxy(x1-11, y1-10,nr);
                                else outtextxy(x1-7, y1-10,nr);
                                combm=0;


                                int i,ij;
                                swape(j,ij);
                                for(i=1; i<=ct; i++)
                                    for(j=i; j<=ct; j++)
                                        if(i!=j)
                                        {
                                            if(MatriceAdiac[i][j]!=0 && i!=p && j!=p && MatriceAdiac[j][i]==0)
                                            {
                                                int calx1,caly1,calx2,caly2,mijx,mijy,drpy,drpx, mijlx, mijly;
                                                double dist;
                                                setcolor(BLACK);
                                                if(maximul(a[i].x-a[j].x,a[j].x-a[i].x)>maximul(a[i].y-a[j].y,a[j].y-a[i].y))
                                                {
                                                    calx2=(((a[i].x+a[j].x)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2;
                                                    caly2=(((a[i].y+R-3+a[j].y+R-3)/2+((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))/2)/2+((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))/2)/2;
                                                    calx1=((((a[i].x+a[j].x)/2+a[j].x)/2+a[j].x)/2+a[j].x)/2;
                                                    caly1=((((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))/2+a[j].y+R-3)/2+a[j].y+R-3)/2;
                                                    line(a[i].x,a[i].y+R-3,a[j].x,a[j].y+R-3);
                                                    ///setcolor(DARKGRAY);
                                                    ///line(calx2, caly2, calx1, caly1);
                                                    ///calx2=(calx2+calx1)/2;
                                                    ///caly2=(caly2+caly1)/2;
                                                    ///line(calx1, caly1, calx1, caly2);
                                                    ///line(calx1, caly1, calx2, caly1);
                                                    mijx=(calx1+calx2)/2;
                                                    mijy=(caly1+caly2)/2;
                                                    dist=sqrt((calx1-mijx)*(calx1-mijx)+(caly1-mijy)*(caly1-mijy));
                                                    dist/=2;
                                                    drpy=((((a[i].y+15*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, drpx, ((((a[i].y-10*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);
                                                    ///line(drpx, drpy, drpx, ((((a[i].y-10*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);

                                                    mijlx=(calx1+drpx+drpx)/3;
                                                    mijly=(caly1+drpy+((((a[i].y-10*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2)/3;

                                                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    ///floodfill(mijlx, mijly+3, DARKGRAY);
                                                    ///floodfill(mijlx, mijly-3, DARKGRAY);

                                                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    ///floodfill(drpx+1, drpy-25, BLACK);

                                                    ///line(mijx, mijy, calx1+dist, mijy);
                                                    ///line(mijx, mijy, calx2-dist, mijy);
                                                    ///line(calx1, caly1, mijx, mijy+dist);
                                                    ///line(calx1, caly1, mijx, mijy-dist);
                                                }
                                                else
                                                {
                                                    line(a[i].x+R-3,a[i].y,a[j].x+R-3,a[j].y);
                                                    caly2=(((a[i].y+a[j].y)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2;
                                                    calx2=(((a[i].x+R-3+a[j].x+R-3)/2+((a[i].x+R-3+a[j].x+R-3)/2+ a[j].x+R-3)/2)/2+((a[i].x+R-3+a[j].x+R-3)/2+ a[j].x+R-3)/2)/2;
                                                    calx1=((((a[i].x+R-3+a[j].x+R-3)/2+(a[j].x+R-3))/2+a[j].x+R-3)/2+a[j].x+R-3)/2;
                                                    caly1=((((a[i].y+a[j].y)/2+a[j].y)/2+a[j].y)/2+a[j].y)/2;
                                                    ///line(calx2, caly2, calx1, caly1);

                                                    drpy=((((a[i].y+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x+15*R-3+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, ((((a[i].x-10*R-3+calx1)/2+calx1)/2+calx1)/2+calx1)/2, drpy);
                                                }

                                                if(suntcosturi==1)
                                                {

                                                    setbkcolor(DARKGRAY);
                                                    setbkcolor(COLOR(17,19,58));

                                                    setfillstyle(SOLID_FILL,DARKGRAY);
                                                    setcolor(WHITE);

                                                    char nr[5];
                                                    sprintf(nr, "%d", MatriceAdiac[i][j]);

                                                    if(MatriceAdiac[i][j]>0)
                                                        outtextxy((a[i].x+a[j].x)/2, (a[i].y+a[j].y)/2, nr);

                                                    setcolor(BLACK);
                                                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    setcolor(WHITE);
                                                }
                                            }
                                            else if(MatriceAdiac[i][j]!=0 && i!=p && j!=p && MatriceAdiac[j][i]!=0)
                                            {
                                                int calx1,caly1,calx2,caly2,mijx,mijy,drpy,drpx, mijlx, mijly;
                                                double dist;
                                                setcolor(BLACK);
                                                if(maximul(a[i].x-a[j].x,a[j].x-a[i].x)>maximul(a[i].y-a[j].y,a[j].y-a[i].y))
                                                {
                                                    calx2=(((a[i].x+a[j].x)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2;
                                                    caly2=(((a[i].y+R-3+a[j].y+R-3)/2+((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))/2)/2+((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))/2)/2;
                                                    calx1=((((a[i].x+a[j].x)/2+ a[j].x)/2+a[j].x)/2+a[j].x)/2;
                                                    caly1=((((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))/2+a[j].y+R-3)/2+a[j].y+R-3)/2;
                                                    line(a[i].x,a[i].y+R-3,a[j].x,a[j].y+R-3);
                                                    line(a[i].x,a[i].y-R+3,a[j].x,a[j].y-R+3);
                                                    ///setcolor(DARKGRAY);
                                                    ///line(calx2, caly2, calx1, caly1);
                                                    ///calx2=(calx2+calx1)/2;
                                                    ///caly2=(caly2+caly1)/2;
                                                    ///line(calx1, caly1, calx1, caly2);
                                                    ///line(calx1, caly1, calx2, caly1);
                                                    mijx=(calx1+calx2)/2;
                                                    mijy=(caly1+caly2)/2;
                                                    dist=sqrt((calx1-mijx)*(calx1-mijx)+(caly1-mijy)*(caly1-mijy));
                                                    dist/=2;
                                                    drpy=((((a[i].y+15*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, drpx, ((((a[i].y-10*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);
                                                    ///line(drpx, drpy, drpx, ((((a[i].y-10*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);

                                                    mijlx=(calx1+drpx+drpx)/3;
                                                    mijly=(caly1+drpy+((((a[i].y-10*R-3+caly1)/2+caly1)/2+caly1)/2+caly1)/2)/3;

                                                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    ///floodfill(mijlx, mijly+3, DARKGRAY);
                                                    ///floodfill(mijlx, mijly-3, DARKGRAY);

                                                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    ///floodfill(drpx+1, drpy-25, BLACK);

                                                    ///line(mijx, mijy, calx1+dist, mijy);
                                                    ///line(mijx, mijy, calx2-dist, mijy);
                                                    ///line(calx1, caly1, mijx, mijy+dist);
                                                    ///line(calx1, caly1, mijx, mijy-dist);
                                                    swape(i,j);
                                                    setcolor(BLACK);
                                                    calx2=(((a[i].x+a[j].x)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2;
                                                    caly2=(((a[i].y-R+3+a[j].y-R+3)/2+((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))/2)/2+((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))/2)/2;
                                                    calx1=((((a[i].x+a[j].x)/2+ a[j].x)/2+a[j].x)/2+a[j].x)/2;
                                                    caly1=((((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))/2+a[j].y-R+3)/2+a[j].y-R+3)/2;
                                                    mijy=(caly1+caly2)/2;
                                                    dist=sqrt((calx1-mijx)*(calx1-mijx)+(caly1-mijy)*(caly1-mijy));
                                                    dist/=2;
                                                    drpy=((((a[i].y-15*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    ///setcolor(DARKGRAY);
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, drpx, ((((a[i].y+10*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);
                                                    ///line(drpx, drpy, drpx, ((((a[i].y+10*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);

                                                    mijlx=(calx1+drpx+drpx)/3;
                                                    mijly=(caly1+drpy+((((a[i].y+10*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2)/3;

                                                    ///setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    ///floodfill(mijlx, mijly+4, DARKGRAY);
                                                    ///floodfill(mijlx, mijly-3, DARKGRAY);


                                                    swape(i,j);
                                                    ClearPlayBO(0);
                                                }
                                                else
                                                {
                                                    line(a[i].x+R-3,a[i].y,a[j].x+R-3,a[j].y);
                                                    line(a[i].x-R+3,a[i].y,a[j].x-R+3,a[j].y);
                                                    caly2=(((a[i].y+a[j].y)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2;
                                                    calx2=(((a[i].x+R-3+a[j].x+R-3)/2+((a[i].x+R-3+a[j].x+R-3)/2+ a[j].x+R-3)/2)/2+((a[i].x+R-3+a[j].x+R-3)/2+ a[j].x+R-3)/2)/2;
                                                    calx1=((((a[i].x+R-3+a[j].x+R-3)/2+(a[j].x+R-3))/2+a[j].x+R-3)/2+a[j].x+R-3)/2;
                                                    caly1=((((a[i].y+a[j].y)/2+a[j].y)/2+a[j].y)/2+a[j].y)/2;
                                                    ///line(calx2, caly2, calx1, caly1);

                                                    drpy=((((a[i].y+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x+15*R-3+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, ((((a[i].x-10*R-3+calx1)/2+calx1)/2+calx1)/2+calx1)/2, drpy);

                                                    swape(i,j);
                                                    caly2=(((a[i].y+a[j].y)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2;
                                                    calx2=(((a[i].x-R+3+a[j].x-R+3)/2+((a[i].x-R+3+a[j].x-R+3)/2+ a[j].x-R+3)/2)/2+((a[i].x-R+3+a[j].x-R+3)/2+ a[j].x-R+3)/2)/2;
                                                    calx1=((((a[i].x-R+3+a[j].x-R+3)/2+(a[j].x-R+3))/2+a[j].x-R+3)/2+a[j].x-R+3)/2;
                                                    caly1=((((a[i].y+a[j].y)/2+a[j].y)/2+a[j].y)/2+a[j].y)/2;
                                                    ///line(calx2, caly2, calx1, caly1);

                                                    drpy=((((a[i].y+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x-15*R+3+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, ((((a[i].x+10*R+3+calx1)/2+calx1)/2+calx1)/2+calx1)/2, drpy);
                                                    swape(i,j);
                                                }

                                                if(suntcosturi==1)
                                                {

                                                    setbkcolor(DARKGRAY);
                                                    setbkcolor(COLOR(17,19,58));

                                                    setfillstyle(SOLID_FILL,DARKGRAY);
                                                    setcolor(WHITE);

                                                    char nr[5];
                                                    sprintf(nr, "%d", MatriceAdiac[i][j]);

                                                    if(MatriceAdiac[i][j]>0)
                                                        outtextxy((a[i].x+a[j].x)/2, (a[i].y+a[j].y)/2, nr);

                                                    setcolor(BLACK);
                                                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    setcolor(WHITE);
                                                }
                                                ClearPlayBO(0);

                                            }
                                            else if(MatriceAdiac[i][j]==0 && i!=p && j!=p && MatriceAdiac[j][i]!=0)
                                            {
                                                int calx1,caly1,calx2,caly2,mijx,mijy,drpy,drpx, mijlx, mijly;
                                                double dist;
                                                setcolor(BLACK);
                                                if(maximul(a[i].x-a[j].x,a[j].x-a[i].x)>maximul(a[i].y-a[j].y,a[j].y-a[i].y))
                                                {
                                                    swape(i,j);
                                                    setcolor(BLACK);
                                                    calx2=(((a[i].x+a[j].x)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2+((a[i].x+a[j].x)/2+ a[j].x)/2)/2;
                                                    caly2=(((a[i].y-R+3+a[j].y-R+3)/2+((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))/2)/2+((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))/2)/2;
                                                    calx1=((((a[i].x+a[j].x)/2+ a[j].x)/2+a[j].x)/2+a[j].x)/2;
                                                    caly1=((((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))/2+a[j].y-R+3)/2+a[j].y-R+3)/2;
                                                    mijy=(caly1+caly2)/2;
                                                    dist=sqrt((calx1-mijx)*(calx1-mijx)+(caly1-mijy)*(caly1-mijy));
                                                    dist/=2;
                                                    drpy=((((a[i].y-15*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    ///setcolor(DARKGRAY);

                                                    line(a[i].x,a[i].y-R+3,a[j].x,a[j].y-R+3);
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, drpx, ((((a[i].y+10*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);
                                                    ///line(drpx, drpy, drpx, ((((a[i].y+10*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2);

                                                    mijlx=(calx1+drpx+drpx)/3;
                                                    mijly=(caly1+drpy+((((a[i].y+10*R+3+caly1)/2+caly1)/2+caly1)/2+caly1)/2)/3;

                                                    ///setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    ///floodfill(mijlx, mijly+4, DARKGRAY);
                                                    ///floodfill(mijlx, mijly-3, DARKGRAY);


                                                    swape(i,j);
                                                }
                                                else
                                                {
                                                    swape(i,j);
                                                    line(a[i].x+R-3,a[i].y,a[j].x+R-3,a[j].y);
                                                    caly2=(((a[i].y+a[j].y)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2+((a[i].y+a[j].y)/2+(a[j].y))/2)/2;
                                                    calx2=(((a[i].x+R-3+a[j].x+R-3)/2+((a[i].x+R-3+a[j].x+R-3)/2+ a[j].x+R-3)/2)/2+((a[i].x+R-3+a[j].x+R-3)/2+ a[j].x+R-3)/2)/2;
                                                    calx1=((((a[i].x+R-3+a[j].x+R-3)/2+(a[j].x+R-3))/2+a[j].x+R-3)/2+a[j].x+R-3)/2;
                                                    caly1=((((a[i].y+a[j].y)/2+a[j].y)/2+a[j].y)/2+a[j].y)/2;
                                                    ///line(calx2, caly2, calx1, caly1);

                                                    drpy=((((a[i].y+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                                                    drpx=((((a[i].x+15*R-3+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                                                    line(calx1, caly1, drpx, drpy);
                                                    line(calx1, caly1, ((((a[i].x-10*R-3+calx1)/2+calx1)/2+calx1)/2+calx1)/2, drpy);
                                                    swape(i,j);
                                                }

                                                if(suntcosturi==1)
                                                {

                                                    setbkcolor(DARKGRAY);
                                                    setbkcolor(COLOR(17,19,58));

                                                    setfillstyle(SOLID_FILL,DARKGRAY);
                                                    setcolor(WHITE);

                                                    char nr[5];
                                                    sprintf(nr, "%d", MatriceAdiac[i][j]);

                                                    if(MatriceAdiac[i][j]>0)
                                                        outtextxy((a[i].x+a[j].x)/2, (a[i].y+a[j].y)/2, nr);

                                                    setcolor(BLACK);
                                                    setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                                    setcolor(WHITE);
                                                }
                                                ClearPlayBO(0);

                                            }
                                            else
                                                ClearPlayBO(0);

                                        }
                                swape(ij,j);

                                setvisualpage(0);
                                setactivepage(0);
                            }
                        }

                    }

                }
                ClearPlayBO(0);
            }

            if(butonas==4 && x>=225 && x<=1175 && y>=105 && y<=625)
            {
                if(stergeremuchii==0)
                {
                    x=mousex();
                    y=mousey();
                    for(j=1; j<=ct; j++)
                        if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R && stergeremuchii==0)
                        {
                            mem1=j;
                            x1=a[j].x;
                            y1=a[j].y;
                            stergeremuchii=1;
                            break;
                        }
                }


                if(stergeremuchii==1)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    x=mousex();
                    y=mousey();
                    for(j=1; j<=ct; j++)
                        if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R && x1!=x && y1!=y && mem1!=j)
                        {
                            x2=a[j].x;
                            y2=a[j].y;
                            setcolor(WHITE);
                            line(x1,y1,x2,y2);
                            line(x2,y2,x1,y1);
                            setcolor(WHITE);
                            MatriceAdiac[mem1][j]=0;
                            stergeremuchii=0;

                            for(int sm=1; sm<=nrmuchii; sm++)
                            {
                                if(mmij[sm][mem1]==mmij[sm][j])
                                    for(int smp=sm; smp<nrmuchii; smp++)
                                    {
                                        for(int numaipot=1; numaipot<=10; numaipot++)
                                            mmij[smp][numaipot]=mmij[smp+1][numaipot];
                                    }
                                nrmuchii--;
                            }
                            ClearPlayBO(0);
                            break;
                        }
                }
            }
            ClearPlayBO(0);
        }
        ///1



        else if(OptiuneComenziuwu==1)
        {
            ///1
            if(butonas==4)
                if(x>=447 && x<=612 && y>=710 && y<=735)///stergere muchie
                {
                    fscroll=fopen("scrlo","a+");
                    int m1,m2,nou;
                    char sir[105];
                    int k=0;
                    consolex=17;
                    consoley+=25;
                    char var=getch();
                    while(var!=13)
                    {
                        if((var>='0' && var<='9') || var==32)
                        {
                            sir[k++]=var;
                            sir[k]=0;
                            char str[2];
                            str[0]=var;
                            str[1]=0;
                            setbkcolor(DARKGRAY);
                            setcolor(WHITE);
                            outtextxy(consolex-15, consoley-15,str);
                            setbkcolor(COLOR(17,19,58));
                            consolex+=15;
                            if(consolex>175)
                            {
                                sir[k]=0;
                                k=0;
                                fprintf(fscroll,"%s",sir);
                                fputc(10,fscroll);
                                linesnr++;
                                consoley+=25;
                                consolex=17;
                            }
                        }
                        if(var==8)
                        {
                            sir[--k]=0;
                            sir[k]=0;
                            if(consolex-15>0) consolex-=15;
                            else if(consolex-15<=9 && consoley-50>80)
                            {
                                linesnr--;
                                consoley-=25;
                                consolex=197;
                            }
                            setfillstyle(SOLID_FILL,DARKGRAY);
                            bar(consolex-15,consoley-15,consolex,consoley);
                            setcolor(WHITE);
                        }
                        var=getch();
                    }
                    sir[k]=0;
                    fprintf(fscroll,"%s",sir);
                    linesnr++;
                    fputc(10,fscroll);
                    fclose(fscroll);
                    m1=m2=nou=0;

                    char *p,sep[]=" ",aux[105];
                    p=strtok(sir,sep);
                    while(p!=0)
                    {
                        nou=0;
                        strcpy(aux,p);
                        for(int i=0; i<strlen(aux); i++)
                            nou=nou*10+(aux[i]-48);
                        if(m1==0 && m2==0) m1=nou;
                        else if(m2==0) m2=nou;
                        p=strtok(0,sep);
                    }

                    if(m1<=ct && m2<=ct && m1!=0 && m2!=0)
                    {
                        MatriceAdiac[m1][m2]=0;
                        setcolor(WHITE);
                        line(a[m1].x,a[m1].y,a[m2].x,a[m2].y);
                        setcolor(COLOR(17,19,58));
                        setcolor(DARKGRAY);
                        circle(a[m1].x,a[m1].y,R);
                        setfillstyle(SOLID_FILL,COLOR(17,19,58));
                        floodfill(a[m1].x+1,a[m1].y,DARKGRAY);
                        setcolor(WHITE);
                        setbkcolor(COLOR(17,19,58));
                        char nr[5];
                        sprintf(nr,"%d",m1);
                        if(ct>=100)  outtextxy(a[m1].x-15, a[m1].y-10,nr);
                        else if(ct>=10) outtextxy(a[m1].x-11, a[m1].y-10,nr);
                        else outtextxy(a[m1].x-7, a[m1].y-10,nr);

                        setcolor(DARKGRAY);
                        circle(a[m2].x,a[m2].y,R);
                        setfillstyle(SOLID_FILL,COLOR(17,19,58));
                        floodfill(a[m2].x+1,a[m2].y,DARKGRAY);
                        setcolor(WHITE);
                        sprintf(nr,"%d",m2);
                        if(ct>=100)  outtextxy(a[m2].x-15, a[m2].y-10,nr);
                        else if(ct>=10) outtextxy(a[m2].x-11, a[m2].y-10,nr);
                        else outtextxy(a[m2].x-7, a[m2].y-10,nr);
                    }
                    ClearPlayBO(0);
                }

            if(butonas==3)
                if(x>=220 && x<=385 && y>=710 && y<=735)///adaugare muchie
                {
                    fscroll=fopen("scrlo","a+");
                    int m1,m2,nou;
                    char sir[105];
                    int k=0;
                    consolex=17;
                    consoley+=25;
                    char var=getch();
                    while(var!=13)
                    {
                        if((var>='0' && var<='9') || var==32)
                        {
                            sir[k++]=var;
                            sir[k]=0;
                            char str[2];
                            str[0]=var;
                            str[1]=0;
                            setbkcolor(DARKGRAY);
                            outtextxy(consolex-15, consoley-15,str);
                            setbkcolor(COLOR(17,19,58));
                            consolex+=15;
                            if(consolex>175)
                            {
                                sir[k]=0;
                                k=0;
                                fprintf(fscroll,"%s",sir);
                                fputc(10,fscroll);
                                linesnr++;
                                consoley+=25;
                                consolex=17;
                            }
                        }
                        if(var==8)
                        {
                            sir[--k]=0;
                            sir[k]=0;
                            if(consolex-15>0) consolex-=15;
                            else if(consolex-15<=9 && consoley-50>80)
                            {
                                linesnr--;
                                consoley-=25;
                                consolex=197;
                            }
                            setfillstyle(SOLID_FILL,DARKGRAY);
                            bar(consolex-15,consoley-15,consolex,consoley);
                            setcolor(WHITE);
                        }
                        var=getch();
                    }
                    sir[k]=0;
                    fprintf(fscroll,"%s",sir);
                    linesnr++;
                    fputc(10,fscroll);
                    fclose(fscroll);
                    m1=m2=nou=0;

                    char *p,sep[]=" ",aux[105];
                    p=strtok(sir,sep);
                    while(p!=0)
                    {
                        nou=0;
                        strcpy(aux,p);
                        for(int i=0; i<strlen(aux); i++)
                            nou=nou*10+(aux[i]-48);
                        if(m1==0 && m2==0) m1=nou;
                        else if(m2==0) m2=nou;
                        p=strtok(0,sep);
                    }

                    if(m1<=ct && m2<=ct && m1!=0 && m2!=0)
                    {
                        MatriceAdiac[m1][m2]=1;
                        setcolor(COLOR(17,19,58));
                        line(a[m1].x,a[m1].y,a[m2].x,a[m2].y);
                        setcolor(WHITE);
                    }
                    ClearPlayBO(0);
                }
            ///1

        }

        if(x>=225 && x<=1175 && y>=105 && y<=625)///adugare de noduri
            if(butonas==1)
            {
                ct++;
                a[ct].x=x;
                a[ct].y=y;
                a[ct].val=ct;

                setcolor(DARKGRAY);
                circle(x,y,R);
                setfillstyle(SOLID_FILL,COLOR(17,19,58));
                floodfill(x,y,DARKGRAY);

                setcolor(WHITE);
                setbkcolor(COLOR(17,19,58));
                char nr[5];
                sprintf(nr,"%d",ct);
                if(ct>=100)  outtextxy(x-15, y-10,nr);
                else if(ct>=10) outtextxy(x-11, y-10,nr);
                else outtextxy(x-7, y-10,nr);
            }

        if(butonas==2 && x>=225 && x<=1175 && y>=105 && y<=625)///sterge nod
        {
            for(int l=1; l<=ct; l++)
            {
                if(x<=a[l].x+R && x>=a[l].x-R && y<=a[l].y+R && y>=a[l].y-R)
                {
                    int nodsters;
                    nodsters=a[l].val;

                    for(int i=1; i<=ct; i++)
                        if(MatriceAdiac[nodsters][i]!=0)
                        {
                            setcolor(WHITE);
                            line(a[nodsters].x, a[nodsters].y, a[i].x, a[i].y);
                            line(a[i].x, a[i].y, a[nodsters].x, a[nodsters].y);
                            setcolor(BLACK);
                        }

                    for(int i=1; i<=ct; i++)
                        if(MatriceAdiac[i][nodsters]!=0)
                        {
                            setcolor(WHITE);
                            line(a[nodsters].x, a[nodsters].y, a[i].x, a[i].y);
                            line(a[i].x, a[i].y, a[nodsters].x, a[nodsters].y);
                            setcolor(BLACK);
                        }

                    for(int i=1; i<=ct; i++)
                        for(int j=1; j<=ct; j++)
                            if(i==nodsters || j==nodsters)
                                if(MatriceAdiac[i][j]!=0)
                                    MatriceAdiac[i][j]=0;

                    for(int i=1; i<=ct; i++)
                        for(int j=nodsters; j<ct; j++)
                            MatriceAdiac[i][j]=MatriceAdiac[i][j+1];

                    for(int i=nodsters; i<ct; i++)
                        for(int j=1; j<=ct; j++)
                            MatriceAdiac[i][j]=MatriceAdiac[i+1][j];

                    for(int i=1; i<=ct; i++)
                    {
                        MatriceAdiac[i][ct]=0;
                        MatriceAdiac[ct][i]=0;
                    }

                    for(int i=nodsters; i<=ct; i++)
                    {
                        a[i].x=a[i+1].x;
                        a[i].y=a[i+1].y;
                        a[i].val=a[i+1].val;
                    }

                    for(int i=1; i<=ct; i++)
                        a[i].val=i;

                    ct--;

                    ClearPlayBO(nodsters);
                }
            }
            ClearPlayBO(0);
        }

        if(butonas==5)///adaugare cost
            if(x>=225 && x<=1175 && y>=105 && y<=625 && butonas==5)
            {
                for(j=1; j<=ct; j++)
                    if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R && adaugcost==0)
                    {
                        mem1=j;
                        x1=a[j].x;
                        y1=a[j].y;
                        adaugcost=1;
                        break;
                    }

                if(adaugcost==1)
                {
                    clearmouseclick(WM_LBUTTONDOWN);
                    x=mousex();
                    y=mousey();
                    for(j=1; j<=ct; j++)
                        if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R && x1!=x && y1!=y && mem1!=j && MatriceAdiac[mem1][j]!=0)
                        {
                            x2=a[j].x;
                            y2=a[j].y;
                            if(mem1 < j)
                            {
                                if(maximul(a[mem1].x-a[j].x, a[j].x-a[mem1].x)> maximul(a[j].y-a[mem1].y, a[mem1].y-a[j].y))
                                {
                                    outtextxy((a[mem1].x+a[j].x)/2, (a[mem1].y+a[j].y)/2+R, " ");
                                    int m1,m2,nou;
                                    char sir[105];
                                    for(int i=1; i<=104; i++)
                                        sir[i]=0;
                                    int lgc=0;
                                    char var=getch();
                                    while(var!=13)
                                    {
                                        if((var>='0' && var<='9') || var==32 || var=='-')
                                        {
                                            sir[lgc++]=var;
                                            char str[2];
                                            str[0]=var;
                                            str[1]=0;
                                            setbkcolor(DARKGRAY);

                                            if(sir[0]!='-')
                                                outtextxy((a[mem1].x+a[j].x)/2, (a[mem1].y+a[j].y)/2+R, sir);
                                            setbkcolor(COLOR(17,19,58));
                                        }

                                        if(var==8)
                                        {
                                            sir[--lgc]=0;
                                            sir[lgc]=0;
                                            setfillstyle(SOLID_FILL,DARKGRAY);
                                            setcolor(WHITE);
                                        }
                                        var=getch();
                                    }
                                    sir[lgc]=0;

                                    char *p,sep[]=" ",aux[105];
                                    p=strtok(sir,sep);
                                    while(p!=0)
                                    {
                                        nou=0;
                                        strcpy(aux,p);
                                        for(int i=0; i<strlen(aux); i++)
                                            nou=nou*10+(aux[i]-48);
                                        MatriceAdiac[mem1][j]=nou;
                                        suntcosturi=1;
                                        if(m1==0 && m2==0) m1=nou;
                                        else if(m2==0) m2=nou;
                                        p=strtok(0,sep);
                                    }
                                }
                                else
                                {

                                    outtextxy((a[mem1].x+a[j].x)/2+R, (a[mem1].y+a[j].y)/2, " ");
                                    int m1,m2,nou;
                                    char sir[105];
                                    for(int i=1; i<=104; i++)
                                        sir[i]=0;
                                    int lgc=0;
                                    char var=getch();
                                    while(var!=13)
                                    {
                                        if(var>='0' && var<='9' || var==32 || var=='-')
                                        {
                                            sir[lgc++]=var;
                                            char str[2];
                                            str[0]=var;
                                            str[1]=0;
                                            setbkcolor(DARKGRAY);

                                            if(sir[0]!='-')
                                                outtextxy((a[mem1].x+a[j].x)/2+R, (a[mem1].y+a[j].y)/2, sir);
                                            setbkcolor(COLOR(17,19,58));
                                        }

                                        if(var==8)
                                        {
                                            sir[--lgc]=0;
                                            sir[lgc]=0;
                                            setfillstyle(SOLID_FILL,DARKGRAY);
                                            setcolor(WHITE);
                                        }
                                        var=getch();
                                    }
                                    sir[lgc]=0;

                                    char *p,sep[]=" ",aux[105];
                                    p=strtok(sir,sep);
                                    while(p!=0)
                                    {
                                        nou=0;
                                        strcpy(aux,p);
                                        for(int i=0; i<strlen(aux); i++)
                                            nou=nou*10+(aux[i]-48);
                                        MatriceAdiac[mem1][j]=nou;
                                        suntcosturi=1;
                                        if(m1==0 && m2==0) m1=nou;
                                        else if(m2==0) m2=nou;
                                        p=strtok(0,sep);
                                    }
                                }
                            }
                            else if(mem1 > j)
                            {
                                if(maximul(a[mem1].x-a[j].x, a[j].x-a[mem1].x)> maximul(a[j].y-a[mem1].y, a[mem1].y-a[j].y))
                                {

                                    outtextxy((a[mem1].x+a[j].x)/2, (a[mem1].y+a[j].y)/2-R, " ");
                                    int m1,m2,nou;
                                    char sir[105];
                                    for(int i=1; i<=104; i++)
                                        sir[i]=0;
                                    int lgc=0;
                                    char var=getch();
                                    while(var!=13)
                                    {
                                        if(var>='0' && var<='9' || var==32 || var=='-')
                                        {
                                            sir[lgc++]=var;
                                            char str[2];
                                            str[0]=var;
                                            str[1]=0;
                                            setbkcolor(DARKGRAY);

                                            if(sir[0]!='-')
                                            {
                                                outtextxy((a[mem1].x+a[j].x)/2, (a[mem1].y+a[j].y)/2-R, sir);

                                            }
                                            setbkcolor(COLOR(17,19,58));
                                        }

                                        if(var==8)
                                        {
                                            sir[--lgc]=0;
                                            sir[lgc]=0;
                                            setfillstyle(SOLID_FILL,DARKGRAY);
                                            setcolor(WHITE);
                                        }
                                        var=getch();
                                    }
                                    sir[lgc]=0;

                                    char *p,sep[]=" ",aux[105];
                                    p=strtok(sir,sep);
                                    while(p!=0)
                                    {
                                        nou=0;
                                        strcpy(aux,p);
                                        for(int i=0; i<strlen(aux); i++)
                                            nou=nou*10+(aux[i]-48);
                                        MatriceAdiac[mem1][j]=nou;
                                        suntcosturi=1;
                                        if(m1==0 && m2==0) m1=nou;
                                        else if(m2==0) m2=nou;
                                        p=strtok(0,sep);
                                    }
                                }
                                else
                                {

                                    outtextxy((a[mem1].x+a[j].x)/2-R, (a[mem1].y+a[j].y)/2, " ");
                                    int m1,m2,nou;
                                    char sir[105];
                                    for(int i=1; i<=104; i++)
                                        sir[i]=0;
                                    int lgc=0;
                                    char var=getch();
                                    while(var!=13)
                                    {
                                        if(var>='0' && var<='9' || var==32 || var=='-')
                                        {
                                            sir[lgc++]=var;
                                            char str[2];
                                            str[0]=var;
                                            str[1]=0;
                                            setbkcolor(DARKGRAY);

                                            if(sir[0]!='-')
                                            {
                                                outtextxy((a[mem1].x+a[j].x)/2-R, (a[mem1].y+a[j].y)/2, sir);

                                            }
                                            setbkcolor(COLOR(17,19,58));
                                        }

                                        if(var==8)
                                        {
                                            sir[--lgc]=0;
                                            sir[lgc]=0;
                                            setfillstyle(SOLID_FILL,DARKGRAY);
                                            setcolor(WHITE);
                                        }
                                        var=getch();
                                    }
                                    sir[lgc]=0;

                                    char *p,sep[]=" ",aux[105];
                                    p=strtok(sir,sep);
                                    while(p!=0)
                                    {
                                        nou=0;
                                        strcpy(aux,p);
                                        for(int i=0; i<strlen(aux); i++)
                                            nou=nou*10+(aux[i]-48);
                                        MatriceAdiac[mem1][j]=nou;
                                        suntcosturi=1;
                                        if(m1==0 && m2==0) m1=nou;
                                        else if(m2==0) m2=nou;
                                        p=strtok(0,sep);
                                    }
                                }
                            }

                            ClearPlayBO(0);
                            adaugcost=0;
                            break;
                        }
                }

                ClearPlayBO(0);
            }

        if(butonas==6 && x>=225 && x<=1175 && y>=105 && y<=625)///stergere cost
        {

            for(j=1; j<=ct; j++)
                if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R && stgcst==0)
                {
                    mem1=j;
                    x1=a[j].x;
                    y1=a[j].y;
                    stgcst=1;
                    break;
                }
            if(stgcst==1)
            {

                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();
                for(j=1; j<=ct; j++)
                    if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R && x1!=x && y1!=y && mem1!=j && MatriceAdiac[mem1][j]!=0)
                    {
                        x2=a[j].x;
                        y2=a[j].y;

                        MatriceAdiac[mem1][j]=1;
                        ClearPlayBO(0);
                        stgcst=0;
                        break;
                    }
            }

            ClearPlayBO(0);
        }

        if(butonas==7 && x>=225 && x<=1175 && y>=105 && y<=625)///DFS
        {
            fscroll=fopen("scrlo","a+");
            if(nrafisdfs==0)
                nrafisdfs++;
            if(nrafisdfs==1)
            {
                consolex=17;
                consoley+=25;
                setcolor(WHITE);
                setbkcolor(COLOR(17,19,58));
                outtextxy(consolex-15, consoley-15,"Sirul DFS: ");
                fprintf(fscroll,"%s","Sirul DFS: ");
                linesnr++;
                fputc(10,fscroll);
                nrafisdfs=0;
            }
            for(int j=1; j<=ct; j++)
            {
                if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R)
                {
                    nrdfs=0;
                    for(int kms=0; kms<=500; kms++)
                        viz[kms]=0;

                    dfs(a[j].val, vectordfs);

                    char sir[105],rand[1005];
                    int lg=0;

                    consolex=17;
                    consoley+=25;
                    linesnr++;

                    for(int kms=1; kms<=nrdfs; kms++)
                    {
                        sprintf(sir, "%d", vectordfs[kms]);

                        for(int i=0; i<strlen(sir); i++)
                        {
                            rand[lg++]=sir[i];
                            char nr[2];
                            nr[0]=sir[i];
                            nr[1]=0;
                            consolex+=15;
                            setbkcolor(DARKGRAY);
                            setcolor(WHITE);
                            outtextxy(consolex-15,consoley-17,nr);
                        }
                        rand[lg++]=' ';
                        consolex+=15;
                        char nr[2];
                        nr[0]=rand[lg-1];
                        nr[1]=0;
                        setbkcolor(DARKGRAY);
                        setcolor(WHITE);
                        outtextxy(consolex-15,consoley-17,nr);
                        if(consolex>175)
                        {
                            rand[lg]=0;
                            lg=0;
                            fprintf(fscroll,"%s",rand);
                            fputc(10,fscroll);
                            strcpy(rand,"");
                            consoley+=25;
                            consolex=17;
                            linesnr++;
                        }

                        setfillstyle(SOLID_FILL,DARKGRAY);
                        setcolor(WHITE);
                    }
                    rand[lg]=0;
                    fprintf(fscroll,"%s",rand);
                    fputc(10,fscroll);
                    break;
                }
            }

            fclose(fscroll);
        }

        if(butonas==8 && x>=225 && x<=1175 && y>=105 && y<=625)
        {
            fscroll=fopen("scrlo","a+");
            consolex=17;
            consoley+=25;
            setbkcolor(COLOR(17,19,58));
            outtextxy(consolex-15, consoley-15,"Sirul BFS: ");
            fprintf(fscroll,"%s","Sirul BFS: ");
            fputc(10,fscroll);
            linesnr++;

            for(int j=1; j<=ct; j++)
            {
                if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R)
                {
                    nbfs=1;
                    for(int kms=0; kms<=500; kms++)
                        vizbfs[kms]=0;

                    bfs(a[j].val, bfst);
                    afisbfs[1]=a[j].val;
                    char rand[1005];
                    int lg=0;

                    char sir[105];

                    consolex=17;
                    consoley+=25;
                    linesnr++;

                    for(int kms=1; kms<=nbfs; kms++)
                    {
                        sprintf(sir, "%d", afisbfs[kms]);

                        for(int i=0; i<strlen(sir); i++)
                        {
                            rand[lg++]=sir[i];
                            char nr[2];
                            nr[0]=sir[i];
                            nr[1]=0;
                            consolex+=15;
                            setbkcolor(DARKGRAY);
                            setcolor(WHITE);
                            outtextxy(consolex-15,consoley-17,nr);
                        }
                        rand[lg++]=' ';
                        consolex+=15;
                        char nr[2];
                        nr[0]=rand[lg-1];
                        nr[1]=0;
                        setbkcolor(DARKGRAY);
                        setcolor(WHITE);
                        outtextxy(consolex-15,consoley-17,nr);
                        if(consolex>175)
                        {
                            rand[lg]=0;
                            lg=0;
                            fprintf(fscroll,"%s",rand);
                            fputc(10,fscroll);
                            strcpy(rand,"");
                            consoley+=25;
                            consolex=17;
                            linesnr++;
                        }

                        setfillstyle(SOLID_FILL,DARKGRAY);
                        setcolor(WHITE);
                    }
                    rand[lg]=0;
                    fprintf(fscroll,"%s",rand);

                    fputc(10,fscroll);
                    break;
                }
            }
            fclose(fscroll);
        }

        if(butonas==9 && x>=225 && x<=1175 && y>=105 && y<=625)
        {
            fscroll = fopen( "scrlo", "a+" );
            nrc=0;
            for(int i = 1 ; i <= ct ; ++i)
            {
                ctc[i]=0;
                spm[i]=0;
                pm[i]=0;
            }
            for(int i = 1 ; i <= ct ; ++i)
                if(ctc[i] == 0)
                {
                    for(int j = 1; j <= ct ; ++j)
                        spm[j] = pm[j] = 0;
                    nrc ++;
                    df1(i);
                    df2(i);
                    for(int j = 1; j <= ct ; ++j)
                        if(spm[j] == 1 && pm[j] == 1)
                            ctc[j] = nrc;
                }


            char sir[105];

            consolex=17;
            consoley+=25;
            setbkcolor(COLOR(17,18,58));
            outtextxy(consolex-15, consoley-15,"nr. de comp. tare");
            fprintf(fscroll,"%s","nr. de comp. tare");
            linesnr++;
            fputc(10,fscroll);
            consolex=17;
            consoley+=25;
            outtextxy(consolex-15, consoley-15,"conexe este: ");
            fprintf(fscroll,"%s","conexe este: ");
            linesnr++;
            fputc(10,fscroll);
            consolex=17;
            consoley+=25;

            sprintf(sir, "%d", nrc);
            outtextxy(consolex-15,consoley-15,sir);
            consolex=17;
            consoley+=25;
            linesnr++;
            fprintf(fscroll,"%s",sir);
            fputc(10,fscroll);

            fclose(fscroll);
        }

        if(butonas==10 && x>=225 && x<=1175 && y>=105 && y<=625)
        {
            fscroll = fopen( "scrlo", "a+" );
            nrc=0;
            for(int i = 1 ; i <= ct ; ++i)
            {
                ctc[i]=0;
                spm[i]=0;
                pm[i]=0;
            }
            for(int i = 1 ; i <= ct ; ++i)
                if(ctc[i] == 0)
                {
                    for(int j = 1; j <= ct ; ++j)
                        spm[j] = pm[j] = 0;
                    nrc ++;
                    df1(i);
                    df2(i);
                    for(int j = 1; j <= ct ; ++j)
                        if(spm[j] == 1 && pm[j] == 1)
                            ctc[j] = nrc;
                }


            char sir[105];


            consolex=17;
            consoley+=25;
            setbkcolor(COLOR(17,19,58));
            outtextxy(consolex-15, consoley-15,"Componentele tare");
            fprintf(fscroll, "%s", "Componentele tare");
            fputc(10,fscroll);
            linesnr++;
            consolex=17;
            consoley+=25;
            outtextxy(consolex-15, consoley-15,"conexe sunt:");
            fprintf(fscroll,"%s","conexe sunt:");
            fputc(10,fscroll);
            linesnr++;
            consolex=17;
            consoley+=25;

            for(int i=1; i<=nrc; i++)
            {
                int lg=0;
                char rand[1005];
                for(int j=1; j<=ct; j++)
                    if(ctc[j]==i)
                    {
                        sprintf(sir, "%d", j);
                        for(int k=0; k<strlen(sir); k++)
                        {
                            rand[lg++]=sir[k];
                            char nr[2];
                            nr[0]=sir[k];
                            nr[1]=0;
                            consolex+=15;
                            setbkcolor(DARKGRAY);
                            setcolor(WHITE);
                            outtextxy(consolex-15,consoley-17,nr);
                        }
                        rand[lg++]=' ';
                        consolex+=15;
                        char nr[2];
                        nr[0]=rand[lg-1];
                        nr[1]=0;
                        setbkcolor(DARKGRAY);
                        setcolor(WHITE);
                        outtextxy(consolex-15,consoley-17,nr);
                        if(consolex>175)
                        {
                            rand[lg]=0;
                            lg=0;
                            fprintf(fscroll,"%s",rand);
                            fputc(10,fscroll);
                            strcpy(rand,"");
                            consoley+=25;
                            consolex=17;
                            linesnr++;
                        }
                        setfillstyle(SOLID_FILL,DARKGRAY);
                        setcolor(WHITE);
                    }
                rand[lg]=0;
                fprintf(fscroll,"%s",rand);
                linesnr++;
                fputc(10,fscroll);
                consolex=17;
                consoley+=25;

            }
            fclose(fscroll);
        }

        if(butonas==11 && x>=225 && x<=1175 && y>=105 && y<=625)
        {
            fscroll=fopen("scrlo","a+");
            consolex=17;
            consoley+=25;
            setbkcolor(COLOR(17,18,58));
            outtextxy(consolex-15, consoley-15,"Costurile Dijkstra: ");
            fprintf(fscroll,"%s","Costurile Dijkstra");
            fputc(10,fscroll);
            linesnr++;
            for(int j=1; j<=ct; j++)
            {

                if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R)
                {
                    int s=a[j].val,i;
                    for(int mor=1; mor<=ct; mor++)
                    {
                        for(int morj=1; morj<=ct; morj++)
                            MDAT[mor][morj]=MatriceAdiac[mor][morj];
                    }

                    for(int mor=1; mor<=ct; mor++)
                    {
                        for(int morj=1; morj<=ct; morj++)
                            if(MDAT[mor][morj]==0)
                                MDAT[mor][morj]=INFINIT;
                    }

                    for(int i =1 ; i <= ct ; i ++ )
                    {
                        f[i] = 0;
                        d[i] = MDAT[s][i];
                    }

                    f[s] = 1, d[s] = 0;
                    d[0] = INFINIT; // pentru determinarea nodului cu costul minim
                    for(int k = 1 ; k < ct ; ++k)
                    {
                        int pmax = 0;
                        for(int i = 1 ; i <= ct ; ++i)
                            if(f[i] == 0 && d[i] <= d[pmax])
                                pmax = i;

                        if(pmax > -1)
                        {
                            f[pmax] = 1;
                            for(i = 1; i <= ct ; ++i)
                                if(f[i] == 0 && d[i] > d[pmax] + MDAT[pmax][i])
                                    d[i] = d[pmax] + MDAT[pmax][i];
                        }
                    }


                    int m1,m2,nou;
                    char sir[105];
                    int k=0;

                    consolex=34;
                    consoley+=25;
                    for(int kms=1; kms<=ct; kms++)
                        if(kms!=j)
                        {
                            consolex=17;
                            consoley+=25;

                            setcolor(WHITE);
                            setbkcolor(COLOR(17,18,58));
                            sprintf(sir, "%d", kms);
                            setbkcolor(DARKGRAY);
                            outtextxy(consolex-15, consoley-15,sir);
                            fprintf(fscroll,"%s",sir);

                            setbkcolor(COLOR(17,19,58));
                            if(kms>=10) consolex+=15;
                            if(kms>=100) consolex+=15;
                            consolex+=15;

                            setbkcolor(DARKGRAY);
                            setcolor(WHITE);
                            outtextxy(consolex-15, consoley-15,":");
                            fprintf(fscroll,"%s",":");

                            setbkcolor(COLOR(17,19,58));

                            consolex+=15;

                            if(d[kms]<999999)
                            {
                                sprintf(sir, "%d", d[kms]);
                                setbkcolor(DARKGRAY);
                                setcolor(WHITE);

                                outtextxy(consolex-15, consoley-15,sir);
                                fprintf(fscroll,"%s",sir);
                                fputc(10,fscroll);
                            }
                            else

                            {
                                outtextxy(consolex-15, consoley-15,"nu are drum");
                                fprintf(fscroll,"%s","nu are drum");
                                fputc(10,fscroll);
                            }

                            linesnr++;

                            consolex=17;
                            consoley+=25;

                            int lgs;
                            lgs=strlen(sir);
                            while(lgs)
                            {
                                consolex+=15;
                                lgs--;
                            }
                            if(consolex>200)
                            {
                                consoley+=25;
                                consolex=17;
                            }

                            setfillstyle(SOLID_FILL,DARKGRAY);
                            setcolor(WHITE);
                        }

                    break;
                }

            }
            fclose(fscroll);
        }

        if(butonas==12 && x>=1270 && x<=1435 && y>=490 && y<=530)
        {
            int latime=15*(ct+2);
            if(latime<204) latime=204;
            int pag2=initwindow( latime, 25*(ct+2), "", 200, 105 );
            setbkcolor(COLOR(17,19,58));
            cleardevice();
            for(int i=1; i<=ct; i++)
                for(int j=1; j<=ct; j++)
                    cmat[j][i]=MatriceAdiac[i][j];


            char sir[105];



            int cy=34;
            int cx=34;

            for(int i=1; i<=ct; i++)
            {
                for(int j=1; j<=ct; j++)
                {
                    if(i==j) setcolor(YELLOW);
                    else setcolor(WHITE);
                    sprintf(sir, "%d", cmat[i][j]);

                    if(cmat[i][j]!=0)
                    {   setbkcolor(COLOR(17,19,58));
                        strcpy(sir,"1");
                        outtextxy(cx-15, cy-17,sir);
                        setbkcolor(COLOR(17,19,58));
                    }
                    else
                    {
                        setbkcolor(COLOR(17,19,58));
                        strcpy(sir,"0");
                        outtextxy(cx-15, cy-17,sir);
                        setbkcolor(COLOR(17,19,58));
                    }
                    int lgs;
                    lgs=strlen(sir);
                    while(lgs)
                    {
                        cx+=15;
                        lgs--;
                    }
                    if(consolex>200)
                    {
                        cy+=25;
                        cx=34;
                    }

                    setfillstyle(SOLID_FILL,DARKGRAY);
                    setcolor(WHITE);
                }
                cy+=25;
                cx=34;

            }
            char title[105]="Press any key to close me";
            outtextxy(17,getmaxy()-25,title);
            getch();
            closegraph(pag2);
            setcurrentwindow(pag1);

        }

        ///rectangle(1270, 490, 1435, 530);
        ///rectangle(1250, 140, 1450, 180);
        if(butonas==13 && x>=1250 && x<=1450 && y>=90 && y<=130)
        {
            int latime=15*(ct+2);
            if(latime<204) latime=204;
            int pag2=initwindow( latime, 25*(ct+2), "", 200, 105 );
            setbkcolor(COLOR(17,19,58));
            cleardevice();
            for(int i=1; i<=ct; i++)
                for(int j=1; j<=ct; j++)
                    cmat[j][i]=MatriceAdiac[i][j];


            char sir[105];


            int cy=34;
            int cx=34;

            for(int i=1; i<=ct; i++)
            {
                for(int j=1; j<=ct; j++)
                {

                    if(i==j) setcolor(YELLOW);
                    else setcolor(WHITE);
                    sprintf(sir, "%d", cmat[i][j]);
                    if(cmat[i][j]!=0)
                    {   setbkcolor(COLOR(17,19,58));
                        strcpy(sir,"1");
                        outtextxy(cx-15, cy-17,sir);
                        setbkcolor(COLOR(17,19,58));
                    }
                    else
                    {
                        setbkcolor(COLOR(17,19,58));
                        strcpy(sir,"0");
                        outtextxy(cx-15, cy-17,sir);
                        setbkcolor(COLOR(17,19,58));
                    }
                    int lgs;
                    lgs=strlen(sir);
                    while(lgs)
                    {
                        cx+=15;
                        lgs--;
                    }
                    if(consolex>200)
                    {
                        cy+=25;
                        cx=34;
                    }

                    setfillstyle(SOLID_FILL,DARKGRAY);
                    setcolor(WHITE);
                }
                cy+=25;
                cx=34;

            }
            char title[105]="Press any key to close me";
            outtextxy(17,getmaxy()-25,title);
            getch();
            closegraph(pag2);
            setcurrentwindow(pag1);

        }

        if (butonas==15 && x>=1250 && x<=1450 && y>=140 && y<=180)
        {   fscroll=fopen("scrlo","a+");
            int nrmxm;
            nrmxm=ct*(ct-1);

            char sir[105];


            setbkcolor(COLOR(17,19,58));
            consolex=17;
            consoley+=25;
            setcolor(WHITE);
            outtextxy(consolex-15, consoley-15,"Nr. max. arce:");
            fprintf(fscroll,"%s","Nr. max. arce:");
            fputc(10,fscroll);
            linesnr++;
            consolex=17;
            consoley+=25;

            sprintf(sir, "%d", nrmxm);
            outtextxy(consolex-15, consoley-15,sir);
            fprintf(fscroll,"%s",sir);
            fputc(10,fscroll);
            consolex=17;
            consoley+=25;
            linesnr++;
            fclose(fscroll);
        }
    }

}
