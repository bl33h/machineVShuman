/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, bl33h, MelissaPerez09, FabianJuarez182, SebasJuarez
@author Sara Echeverria, Melissa Perez, Fabian Juarez, Sebastian Juarez
FileName: machineVShuman
@version: V
Creation: 06/10/2022
Last modification: 10/10/2022
----------------------------------------------------------------------------------------------------
* Descripcion: 
* Establecer la eficiencia y rentabilidad a largo plazo de la produccion de una 
* máquina en comparacion a la que el personal humano realizaria.
-----------------------------------------------------------------*/

// Librerias
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
int cantidadPersonal;
int cantidadOperadores;
int salarioPersonal;
int cantidadOperadores;
int salarioOperadores;
int presupuesto;
int proyeccion;
int cantPiezas;
int ensamblajeMaquina;
int piezasPMin;
pthread_mutex_t mutex;

// --- Estructura con la informacion de la produccion ---
struct datosProduccion
{
    int cantProcesos = 0;
    int cantPiezas = 0;
};

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
void* procesoPersonal(void *piezas)
{
   datosProduccion *produccionStructure = (datosProduccion*) piezas; // *Structure call
    // *Mutex lock*
    pthread_mutex_lock(&lock);
    cout<<"El proceso No."<< contador << ", realizado por el personal humano, ha producido 1 pieza." <<endl;
    produccionStructure->cantPiezas += 1;
    // *Mutex Unlock*
    pthread_mutex_unlock(&lock);
    pthread_mutex_destroy(&lock);
    return NULL;
}

// --- Metodo produccion por parte de la maquina ---
void* procesoMaquina(void *arg)
{

}

// --- Main ---
int main()
{
    // Inputs
    cout << "--- B I E N V E N I D O ---";
    // Informacion general de la empresa
    cout << "\nFinalidad de su empresa (fabrica, maquila, entre otros): ";
    cin >> tipoTrabajo;
    cout << "Cantidad de procesos a realizar en la produccion: ";
    cin >> cantProcesos;
    cout << "Piezas producidas por minuto: ";
    cin >> piezasPMin;
    cout << "Cantidad de piezas totales a producir: ";
    cin >> cantPiezas;
    cout << "\nNumero de personas que conforman el personal (sin contar a los operadores): ";
    cin >> cantidadPersonal;
    cout << "\nNumero de personas que conforman al grupo de los operadores: ";
    cin >> cantidadOperadores;
    // Inversion en maquina y personal humano
    cout << "Salario del personal en dolares ($): ";
    cin >> salarioPersonal;
    cout << "Salario de los operadores en dolares ($): ";
    cin >> salarioOperadores;
    cout << "Inversion de la maquina en dolares ($): ";
    cin >> inversionMaquina;
    // Presupuesto
    cout << "Presupuesto inicial en dolares ($): ";
    cin >> presupuesto;
    cout << "Inicializando los procesos...";
}