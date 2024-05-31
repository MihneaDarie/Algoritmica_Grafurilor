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

int maximul(int a,int b)
{   if(a>b) return a;
    return b;
}

void swape(int &a, int &b)
{   int aux;
    aux=a;
    a=b;
    b=aux;
}
