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
int cantProcesos;
/* meter esta en el main por la cantidad de Personal int tiempoEjecucion[cantidadPersonal];*/
int inversionMaquina;
int salarioPersonal;
int cantidadPersonal;
int presupuesto;
int proyeccion;
int cantPiezas;
int ensamblajeMaquina;
int piezasPMin
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

int main(){
    cout << "- B I E N V E N I D O -";
    cout << "\nTipo de trabajo que va a realizar: ";
    cin >> tipoTrabajo;
    cout << "Cantidad de procesos a realizar: ";
    cin >> cantProcesos;
    cout << "Piezas por minuto: ";
    cin >> piezasPMin;
    cout << "Cantidad de piezas totales a producir: ";
    cin >> cantPiezas;
    cout << "Cantidad de personal: ";
    cin >> cantidadPersonal;
    cout << "Salario del personal: ";
    cin >> salarioPersonal;
    cout << "Inversion de la maquina: ";
    cin >> inversionMaquina;
    cout << "Presupuesto inicial: ";
    cin >> presupuesto;


    cout << "Inicializando los procesos...";
}

void* costoProduccion(void *arg){
    costo *x;
    x = (costo*)arg;
    int costoFijoTotal = (x-> costoFijoEnergia) + (x -> costoFijoAgua) + (x-> costoFijoMateriaPrima);

    int costoVariable = (cantPiezas/piezasPMin) * 2;

    int costoTotal = costoFijoTotal + costoVariable;

}