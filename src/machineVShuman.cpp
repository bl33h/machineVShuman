/*---------------------------------------------------------------------------
Copyright (C), 2022-2023, bl33h, MelissaPerez09, FabianJuarez182, SebasJuarez
@author Sara Echeverria, Melissa Perez, Fabian Juarez, Sebastian Juarez
FileName: machineVShuman
@version: VI
Creation: 06/10/2022
Last modification: 22/10/2022
----------------------------------------------------------------------------------------------------
* Descripcion: 
* Establecer la eficiencia y rentabilidad a largo plazo de la produccion de una 
* máquina en comparacion a la que el personal humano realizaria. 

* Condiciones:
* La cantidad de personal en las areas debe de ir en disminucion (siendo el area1 > area2 > area3)
-----------------------------------------------------------------*/


// Librerias
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <semaphore.h>
using namespace std;


// Threads mutex y condicional
pthread_mutex_t piezas;
pthread_cond_t producidas;
sem_t semaphore;

// Variables a solicitar
string tipoTrabajo;
int inversionMaquina;
int salarioPersonal;

// Variables fijas
int cantProcesos = 1;               //hilos a crear
int cantPiezasTotales = 10;         //piezas totales a producir
int cantidadPiezasPorArea1 = 0;     //Cantidad de piezas a generar en el area 1
int cantidadPersonalArea1 = 2;      //personas en area 1
int cantidadPersonalArea2 = 1;      //personas en area 2
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
        sem_wait(&semaphore);
        piezasEnsambladas++;
        cout << "Persona del AREA 3: ensamblo 1 pieza" << endl;
        pthread_mutex_unlock(&piezas);
        pthread_cond_signal(&producidas);
        sleep(1);
        sem_post(&semaphore);
    }
    cout << "\nPersonal del AREA 3 ha terminado de producir"<< endl;
    cout << "''''''''''''''''''''" << endl;
    pthread_exit(nullptr);
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

    pthread_mutex_init(&piezas, nullptr);
    pthread_cond_init(&producidas, nullptr);
    sem_init(&semaphore, 0, 2);
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
    pthread_exit(NULL);
    
    //libera memoria
    sem_destroy(&semaphore);
    pthread_mutex_destroy(&piezas);
    pthread_cond_destroy(&producidas);
    return 0;
}