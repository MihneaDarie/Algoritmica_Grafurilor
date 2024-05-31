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

void GNButtons() /// aceasta functie inregistreaza toate apasaturile de mouse si toate butoanele posibile de pe o pagina cu GO
{
    setactivepage(0);
    int x,y,j;

    int x1,y1,mem1;
    int x2,y2;

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
            ClearPlayBN(0);
            setactivepage(1);
            putimage(0,0,poza,0);
            setvisualpage(0);
            POINT poz;
            while(1)
            {
                setactivepage(page);
                setvisualpage(1-page);
                ClearPlayBN(mem1);

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

                    for(int i=1; i<=ct; i++)
                        if(MatriceAdiac[i][mem1] || MatriceAdiac[mem1][i])
                            line(poz.x,poz.y,a[i].x,a[i].y);


                    for(j=1;j<=ct;j++)
                        if(MatriceAdiac[mem1][j]!=0 && suntcosturi )
                         {   char s[105];
                             setcolor(WHITE);
                             setbkcolor(COLOR(17,19,58));
                             sprintf(s,"%d",MatriceAdiac[mem1][j]);
                             outtextxy((poz.x+a[j].x)/2,(poz.y+a[j].y)/2,s);

                         }

                }

                if(ismouseclick(WM_LBUTTONDOWN))
                {
                    if(poz.x>=225 && poz.x<=1175 && poz.y>=105 && poz.y<=625 )
                    {
                        a[mem1].x=poz.x;
                        a[mem1].y=poz.y;
                    }
                    butonas=0;
                    break;
                }
                page=1-page;

            }///x>=225 && x<=1175 && y>=105 && y<=625

        }
        setactivepage(0);
        setvisualpage(0);
        ClearPlayBN(0);
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
            meniuGrafN();
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
            ClearPlayBN(0);
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

         if(x>=0 && x<=200 && y>=80 && y<=749)
            ctorder++;

        if(x>=1313 && x<=1478 && y>=710 && y<=735)///activare buton stergere cost
            if(butonas!=6)
            {   ClearPlayBN(0);
                butonas=6;

            }

        if(x>=1310 && x<=1385 && y>=190 && y<=230)
         {   ClearPlayBN(0);
             if(butonas!=7) ///BUTONUL DE DFS
            {
                butonas=7;

            }
         }
        ///rectangle(1310, 250, 1385, 290);
        if(x>=1310 && x<=1385 && y>=250 && y<=290)
           {ClearPlayBN(0);
               if(butonas!=8)
            {
                butonas=8;
            }

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
                fscroll=fopen("scrlo","a+");
                butonas=11;
                consolex=17;
                consoley+=25;
                setcolor(WHITE);
                setbkcolor(COLOR(17,19,58));
                linesnr++;
                fprintf(fscroll,"%s","Apasa pe un nod");
                fputc(10,fscroll);
                outtextxy(consolex-15, consoley-15,"Apasa pe un nod");
                butonas=11;
                consolex=17;
                consoley+=25;
                setcolor(WHITE);
                setbkcolor(COLOR(17,19,58));
                linesnr++;
                fprintf(fscroll,"%s","de grad impar");
                fputc(10,fscroll);
                outtextxy(consolex-15, consoley-15,"de grad impar");
                fclose(fscroll);

            }

        ///rectangle(1310, 490, 1390, 530);
        if(x>=1310 && x<=1390 && y>=490 && y<=530)
            if(butonas!=12)
            {
                butonas=12;

            }

        ///rectangle(1280, 550, 1425, 590);
        if(x>=1280 && x<=1425 && y>=550 && y<=590)
            if(butonas!=13)
            {
                butonas=13;

            }
        ///rectangle(1250, 90, 1450, 130);
        if(x>=1250 && x<=1450 && y>=90 && y<=130)
            if(butonas!=14)
            {
                butonas=14;

            }

        if (x>=1250 && x<=1450 && y>=140 && y<=180)
            if(butonas!=15)
            {
                butonas=15;
            }

        ///if(ctorder==66)
        ///{   PlaySound("Execute Order 66.wav",NULL,SND_ASYNC);
        ///}

        ///aici las restul de butonase

        if(OptiuneComenziuwu==2)
        {
            ///1
            if(x>=225 && x<=1175 && y>=105 && y<=625 && butonas==3)
            {
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
                    ClearPlayBN(0);
                    setactivepage(1);
                    putimage(0,0,poza,0);
                    setvisualpage(0);
                    POINT poz;
                    while(1)
                    {
                        setactivepage(page);
                        setvisualpage(1-page);
                        ClearPlayBN(0);
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
                            if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R && x1!=x && y1!=y && MatriceAdiac[j][mem1]==0 && MatriceAdiac[mem1][j]==0)
                            {
                                x2=a[j].x;
                                y2=a[j].y;
                                setcolor(WHITE);
                                line(x1,y1,poz.x,poz.y);
                                setcolor(BLACK);
                                line(x1,y1,x2,y2);
                                setcolor(WHITE);

                                setcolor(DARKGRAY);
                                circle(x2,y2,R);
                                setfillstyle(SOLID_FILL,COLOR(17,19,58));
                                floodfill(x2,y2,DARKGRAY);
                                circle(x1,y1,R);
                                floodfill(x1,y1,DARKGRAY);
                                if(mem1<=ct && j<=ct )
                                {
                                    MatriceAdiac[mem1][j]=1;
                                    MatriceAdiac[j][mem1]=1;
                                    mmij[++nrmuchii][1]=a[mem1].val;
                                    mmij[nrmuchii][2]=a[j].val;
                                    mmij[nrmuchii][3]=(x1+x2)/2;
                                    mmij[nrmuchii][4]=(y1+y2)/2;
                                    mmij[nrmuchii][5]=((x1+x2)/2+x1)/2;
                                    mmij[nrmuchii][6]=((y1+y2)/2+y1)/2;
                                    mmij[nrmuchii][7]=((x1+x2)/2+x2)/2;
                                    mmij[nrmuchii][8]=((y1+y2)/2+y2)/2;

                                    mx[nrmuchii].i=mem1;
                                    mx[nrmuchii].j=j;
                                    mx[nrmuchii].cost=1;

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
                                break;
                            }
                            else
                                ClearPlayBN(0);
                        setactivepage(0);
                        setvisualpage(0);
                        ClearPlayBN(0);
                    }

                }

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
                            MatriceAdiac[j][mem1]=0;
                            stergeremuchii=0;

                            for(int sm=1; sm<nrmuchii; sm++)
                            {
                                if(mx[sm].i==mem1 && mx[sm].j==j)
                                    for(int smp=sm; smp<=nrmuchii; smp++)
                                    {
                                        mx[smp].i=mx[smp+1].i;
                                        mx[smp].j=mx[smp+1].j;
                                        mx[smp].cost=mx[smp+1].cost;
                                    }
                                else if(mx[sm].i==j && mx[sm].j==mem1)
                                    for(int smp=sm; smp<=nrmuchii; smp++)
                                    {
                                        mx[smp].i=mx[smp+1].i;
                                        mx[smp].j=mx[smp+1].j;
                                        mx[smp].cost=mx[smp+1].cost;
                                    }
                            }

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
                            ClearPlayBN(0);
                            break;
                        }
                }
            }

            ///1

        }

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
                        MatriceAdiac[m2][m1]=0;
                        setcolor(WHITE);
                        line(a[m1].x,a[m1].y,a[m2].x,a[m2].y);
                        setcolor(COLOR(17,19,58));
                        setcolor(DARKGRAY);
                        circle(a[m1].x,a[m1].y,R);
                        setfillstyle(SOLID_FILL,COLOR(17,19,58));
                        floodfill(a[m1].x,a[m1].y,DARKGRAY);
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
                        floodfill(a[m2].x,a[m2].y,DARKGRAY);

                        setcolor(WHITE);
                        sprintf(nr,"%d",m2);
                        if(ct>=100)  outtextxy(a[m2].x-15, a[m2].y-10,nr);
                        else if(ct>=10) outtextxy(a[m2].x-11, a[m2].y-10,nr);
                        else outtextxy(a[m2].x-7, a[m2].y-10,nr);

                        for(int sm=1; sm<nrmuchii; sm++)
                        {
                            if(mx[sm].i==mem1 && mx[sm].j==j)
                                for(int smp=sm; smp<=nrmuchii; smp++)
                                {
                                    mx[smp].i=mx[smp+1].i;
                                    mx[smp].j=mx[smp+1].j;
                                    mx[smp].cost=mx[smp+1].cost;
                                }
                            else if(mx[sm].i==j && mx[sm].j==mem1)
                                for(int smp=sm; smp<=nrmuchii; smp++)
                                {
                                    mx[smp].i=mx[smp+1].i;
                                    mx[smp].j=mx[smp+1].j;
                                    mx[smp].cost=mx[smp+1].cost;
                                }
                        }
                        nrmuchii--;
                    }
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
                        MatriceAdiac[m2][m1]=1;
                        setcolor(COLOR(17,19,58));
                        line(a[m1].x,a[m1].y,a[m2].x,a[m2].y);
                        setcolor(WHITE);

                        nrmuchii++;
                        mx[nrmuchii].i=m1;
                        mx[nrmuchii].j=m2;
                        mx[nrmuchii].cost=1;
                    }
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

                    ClearPlayBN(nodsters);
                }
            }

            ClearPlayBN(0);
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

                            outtextxy((a[mem1].x+a[j].x)/2, (a[mem1].y+a[j].y)/2, " ");
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
                                        outtextxy((a[mem1].x+a[j].x)/2, (a[mem1].y+a[j].y)/2, sir);
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
                                MatriceAdiac[j][mem1]=nou;
                                for(int idck=1; idck<=nrmuchii; idck++)
                                    if((mx[idck].i==mem1 && mx[idck].j==j) || (mx[idck].i==j && mx[idck].j==mem1))
                                    mx[idck].cost=nou;
                                suntcosturi=1;
                                if(m1==0 && m2==0) m1=nou;
                                else if(m2==0) m2=nou;
                                p=strtok(0,sep);
                            }

                            ClearPlayBN(0);
                            adaugcost=0;
                            break;
                        }
                }
                ClearPlayBN(0);
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
                        MatriceAdiac[j][mem1]=1;
                        for(int idck=1; idck<=nrmuchii; idck++)
                                    if((mx[idck].i==mem1 && mx[idck].j==j) || (mx[idck].i==j && mx[idck].j==mem1))
                                    mx[idck].cost=1;
                        ClearPlayBN(0);
                        stgcst=0;
                        break;
                    }
            }
            ClearPlayBN(0);
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

                    consolex=0;
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

        if(butonas==9 && x>=225 && x<=1175 && y>=105 && y<=625) ///conexitate
        {
            fscroll=fopen("scrlo", "a+");
            int econex=1;
            nrdfs=0;
            for(int kms=0; kms<=500; kms++)
                viz[kms]=0;
            dfs2(1, vectordfs);

            for(int sendhelp=1; sendhelp<=ct; sendhelp++)
                if(viz[sendhelp]==0)
                    econex=0;
            if(ct==0)
            {
                consolex=17;
                consoley+=25;
                setcolor(WHITE);
                setbkcolor(COLOR(17,19,58));
                outtextxy(consolex-15, consoley-25,"Nu exista graf");
                fprintf(fscroll,"%s","Nu exista graf");
                fputc(10,fscroll);
                linesnr++;
            }
            else
            {
                if(econex==1)
                {
                    consolex=17;
                    consoley+=25;
                    setcolor(WHITE);
                    setbkcolor(COLOR(17,19,58));
                    outtextxy(consolex-15, consoley-25,"Graful e conex");
                    fprintf(fscroll,"%s","Graful e conex");
                    fputc(10,fscroll);
                    linesnr++;
                }
                else
                {
                    consolex=17;
                    consoley+=25;
                    setcolor(WHITE);
                    setbkcolor(COLOR(17,19,58));
                    outtextxy(consolex-15, consoley-15,"Graful nu e conex");
                    fprintf(fscroll,"%s","Graful nu e conex");
                    fputc(10,fscroll);
                    linesnr++;
                }
            }
            fclose(fscroll);
        }

        if(butonas==10 && x>=225 && x<=1175 && y>=105 && y<=625)
        {
            fscroll=fopen("scrlo","a+");
            nrc=0;
            char sir[505];
            for(int j=1; j<=ct; j++)
                L[j]=0, viz[j]=0, vectordfs[j]=0;

            for(int i=1; i<=ct; i++)
                if(L[i]==0)
                {
                    nrc++;
                    dfs2(i, vectordfs);
                }

            consolex=20;
            consoley+=25;
            linesnr++;
            setcolor(WHITE);
            setbkcolor(COLOR(17,19,58));
            fprintf(fscroll,"%s","Nr. comp. conexe: ");
            fputc(10,fscroll);
            outtextxy(consolex-17, consoley-25,"Nr. comp. conexe: ");
            consolex=17;
            consoley+=25;
            sprintf(sir, "%d", nrc);
            linesnr++;
            fprintf(fscroll,"%s",sir);
            fputc(10,fscroll);
            outtextxy(consolex-15, consoley-25,sir);
            consolex=17;
            consoley+=25;
            linesnr++;
            fprintf(fscroll,"%s","Iar acestea sunt:");
            fputc(10,fscroll);
            outtextxy(consolex-15, consoley-25,"Iar acestea sunt:");

            consolex=17;
            consoley+=25;



            for(int kms=1; kms<=nrc; kms++)
            {
                int lg=0;
                char rand[1005];
                for(int j=1; j<=ct; j++)
                    if(L[j]==kms)
                    {
                        sprintf(sir, "%d", j);
                        for(int i=0; i<strlen(sir); i++)
                        {
                            rand[lg++]=sir[i];
                            char nr[2];
                            nr[0]=sir[i];
                            nr[1]=0;
                            consolex+=15;
                            setbkcolor(DARKGRAY);
                            setcolor(WHITE);
                            outtextxy(consolex-15,consoley-25,nr);
                        }
                        rand[lg++]=' ';
                        consolex+=15;
                        char nr[2];
                        nr[0]=rand[lg-1];
                        nr[1]=0;
                        setbkcolor(DARKGRAY);
                        setcolor(WHITE);
                        outtextxy(consolex-15,consoley-25,nr);
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
                linesnr++;
                consoley+=25;
                consolex=17;
            }
            fclose(fscroll);
        }

        if(butonas==11 && x>=225 && x<=1175 && y>=105 && y<=625)
        {
            fscroll=fopen("scrlo","a+");
            for(int j=1; j<=ct; j++)
                if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R)
                {
                    mE=0;

                    for(int i=1; i<=ct; i++)
                        for(int l=1; l<=ct; l++)
                            cm[i][l]=MatriceAdiac[i][l];

                    Euler(a[j].val);

                    for(int i=1; i<=ct; i++)
                        for(int l=1; l<=ct; l++)
                            MatriceAdiac[i][l]=cm[i][l];

                    char sir[505];
                    consolex=17;
                    consoley+=25;
                    linesnr++;
                    fprintf(fscroll,"%s","Lantul Euler: ");
                    fputc(10,fscroll);
                    outtextxy(consolex-15, consoley-15,"Lantul Euler: ");
                    consolex=17;
                    consoley+=25;
                    int lg=0;
                    char rand[1005];
                    for(int kms=1; kms<=mE; kms++)
                    {
                        sprintf(sir, "%d", vE[kms]);
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
                    linesnr++;
                    rand[lg]=0;
                    fprintf(fscroll,"%s",rand);
                    fputc(10,fscroll);
                    break;
                }
            fclose(fscroll);
        }

        if(butonas==12 && x>=225 && x<=1175 && y>=105 && y<=625)
        {
            fscroll=fopen("scrlo","a+");
            sumaprim=0;
            for(int j=1; j<=ct; j++)
            {
                if(x<=a[j].x+R && x>=a[j].x-R && y<=a[j].y+R && y>=a[j].y-R)
                {
                    int acelprim;
                    for (int i=1; i<=ct; i++)
                        viz[i]=0;
                    acelprim=a[j].val;
                    Prim(a[j].val);
                    break;
                }
            }

            char sir[105],rand[1005],lg=0;
            int k=0;

            setbkcolor(COLOR(17,19,58));
            consolex=17;
            consoley+=25;
            outtextxy(consolex-15, consoley-15,"Cost Prim: ");
            fprintf(fscroll,"%s","Cost Prim: ");
            fputc(10,fscroll);
            linesnr++;
            consolex=17;
            consoley+=25;
            sprintf(sir, "%d", sumaprim);

            fprintf(fscroll,"%s",sir);
            outtextxy(consolex-15,consoley-15,sir);
            linesnr++;

            fputc(10,fscroll);
            setfillstyle(SOLID_FILL,DARKGRAY);
            setcolor(WHITE);
            fclose(fscroll);
        }

        if(butonas==13 && x>=225 && x<=1175 && y>=105 && y<=625)
        {
            fscroll=fopen("scrlo","a+");
            for(int i=1; i<nrmuchii; i++)
                for(int j=i+1; j<=nrmuchii; j++)
                    if(mx[i].cost>mx[j].cost)
                    {
                        muchie aux;
                        aux=mx[i];
                        mx[i]=mx[j];
                        mx[j]=aux;
                    }

            for(int i =1 ; i <= ct ; ++i)
                t[i] = i;

            ///determinare Aarbore Partial de cost Minim
            int S = 0;
            for(int i = 1 ; i <= nrmuchii ; i ++)
                if(t[mx[i].i] != t[mx[i].j]) ///extremitatile fac parte din subrabori diferiti
                {
                    S += mx[i].cost;
                    ///reunim subarborii
                    int ai = t[mx[i].i], aj = t[mx[i].j];
                    for(int j =1 ; j <= ct ; ++j)
                        if(t[j] == aj)
                            t[j] = ai;
                }

            char sir[105],rand[1005],lg=0;

            setbkcolor(COLOR(17,19,58));
            consolex=17;
            consoley+=25;
            setcolor(WHITE);
            outtextxy(consolex-15, consoley-15,"Cost Kruskal: ");
            fprintf(fscroll,"%s","Cost Kruskal: ");
            fputc(10,fscroll);
            linesnr++;
            consolex=17;
            consoley+=25;

            sprintf(sir, "%d", S);

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
            setbkcolor(DARKGRAY);
            setcolor(WHITE);
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
            linesnr++;
            rand[lg]=0;
            fprintf(fscroll,"%s",rand);
            fputc(10,fscroll);
            setfillstyle(SOLID_FILL,DARKGRAY);
            setcolor(WHITE);
            fclose(fscroll);
        }

        ///rectangle(1250, 90, 1450, 130);
        if(butonas==14 && x>=1250 && x<=1450 && y>=90 && y<=130)
        {
            int latime=15*(ct+2);
            if(latime<204) latime=204;
            int pag2=initwindow( latime, 25*(ct+2), "", 200, 105 );
            setbkcolor(COLOR(17,19,58));
            cleardevice();


            char sir[105];


            int cy=34;
            int cx=34;

            for(int i=1; i<=ct; i++)
            {
                for(int j=1; j<=ct; j++)
                {
                    if(i==j) setcolor(YELLOW);
                    else setcolor(WHITE);
                    sprintf(sir, "%d", MatriceAdiac[i][j]);
                    if(MatriceAdiac[i][j]!=0)
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

        ///rectangle(1250, 140, 1450, 180);
        if (butonas==15 && x>=1250 && x<=1450 && y>=140 && y<=180)
        {
            fscroll=fopen("scrlo","a+");
            int nrmxm;
            nrmxm=ct*(ct-1)/2;

            setbkcolor(COLOR(17,19,58));
            consolex=17;
            consoley+=25;
            setcolor(WHITE);
            outtextxy(consolex-15, consoley-15,"Nr. max. muchii:");
            fprintf(fscroll,"%s","Nr. max. muchii:");
            fputc(10,fscroll);
            linesnr++;
            consolex=17;
            consoley+=25;

            char sir[105];
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
