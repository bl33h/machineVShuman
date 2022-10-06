/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, bl33h, MelissaPerez09, FabianJuarez182, SebasJuarez
@author Sara Echeverria, Melissa Perez, Fabian Juarez, Sebastian Juarez
FileName: machineVShuman
@version: II
Creation: 06/10/2022
Last modification: 06/10/2022
----------------------------------------------------------------------------------------------------
* Descripción: 
* Establecer la eficiencia y rentabilidad a largo plazo de la producción de una 
* máquina en comparación a la que el personal humano realizaría.
-----------------------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
using namespace std;
string tipoTrabajo;
/* meter esta en el main por la cantidad de Personal int tiempoEjecucion[cantidadPersonal];*/
int salarioOperadores;
int salarioAyudantes;
int cantidadPersonal;
int presupuesto;
int proyeccion;
int cantPiezas;
int ensamblajeMaquina;
pthread_mutex_t mutex;

struct datosEmpresa
{
    pthread_t thread;
    int contador;
};
struct datosEmpleado
{
    pthread_t thread;
    int contador;
};
struct costo{
    pthread_t thread;
    int costoFijoEnergia;
    int costoFijoAgua;
    int costoFijoMateriaPrima;
    int costoVariable;  
};