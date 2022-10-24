/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, bl33h, MelissaPerez09, FabianJuarez182, SebasJuarez
@author Sara Echeverria, Melissa Perez, Fabian Juarez, Sebastian Juarez
FileName: machineVShuman
@version: VII
Creation: 06/10/2022
Last modification: 23/10/2022
----------------------------------------------------------------------------------------------------
* Descripcion: 
* Establecer la eficiencia y rentabilidad a largo plazo de la produccion de una 
* máquina en comparacion a la que el personal humano realizaria. 

* Condiciones:
* La cantidad de personal en las areas debe de ir en disminucion (siendo el area1 > area2 > area3)
-----------------------------------------------------------------*/


// Librerias
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <math.h>
#include <errno.h>
#include <sys/wait.h>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <semaphore.h>
using namespace std;

// Threads mutex y condicional
pthread_mutex_t piezas;
pthread_cond_t producidas;

// Variables a solicitar
string tipoTrabajo;
int inversionMaquina;
int salarioPersonal;

// Variables fijas
int cantProcesos = 1;               //hilos a crear
int cantPiezasTotales = 10;         //piezas totales a producir
int cantidadPiezasPorArea1 = 0;     //Cantidad de piezas a generar en el area 1
int cantidadPersonalArea1 = 2;      //personas en area 1
int cantidadPersonalArea2 = 2;      //personas en area 2
int cantidadPersonalArea3 = 1;      //personas en area 3
int ensambladosArea1 = 0;           //contador para piezas ensambladas en area 1
int ensambladosArea2 = 0;           //contador para piezas ensambladas en area 2
int piezasEnsambladas = 0;          //contador para totales piezas ensambladas


// --- Estructura con la informacion de los costos ---
struct costo{
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
    //int costoVariable = (cantPiezasTotales/piezasPMin) * 2; // Valor fijo
    //int costoTotal = costoFijoTotal + costoVariable;
    return NULL;
}

// --- Proceso area 1 ---
void* area1(void* arg){

    //produccion de piezas en el area 1
    for (int i = 0; i < cantPiezasTotales / cantidadPersonalArea1; i++){
        pthread_mutex_lock(&piezas);
        ensambladosArea1++;
        cout << "Persona del AREA 1: ensamblo 1 pieza" << endl;
        pthread_mutex_unlock(&piezas);
        pthread_cond_signal(&producidas);
        sleep(1);
    }
    cout << "\nPersonal del AREA 1 ha terminado de producir"<< endl;
    cout << "''''''''''''''''''''" << endl;
    pthread_exit(nullptr);
}

// --- Proceso area 2 ---
void* area2(void* arg){
    pthread_mutex_lock(&piezas);
    //cada 5 piezas ensambladas por el area 1, comienza a ensamblar
    while (ensambladosArea1 < 5){
        pthread_cond_wait(&producidas, &piezas);
    }
    pthread_mutex_unlock(&piezas);
    cout << "\nAREA 2 ha comenzado a ensamblar" << endl;
    cout << "''''''''''''''''''''" << endl;

    //produccion de piezas en el area 2
    for (int i = 0; i < ensambladosArea1 / cantidadPersonalArea2 ; i++){
        pthread_mutex_lock(&piezas);
        ensambladosArea2++;
        cout << "Persona del AREA 2: ensamblo 1 pieza" << endl;
        pthread_mutex_unlock(&piezas);
        pthread_cond_signal(&producidas);
        sleep(1);
    }
    cout << "\nPersonal del AREA 2 ha terminado de producir"<< endl;
    cout << "''''''''''''''''''''" << endl;
    pthread_exit(nullptr);
}

// --- Proceso area 3 ---
void* area3(void* arg){
    pthread_mutex_lock(&piezas);
    //cada 5 piezas ensambladas por el area 2, comienza a ensamblar
    while (ensambladosArea2 < 5){
        pthread_cond_wait(&producidas, &piezas);
    }
    pthread_mutex_unlock(&piezas);
    cout << "\nAREA 3 ha comenzado a ensamblar" << endl;
    cout << "''''''''''''''''''''" << endl;

    //produccion de piezas en el area 3
    for (int i = 0; i < ensambladosArea2 / cantidadPersonalArea3; i++){
        pthread_mutex_lock(&piezas);
        piezasEnsambladas++;
        cout << "Persona del AREA 3: ensamblo 1 pieza" << endl;
        pthread_mutex_unlock(&piezas);
        pthread_cond_signal(&producidas);
        sleep(1);
    }
    cout << "\nPersonal del AREA 3 ha terminado de producir"<< endl;
    cout << "''''''''''''''''''''" << endl;
    pthread_exit(nullptr);
}

// --- Estructura del control de la maquina ---
struct controlMaquina{
    int piezasPorLaMaquina = 0;
    int piezasProceso2 = 0;
    int piezasProceso3 = 0;
};

