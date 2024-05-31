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

void dfs(int k, int vectordfs[])
{
    nrdfs++;
    vectordfs[nrdfs]=k;
    if(ct!=0)
    {setlinestyle(0,0,5);
    setcolor(YELLOW);
    circle(a[k].x,a[k].y,R);
    setlinestyle(0,0,2);
    }
    viz[k]=1; //vizitam varful curent x
    L[k]=nrc;
    for(int i=1; i<=ct; i++) // determinam vecinii nevizitati ai lui x
        if(MatriceAdiac[k][i]!=0 && viz[i]==0)
        {
            delay(1050-speed);
            dfs(i, vectordfs); // continuam parcurgerea cu vecinul curent i
        }
}

void dfs2(int k, int vectordfs[])
{
    nrdfs++;
    vectordfs[nrdfs]=k;
    viz[k]=1; //vizitam varful curent x
    L[k]=nrc;
    for(int i=1; i<=ct; i++) // determinam vecinii nevizitati ai lui x
        if(MatriceAdiac[k][i]!=0 && viz[i]==0)
        {
            dfs2(i, vectordfs); // continuam parcurgerea cu vecinul curent i
        }
}

void Euler(int k)
{
    for(int i = 1 ; i <= ct ; i ++)
        if(MatriceAdiac[k][i] != 0)
        {
            MatriceAdiac[k][i] = MatriceAdiac[i][k] = 0;
            Euler(i);
        }
    vE[++mE] = k;
}

void bfs(int start, int bfst[])
{
    int i,k,st,dr;
    //initializez coada
    st=dr=1;
    bfsx[1]=start;
    vizbfs[start]=1;//vizitez varful initial
    setlinestyle(0,0,5);
    setcolor(YELLOW);
    circle(a[start].x,a[start].y,R);
    setlinestyle(0,0,2);
    while(st<=dr)//cat timp coada nu este vida
    {
        k=bfsx[st];//preiau un element din coada
        bfst[k]=st;
        setlinestyle(0,0,5);
        setcolor(YELLOW);
        circle(a[k].x,a[k].y,R);
        setlinestyle(0,0,2);
        for(i=1; i<=ct; i++) //parcurg varfurile
            if(vizbfs[i]==0 && MatriceAdiac[k][i]!=0)//daca i este vecin cu k si nu este vizitat
            {
                vizbfs[i]=1;//il vizitez
                afisbfs[++nbfs]=i;
                bfsx[++dr]=i;//il adaug in coada
                setlinestyle(0,0,5);
                setcolor(YELLOW);
                circle(a[k].x,a[k].y,R);
                setlinestyle(0,0,2);
                delay(1050-speed);
            }
        st++;
    }
}

void Prim(int nod_start)
{
    int i,p,minis,k;

    viz[nod_start]=1; //marcam nodul de start vizitat
    for(i=1; i<=ct; i++)
        tata[i]=nod_start;
    tata[nod_start]=0;// initializam vectorul de tati

    for(k=1; k<=ct-1; k++)
    {
        minis=999999; //minimul este initializat cu infinit
        p=0;
        for(i=1; i<=ct; i++)
        {

            if(viz[i]==0 && MatriceAdiac[i][tata[i]]<minis && MatriceAdiac[i][tata[i]]!=0) //cautam un nod nevizitat si il comparam cu minimul
            {
                minis=MatriceAdiac[i][tata[i]];
                p=i;//retinem nodul in variabila p
            }
            viz[p]=1; //il marcam vizitat la sfarsit
        }

        for(i=1; i<=ct; i++)
            if(viz[i]==0 && ((MatriceAdiac[i][tata[i]]>MatriceAdiac[i][p] && MatriceAdiac[i][p]!=0) || (MatriceAdiac[i][tata[i]]==0 && MatriceAdiac[i][p]!=0)))
                tata[i]=p;
    }
    for(i=1; i<=ct; i++)
        sumaprim+=MatriceAdiac[i][tata[i]];

}

void df1(int n)
{
    spm[n] = 1;
    for(int i =1 ; i <= ct ; i ++)
        if(spm[i] == 0 && MatriceAdiac[n][i] != 0)
            df1(i);
}

void df2(int n)
{
    pm[n] = 1;
    for(int i =1 ; i <= ct ; i ++)
        if(pm[i] == 0 && MatriceAdiac[i][n] != 0)
            df2(i);
}
