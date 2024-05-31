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

void MainButtons() /// aceasta funtie inregistreaza fiecare apasatura de mouse si toate butoanele posibile de pe pagina main
{
    int x,y;
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();
        if(x>=548 && x<=950 && y>=269 && y<=337)
            Materie();
        if(x>=xbutGN-500 && x<=xbutGN-150 && y>=ybutGN+100 && ybutGN+200)
            meniuGrafN();
        if(x>=xbutGO+150 && x<=xbutGO+500 && y>=ybutGO+100 && y<=ybutGO+200)
            meniuGrafO();
    }
}
