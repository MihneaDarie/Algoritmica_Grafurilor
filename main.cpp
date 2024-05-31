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
using namespace std;

void meniuGrafN();
void meniuGrafO();

nod a[505];
muchie mx[505];

int xbutGN,ybutGN,xbutGO,ybutGO;
int ct,ctorder,R=20,MatriceAdiac[505][505],butonas, OptiuneComenziuwu=2, craiova;
int rx,ry=100;
int adaugcost;
int consolex=17,consoley=95,nrcautat=0, combm=0,nrmuchii,suntcosturi=0, stergeremuchii=0;
int stgcst;
int mmij[505][15];
int viz[500];
int page=0;
int eva,nrdfs, vectordfs[500], nrafisdfs;
int butondfs=0;
int bfsx[505], nbfs=1;
int vizbfs[505], bfst[505], afisbfs[505];
int tata[505], sumaprim=0;
int t[505];
int L[505], nrc;
int mE, vE[1000];
int cm[505][505];
int x1u, yu, xh[505], ok, ph[505];
int d[505], f[505];
int spm[505], pm[505], ctc[505];
int MDAT[505][505];
int cmat[505][505];
int linesnr=1;
int scroll=1;
int N,O;
int pag1;
int slider,speed;

char CaleSave[1005],CaleOpen[1005];

FILE* fscroll;
FILE* save;

void* image;
void* poza;

void resetmatrix(int a[505][505],int n)
{
    int i,j;
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
            a[i][j]=0;
}