// --- Primer metodo maquina ---
void *maquina1(void *piezasM)
{
    controlMaquina *estructuraMaquina = (controlMaquina*) piezasM; // *Structure call
    // *Mutex lock*
    pthread_mutex_lock(&piezas);
    cout<<"El primer proceso de la maquina ha producido 1 pieza."<<endl;
    estructuraMaquina->piezasPorLaMaquina += 1;
    // *Mutex Unlock*
    pthread_mutex_unlock(&piezas);
    pthread_mutex_destroy(&piezas);
    return NULL;
}

// --- Segundo metodo maquina ---
void *maquina2(void *piezasM)
{
    controlMaquina *estructuraMaquina = (controlMaquina*) piezasM; // *Structure call
    // *Mutex lock*
    pthread_mutex_lock(&piezas);
    cout<<"El segundo proceso de la maquina ha producido 1 pieza."<<endl;
    estructuraMaquina->piezasProceso2 += 1;
    cout<<"Piezas totales ensambladas: "<<estructuraMaquina--->piezasProceso2<<endl;
    // *Mutex Unlock*
    pthread_mutex_unlock(&piezas);
    pthread_mutex_destroy(&piezas);
    return NULL;
}


// --- Main ---
int main(){
    cout << "--- B I E N V E N I D O ---" << endl;
    // Informacion general de la empresa
    //cout << "\nFinalidad de su empresa (fabrica, maquila, entre otros): ";
    //cin >> tipoTrabajo;
   
    // Inversion en maquina y personal humano
    //cout << "\nSalario del personal en dolares ($): ";
    //cin >> salarioPersonal;
    //cout << "Inversion de la maquina en dolares ($): ";
    //cin >> inversionMaquina;

    cout << "Inicializando los procesos...\n\n";
    cout << "--- Produccion por parte del personal humano ---\n\n";
    
    pthread_mutex_init(&piezas, nullptr);
    pthread_cond_init(&producidas, nullptr);
    //inicia con la cantidad de procesos que se crean los thread
    pthread_t threads[1];
    
    cantidadPiezasPorArea1 = cantPiezasTotales / cantidadPersonalArea1;
    for (int i = 0; i < 1; i++){
        for (int i = 0; i < cantidadPersonalArea1; i++){
            pthread_create(&threads[i], nullptr, &area1, nullptr);
        }
        for (int i = 0; i < cantidadPersonalArea2; i++){
            pthread_create(&threads[i], nullptr, &area2, nullptr);
        }
        for (int i = 0; i < cantidadPersonalArea3; i++){
            pthread_create(&threads[i], nullptr, &area3, nullptr);
        }
    }
    
    for(auto thread : threads){
        pthread_join(thread, nullptr);
    }
    
    cout << "\nCantidad de piezas ensambladas: " << piezasEnsambladas << endl;
    //pthread_exit(NULL);
    
    cout << "--- Produccion por parte de la maquina ---\n\n";
    double worker;
    bool produccion = false;
    controlMaquina produccionMaquina;
    pthread_t tid[2];
    pthread_attr_t attr;
    cout<<"La produccion por la maquina ha comenzado..."<<endl;
    while(produccion == false){
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
        worker = pthread_create(&tid[0],&attr,maquina1,(void *)&produccionMaquina);
        worker = pthread_join(tid[0],NULL);
        if(produccionMaquina.piezasProceso2 == 10)
        {
            produccionMaquina.piezasPorLaMaquina -= 4;
            produccionMaquina.piezasProceso2 = 10;
            produccion = true;
        }
        if((produccionMaquina.piezasPorLaMaquina % 5 == 0)||(produccionMaquina.piezasPorLaMaquina== 5))
        {
            produccionMaquina.piezasPorLaMaquina -= 1;
            worker = pthread_create(&tid[2],&attr,maquina2,(void *)&produccionMaquina);
            worker = pthread_join(tid[2],NULL);
        }
        worker = pthread_create(&tid[1],&attr,maquina1,(void *)&produccionMaquina);
        worker = pthread_join(tid[1],NULL);
        sleep(1);
        if(produccionMaquina.piezasProceso2 == 10)
        {
            produccionMaquina.piezasPorLaMaquina -= 4;
            produccionMaquina.piezasProceso2 = 10;
            produccion = true;
        }
        if((produccionMaquina.piezasPorLaMaquina % 5 == 0)||(produccionMaquina.piezasPorLaMaquina== 5))
        {
            produccionMaquina.piezasPorLaMaquina -=1;
            worker = pthread_create(&tid[2],&attr,maquina2,(void *)&produccionMaquina);
            worker = pthread_join(tid[2],NULL);
        }
    }
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
    return 0;
}