/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, bl33h, MelissaPerez09, FabianJuarez182, SebasJuarez
@author Sara Echeverria, Melissa Perez, Fabian Juarez, Sebastian Juarez
FileName: machineVShuman
@version: VI
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

// Mutex lock
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Variables
string tipoTrabajo;
int cantProcesos;
/* meter esta en el main por la cantidad de Personal int tiempoEjecucion[cantidadPersonal];*/
int inversionMaquina;
int cantidadPersonalArea1;
int cantidadPersonalArea2;
int cantidadPersonalArea3;
int salarioPersonal;
int cantidadOperadores;
int salarioOperadores;
int presupuesto;
int proyeccion;
int cantPiezasTotales;
int ensamblajeMaquina = 0;
int piezasPMin;
int contador;
int enEspera = 0;
int cantPiezasT=0;

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
    int cantProcesos = 0;
    int cantPiezas = 0;
    int contador = 0;
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
    int costoVariable = (cantPiezasTotales/piezasPMin) * 2; // Valor fijo
    int costoTotal = costoFijoTotal + costoVariable;
    return NULL;
}

// --- Metodo produccion por parte del personal humano ---
void* procesoPersonal(void *args)
{
   datosEmpleado *produccionStructure = (datosEmpleado*) args; // *Structure call
    // *Mutex lock*
    while(produccionStructure->cantPiezas != cantPiezasT && cantPiezasT > 0)
    {
        if (cantPiezasT > 0){
            pthread_mutex_lock(&mutex);
            produccionStructure->cantPiezas = produccionStructure->cantPiezas + piezasPMin;
            cantPiezasT = cantPiezasT - piezasPMin;
            cout<<"El proceso No."<< produccionStructure->contador << ", realizado por el personal humano, ha producido " << piezasPMin <<  " piezas." << cantPiezasT <<endl;
            // *Mutex Unlock*
            pthread_mutex_unlock(&mutex);
        }
        else{
            pthread_exit(NULL);
        }
    }
}

// --- Metodo produccion por parte de la maquina ---
void* procesoMaquina(void *arg)
{
    for (int i = 0; i < cantPiezasTotales; i++){
        pthread_mutex_lock(&mutex);
        ensamblajeMaquina++;
        cout << "La maquina ha ensamblado una pieza" << endl;
        pthread_mutex_unlock(&mutex);
    }
    cout << "Proceso terminado"<< endl;
    cout << "''''''''''''''''''''\n" << endl;
    pthread_exit(nullptr);
}

void* procesoMaquina2(void* arg){
    pthread_mutex_lock(&mutex);
    while (ensamblajeMaquina < cantPiezasTotales-2){
        //pthread_cond_wait(&entregado, &pieza);
    }
    pthread_mutex_unlock(&mutex);
    cout << "\nComenzando el siguiente proceso" << endl;
    cout << "''''''''''''''''''''" << endl;
    
    while (enEspera <= cantPiezasTotales && ensamblajeMaquina > 0){
        pthread_mutex_lock(&mutex);
        cout << "Piezas en espera: " << ensamblajeMaquina-- << endl;
        cout << "La maquina ha ensamblado una pieza" << endl;
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    pthread_exit(nullptr);
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
    cin >> cantPiezasTotales;
    cout << "\nNumero de personas que conforman el personal de la 1ra fase (sin contar a los operadores): ";
    cin >> cantidadPersonalArea1;
    cout << "\nNumero de personas que conforman el personal de la 2da fase (sin contar a los operadores): ";
    cin >> cantidadPersonalArea2;
    cout << "\nNumero de personas que conforman el personal de la 3ra fase (sin contar a los operadores): ";
    cin >> cantidadPersonalArea3;
    cout << "Numero de personas que conforman al grupo de los operadores: ";
    cin >> cantidadOperadores;
    // Inversion en maquina y personal humano
    cout << "\nSalario del personal en dolares ($): ";
    cin >> salarioPersonal;
    cout << "Salario de los operadores en dolares ($): ";
    cin >> salarioOperadores;
    cout << "Inversion de la maquina en dolares ($): ";
    cin >> inversionMaquina;
    // Presupuesto
    cout << "\nPresupuesto inicial en dolares ($): ";
    cin >> presupuesto;
    cout << "Inicializando los procesos...\n";
    cantPiezasT = cantPiezasTotales;
    datosEmpleado estructuraDatosEmpleado[cantidadPersonalArea1];
    for(int i=0; i<cantidadPersonalArea1; i++){
        estructuraDatosEmpleado[i].cantProcesos = cantPiezasT;
        estructuraDatosEmpleado[i].contador = i;
    }
    for (int k = 0; k < cantidadPersonalArea1; k++){
            pthread_create(&estructuraDatosEmpleado[k].thread, NULL, procesoPersonal, ( void *)&estructuraDatosEmpleado[k]);
    }
    for(int l = 0; l < cantidadPersonalArea1; l++){
        pthread_join(estructuraDatosEmpleado[l].thread, NULL);
    }
    pthread_mutex_init(&mutex, nullptr);
    pthread_t threads[cantProcesos];
    
    for (int i = 0; i < cantProcesos; i++){
        if (i == 2){
            pthread_create(&threads[i], nullptr, &procesoMaquina2, nullptr);
        }
        else{
            pthread_create(&threads[i], nullptr, &procesoMaquina, nullptr);
        }
    }
    
    for(auto thread : threads){
        pthread_join(thread, nullptr);
    }
    
    cout << "\nCantidad de piezas ensambladas: " << cantPiezasTotales << endl;
    pthread_exit(NULL);
    return 0;
}