/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, bl33h, MelissaPerez09, FabianJuarez182, SebasJuarez
@author Sara Echeverria, Melissa Perez, Fabian Juarez, Sebastian Juarez
FileName: machineVShuman
@version: III
Creation: 06/10/2022
Last modification: 10/10/2022
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

// Variables
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
int piezasPMin;
pthread_mutex_t mutex;

// --- Estructura con la informacion de la empresa ---
struct datosEmpresa
{
    pthread_t thread;
    int contador;
};

// --- Estructura con la informacion del empleado ---
struct datosEmpleado
{
    pthread_t thread;
    int contador;
};

// --- Estructura con la informacion de los costos ---
struct costo{
    pthread_t thread;
    int costoFijoEnergia;
    int costoFijoAgua;
    int costoFijoMateriaPrima;
    int costoVariable;  
};

// --- Metodo costos ---
void* costoProduccion(void *arg)
{
    costo *costos;
    costos = (costo*)arg;
    int costoFijoTotal = (costos -> costoFijoEnergia) + (costos -> costoFijoAgua) + (costos-> costoFijoMateriaPrima);
    int costoVariable = (cantPiezas/piezasPMin) * 2; // Valor fijo
    int costoTotal = costoFijoTotal + costoVariable;
}

// --- Metodo produccion por parte del personal humano ---
void* procesoPersonal(void *arg)
{

}

// --- Metodo produccion por parte de la maquina ---
void* procesoMaquina(void *arg)
{
       
}

// --- Main ---
int main(){
    cout << "- B I E N V E N I D O -";
    cout << "\nFinalidad de su empresa: ";
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