void ClearPlayBN(int p)
{
    setfillstyle(SOLID_FILL,WHITE);
    bar(200,80,1200,650);

    int i,j;

    for(i=1; i<=ct; i++)
        for(j=1; j<=ct; j++)
            if(j>=i)
                if((MatriceAdiac[i][j]!=0 || MatriceAdiac[j][i]!=0) && i!=p && j!=p )
                {
                    setcolor(BLACK);
                    line(a[i].x,a[i].y,a[j].x,a[j].y);
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

    for(i=1; i<=ct; i++)
        if(i!=p)
        {
            setcolor(DARKGRAY);
            circle(a[i].x,a[i].y,R);
            setfillstyle(SOLID_FILL,COLOR(17,19,58));
            floodfill(a[i].x,a[i].y,DARKGRAY);
            setcolor(WHITE);
            setbkcolor(COLOR(17,19,58));
            char nr[5];
            sprintf(nr,"%d",i);
            if(ct>=100)  outtextxy(a[i].x-15, a[i].y-10,nr);
            else if(ct>=10) outtextxy(a[i].x-11, a[i].y-10,nr);
            else outtextxy(a[i].x-7, a[i].y-10,nr);
        }
    free(poza);
    poza=malloc(imagesize(0,0,getmaxx(),getmaxy()));
    getimage(0,0,getmaxx(),getmaxy(),poza);
}

void ClearPlayBO(int p)
{
    setfillstyle(SOLID_FILL,WHITE);
    bar(200,80,1200,650);

    int i,j;
    setbkcolor(COLOR(17,18,58));
    for(i=1; i<=ct; i++)
        for(j=i; j<=ct; j++)
            if(i!=j)
            {
                if(MatriceAdiac[i][j]!=0 && i!=p && j!=p && MatriceAdiac[j][i]==0)
                {
                    int calx1,caly1,calx2,caly2,mijx,mijy,drpy,drpx, mijlx, mijly;
                    double dist;
                    setcolor(BLACK);
                    if(max(a[i].x-a[j].x,a[j].x-a[i].x)>max(a[i].y-a[j].y,a[j].y-a[i].y))
                    {
                        calx2=((a[i].x+a[j].x)/2+((a[i].x+a[j].x)/2+ a[j].x))/2;
                        caly2=(((a[i].y+R-3+a[j].y+R-3)/2+((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))/2)/2+((a[i].y+R-3+a[j].y+R-3)))/2;
                        calx1=((((a[i].x+a[j].x)/2+a[j].x)))/2;
                        caly1=((((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))))/2;
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
                        caly2=(((a[i].y+a[j].y)/2+((a[i].y+a[j].y)/2+(a[j].y))))/2;
                        calx2=(((a[i].x+R-3+a[j].x+R-3)/2+((a[i].x+R-3+a[j].x+R-3)/2+ a[j].x+R-3)/2)/2+((a[i].x+R-3+a[j].x+R-3)))/2;
                        calx1=((((a[i].x+R-3+a[j].x+R-3)/2+(a[j].x+R-3))))/2;
                        caly1=((((a[i].y+a[j].y)/2+a[j].y)))/2;
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
                        if(max(a[i].x-a[j].x,a[j].x-a[i].x)>max(a[i].y-a[j].y,a[j].y-a[i].y))
                        {
                            if(MatriceAdiac[i][j]>0)
                                outtextxy((a[i].x+a[j].x)/2, (a[i].y+a[j].y)/2+R-6, nr);
                        }
                        else
                        {
                            if(MatriceAdiac[i][j]>0)
                                outtextxy((a[i].x+a[j].x)/2+R-6, (a[i].y+a[j].y)/2, nr);
                        }

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
                    if(max(a[i].x-a[j].x,a[j].x-a[i].x)>max(a[i].y-a[j].y,a[j].y-a[i].y))
                    {
                        calx2=((a[i].x+a[j].x)/2+((a[i].x+a[j].x)/2+ a[j].x))/2;
                        caly2=(((a[i].y+R-3+a[j].y+R-3)/2+((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))/2)/2+((a[i].y+R-3+a[j].y+R-3)))/2;
                        calx1=((((a[i].x+a[j].x)/2+a[j].x)))/2;
                        caly1=((((a[i].y+R-3+a[j].y+R-3)/2+(a[j].y+R-3))))/2;
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


                        swap(i,j);
                        setcolor(BLACK);
                        calx2=(((a[i].x+a[j].x)/2+((a[i].x+a[j].x)/2+ a[j].x)))/2;
                        caly2=(((a[i].y-R+3+a[j].y-R+3)/2+((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))))/2;
                        calx1=((((a[i].x+a[j].x)/2+ a[j].x)))/2;
                        caly1=((((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))))/2;
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


                        swap(i,j);
                    }
                    else
                    {
                        line(a[i].x+R-3,a[i].y,a[j].x+R-3,a[j].y);
                        line(a[i].x-R+3,a[i].y,a[j].x-R+3,a[j].y);
                        caly2=(((a[i].y+a[j].y)/2+((a[i].y+a[j].y)/2+(a[j].y))))/2;
                        calx2=(((a[i].x+R-3+a[j].x+R-3)/2+((a[i].x+R-3+a[j].x+R-3)/2+ a[j].x+R-3)/2)/2+((a[i].x+R-3+a[j].x+R-3)))/2;
                        calx1=((((a[i].x+R-3+a[j].x+R-3)/2+(a[j].x+R-3))))/2;
                        caly1=((((a[i].y+a[j].y)/2+a[j].y)))/2;
                        ///line(calx2, caly2, calx1, caly1);

                        drpy=((((a[i].y+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                        drpx=((((a[i].x+15*R-3+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                        line(calx1, caly1, drpx, drpy);
                        line(calx1, caly1, ((((a[i].x-10*R-3+calx1)/2+calx1)/2+calx1)/2+calx1)/2, drpy);

                        swap(i,j);
                        caly2=(((a[i].y+a[j].y)/2+((a[i].y+a[j].y)/2+(a[j].y))))/2;
                        calx2=(((a[i].x-R+3+a[j].x-R+3)/2+((a[i].x-R+3+a[j].x-R+3)/2+ a[j].x-R+3)/2))/2;
                        calx1=((((a[i].x-R+3+a[j].x-R+3)/2+(a[j].x-R+3))))/2;
                        caly1=((((a[i].y+a[j].y)/2+a[j].y)))/2;
                        ///line(calx2, caly2, calx1, caly1);

                        drpy=((((a[i].y+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                        drpx=((((a[i].x-15*R+3+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                        line(calx1, caly1, drpx, drpy);
                        line(calx1, caly1, ((((a[i].x+10*R+3+calx1)/2+calx1)/2+calx1)/2+calx1)/2, drpy);
                        swap(i,j);
                    }

                    if(suntcosturi==1)
                    {

                        setbkcolor(DARKGRAY);
                        setbkcolor(COLOR(17,19,58));

                        setfillstyle(SOLID_FILL,DARKGRAY);
                        setcolor(WHITE);

                        char nr[5];

                        sprintf(nr, "%d", MatriceAdiac[i][j]);
                        if(max(a[i].x-a[j].x,a[j].x-a[i].x)>max(a[i].y-a[j].y,a[j].y-a[i].y))
                        {
                            if(MatriceAdiac[i][j]>0)
                                outtextxy((a[i].x+a[j].x)/2, (a[i].y+a[j].y)/2+R-6, nr);
                        }
                        else
                        {
                            if(MatriceAdiac[i][j]>0)
                                outtextxy((a[i].x+a[j].x)/2+R-6, (a[i].y+a[j].y)/2, nr);
                        }


                        sprintf(nr, "%d", MatriceAdiac[j][i]);

                        if(max(a[i].x-a[j].x,a[j].x-a[i].x)>max(a[i].y-a[j].y,a[j].y-a[i].y))
                        {
                            if(MatriceAdiac[j][i]>0)
                                outtextxy((a[i].x+a[j].x)/2, (a[i].y+a[j].y)/2-R, nr);
                        }
                        else
                        {
                            if(MatriceAdiac[j][i]>0)
                                outtextxy((a[i].x+a[j].x)/2-R, (a[i].y+a[j].y)/2, nr);
                        }

                        setcolor(BLACK);
                        setfillstyle(SOLID_FILL,COLOR(17,19,58));
                        setcolor(WHITE);
                    }

                }
                else if(MatriceAdiac[i][j]==0 && i!=p && j!=p && MatriceAdiac[j][i]!=0)
                {
                    int calx1,caly1,calx2,caly2,mijx,mijy,drpy,drpx, mijlx, mijly;
                    double dist;
                    setcolor(BLACK);
                    if(max(a[i].x-a[j].x,a[j].x-a[i].x)>max(a[i].y-a[j].y,a[j].y-a[i].y))
                    {
                        swap(i,j);
                        line(a[i].x,a[i].y-R+3,a[j].x,a[j].y-R+3);
                        calx2=(((a[i].x+a[j].x)/2+((a[i].x+a[j].x)/2+ a[j].x)))/2;
                        caly2=(((a[i].y-R+3+a[j].y-R+3)/2+((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))))/2;
                        calx1=((((a[i].x+a[j].x)/2+ a[j].x)))/2;
                        caly1=((((a[i].y-R+3+a[j].y-R+3)/2+(a[j].y-R+3))))/2;
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


                        swap(i,j);
                    }
                    else
                    {
                        swap(i,j);
                        line(a[i].x-R+3,a[i].y,a[j].x-R+3,a[j].y);
                        caly2=(((a[i].y+a[j].y)/2+((a[i].y+a[j].y)/2+(a[j].y))))/2;
                        calx2=(((a[i].x-R+3+a[j].x-R+3)/2+((a[i].x-R+3+a[j].x-R+3)/2+ a[j].x-R+3)/2))/2;
                        calx1=((((a[i].x-R+3+a[j].x-R+3)/2+(a[j].x-R+3))))/2;
                        caly1=((((a[i].y+a[j].y)/2+a[j].y)))/2;
                        ///line(calx2, caly2, calx1, caly1);

                        drpy=((((a[i].y+caly1)/2+caly1)/2+caly1)/2+caly1)/2;
                        drpx=((((a[i].x-15*R+3+calx1)/2+calx1)/2+calx1)/2+calx1)/2;
                        line(calx1, caly1, drpx, drpy);
                        line(calx1, caly1, ((((a[i].x+10*R+3+calx1)/2+calx1)/2+calx1)/2+calx1)/2, drpy);
                        swap(i,j);
                    }

                    if(suntcosturi==1)
                    {

                        setbkcolor(DARKGRAY);
                        setbkcolor(COLOR(17,19,58));

                        setfillstyle(SOLID_FILL,DARKGRAY);
                        setcolor(WHITE);

                        char nr[5];

                        sprintf(nr, "%d", MatriceAdiac[j][i]);
                        if(max(a[i].x-a[j].x,a[j].x-a[i].x)>max(a[i].y-a[j].y,a[j].y-a[i].y))
                        {
                            if(MatriceAdiac[j][i]>0)
                                outtextxy((a[i].x+a[j].x)/2, (a[i].y+a[j].y)/2-R, nr);
                        }
                        else
                        {
                            if(MatriceAdiac[j][i]>0)
                                outtextxy((a[i].x+a[j].x)/2-R, (a[i].y+a[j].y)/2, nr);
                        }

                        setcolor(BLACK);
                        setfillstyle(SOLID_FILL,COLOR(17,19,58));
                        setcolor(WHITE);
                    }

                }

            }


    for(i=1; i<=ct; i++)
        if(i!=p)
        {
            setcolor(DARKGRAY);
            circle(a[i].x,a[i].y,R);
            setfillstyle(SOLID_FILL,COLOR(17,19,58));
            floodfill(a[i].x,a[i].y,DARKGRAY);

            setcolor(WHITE);
            char nr[5];
            sprintf(nr,"%d",i);
            if(ct>=100)  outtextxy(a[i].x-15, a[i].y-10,nr);
            else if(ct>=10) outtextxy(a[i].x-11, a[i].y-10,nr);
            else outtextxy(a[i].x-7, a[i].y-10,nr);
        }
    free(poza);
    poza=malloc(imagesize(0,0,getmaxx(),getmaxy()));
    getimage(0,0,getmaxx(),getmaxy(),poza);
}

void ClearSlider(int var)
{
    setfillstyle(SOLID_FILL,COLOR(17,19,58));
    setcolor(WHITE);///slider
    bar(1240, 610, 1465, 630);
    rectangle(1240, 610, 1465, 630);
    line(1250,620,1455,620);
    if(1260+var*10<1455)
    {
        setfillstyle(SOLID_FILL,YELLOW);
        bar(1250+var*10, 615, 1270+var*10, 625);
    }
}

int consx=17,consy=95;
///rectangle(0, 80, 200, 749);
void ClearConsole(int row)
{
    int i,j;
    char sir[1005];
    setfillstyle(SOLID_FILL,DARKGRAY);
    bar(0,80,200,749);
    setfillstyle(SOLID_FILL,YELLOW);
    bar(190,90+scroll*10,195,110+scroll*10);

    for(i=1; i<=linesnr; i++)
    {
        fgets(sir,1005,fscroll);
        if(i>=row)
        {
            if((sir[0]>='A' && sir[0]<='Z') || (sir[0]>='a' && sir[0]<='z'))
            {
                setcolor(WHITE);
                setbkcolor(COLOR(17,19,58));
                outtextxy(consx-15, consy-15,sir);
                setbkcolor(DARKGRAY);
            }
            else
                for(j=0; j<strlen(sir); j++)
                {
                    char str[2];
                    str[0]=sir[j];
                    str[1]=0;
                    setbkcolor(DARKGRAY);
                    outtextxy(consx-15, consy-15,str);
                    setbkcolor(COLOR(17,19,58));
                    consx+=15;

                }
            consy+=25;
            consx=17;
        }

    }
    consoley=consy-25;
}

void SaveFile(char Calesave[1005])
{
    int i,j;
    save= fopen(Calesave,"w");
    fclose(save);
    save=fopen(Calesave,"a+");

    fprintf(save,"%d", ct);
    fputc(10,save);


    for(i=1; i<=ct; i++)
    {
        for(j=1; j<=ct; j++)
        {
            fprintf(save,"%d",MatriceAdiac[i][j]);
            fputc(32,save);
        }
        fputc(10,save);
    }

    fputc(10,save);

    for(i=1; i<=ct; i++)
    {
        fprintf(save,"%d",a[i].x);
        fputc(32,save);
        fprintf(save,"%d",a[i].y);
        fputc(32,save);
        fprintf(save,"%d",a[i].val);
        fputc(10,save);
    }

    fclose(save);
}

void BuildSave(char CaleOpen[1005])
{
    int i,j;
    save=fopen(CaleOpen,"r");
    fscanf(save,"%d",&ct);
    for(i=1; i<=ct; i++)
        for(j=1; j<=ct; j++)
            fscanf(save,"%d",&MatriceAdiac[i][j]);
    for(i=1; i<=ct; i++)
    {
        fscanf(save,"%d",&a[i].x);
        fscanf(save,"%d",&a[i].y);
        fscanf(save,"%d",&a[i].val);
    }
    fclose(save);
}


void saveFilePath()
{
    OPENFILENAME fila;
    char szFileName[1005] = "";

    ZeroMemory(&fila, sizeof(fila));
    fila.lStructSize = sizeof(fila);
    fila.hwndOwner = NULL;
    fila.lpstrFilter = "All Files (*.*)\0*.*\0";
    fila.lpstrFile = szFileName;
    fila.nMaxFile = 1005;
    fila.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;

    if (GetSaveFileName(&fila))
        strcpy(CaleSave,szFileName);
}

void openFile()
{
    OPENFILENAME fila;
    char szFileName[1005] = "";

    ZeroMemory(&fila, sizeof(fila));
    fila.lStructSize = sizeof(fila);
    fila.hwndOwner = NULL;
    fila.lpstrFilter = "All Files (*.*)\0*.*\0";
    fila.lpstrFile = szFileName;
    fila.nMaxFile = 1005;
    fila.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

    if (GetOpenFileName(&fila))
        strcpy(CaleOpen,szFileName);

}

int main()
{
    pag1=initwindow(1500,750,"Algoritmica Grafurilor");
    setbkcolor(COLOR(17,19,58));
    setactivepage(0);
    setvisualpage(0);
    setlinestyle(0,0,2);
    MainMenu();
    closegraph();
    return 0;
}
