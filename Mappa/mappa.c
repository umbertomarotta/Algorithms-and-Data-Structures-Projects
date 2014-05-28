#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <assert.h>
#include <stdarg.h>

#include "mappa.h"
#include "citta.h"
#include "grafo.h"

#define DIM 1000

struct smappa{
    int Costo_Aereo;
    int Costo_Treno;
    int Costo_Pedaggio;
    int Costo_Benzina;
    int Vel_Aereo;
    int Vel_Treno;
    int Vel_Autostrade;
    int Vel_Strade;
    grafo Voli;
    grafo Ferrovie;
    grafo Autostrade;
    grafo Strade;
    int NumCitta;
    citta lista[DIM];
};
