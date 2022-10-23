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
-----------------------------------------------------------------*/

// Librerias
#include <unistd.h>
#include <pthread.h>
#include <iostream>
using namespace std;

// Threads mutex y condicional
pthread_mutex_t piezas;
pthread_cond_t producidas;

// Variables a solicitar
string tipoTrabajo;
int inversionMaquina;
int salarioPersonal;

// Variables fijas
int cantProcesos = 3;               //hilos a crear
int cantPiezasTotales = 10;         //piezas totales a producir
int cantidadPersonalArea1 = 3;      //personas en area 1
int cantidadPersonalArea2 = 3;      //personas en area 2
int cantidadPersonalArea3 = 3;      //personas en area 3
int ensambladosArea1 = 0;           //contador para piezas ensambladas en area 1
int ensambladosArea2 = 0;           //contador para piezas ensambladas en area 2


// --- Estructura con la informacion de los costos ---
struct costos{
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

// --- Proceso area 1 ---
void* area1(void* arg){
    //numero del personas del personal
    int numPersona = *(int*) arg;

    //produccion de piezas en el area 1
    for (int i = 0; i < cantPiezasTotales; i++){
        pthread_mutex_lock(&piezas);
        ensambladosArea1++;
        cout << "Persona del AREA 1: produjo 1 pieza" << endl;
        pthread_mutex_unlock(&piezas);
        pthread_cond_signal(&producidas);
        sleep(1);
    }
    cout << "\nPersonal del AREA 1 ha terminado de producir"<< endl;
    cout << "''''''''''''''''''''" << endl;
    pthread_exit(nullptr);
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
   
    // Inversion en maquina y personal humano
    cout << "\nSalario del personal en dolares ($): ";
    cin >> salarioPersonal;
    cout << "Inversion de la maquina en dolares ($): ";
    cin >> inversionMaquina;

    cout << "Inicializando los procesos...\n";

    pthread_mutex_init(&piezas, nullptr);
    pthread_cond_init(&producidas, nullptr);
    //inicia 3 threads
    pthread_t threads[cantProcesos];

    for (int i = 0; i < cantProcesos; i++){
        if (i == 2){
            //area2
            //pthread_create(&threads[i], nullptr, &area2, nullptr);
        }
        else{
            //area1
            pthread_create(&threads[i], nullptr, &area1, nullptr);
        }
    }
    
    for(auto thread : threads){
        pthread_join(thread, nullptr);
    }
    
    cout << "\nCantidad de piezas ensambladas: " << cantPiezasTotales << endl;
    pthread_exit(NULL);
    return 0;
}