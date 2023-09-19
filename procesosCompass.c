/*--------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓ
* CC3086 Programación de Microprocesadores
* 
* Proyecto 02 - Fase 02 
* Fecha: 21/09/2023
* Descripción: Procesos Compass
* --------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>


// Creacion de función Compass
void compass(int number);

// Variables para la cantidad de autos que pagarán con Compass y Efectivo.
int numAutosConCompass;
int numAutosEfectivo;

// Variables para representar el tiempo de procesamiento de cada kiosco.
double tiempoKioscoCompass;
double tiempoKioscoEfectivo;

// Variables para representar el tiempo total utilizado por cada kiosco.
double tiempoTotalCompass;
double tiempoTotalEfectivo;

// Variables para la cantidad total de autos y el tiempo total de procesamiento.
int totalAutos;
double tiempoTotal;

//Variables para realizar la simulación de paso de autos.

int idAuto; // para identificar cada auto
int tipoPago; // para representar si el auto paga con Compass o en efectivo
double tiempoInicio; // para registrar el tiempo de inicio de paso por un kiosco


void compass(int number) {
    for (int i = 0; i < number; i++) {
        sleep(5);
        printf("Gracias por usar Compass, buen viaje");
    }
}


/*
Carro: 
a.Compass Bool 


1. Int de cuantos carros
    - Random 
2. Una base de datos con carros, una lista 


0. Main
Cuantos carros pasan por Compass = a
Cuantos carros pasan po Efectivo  = b 



1. Main y Función  

    // Dividir el rango en fragmentos para asignar a cada hilo
    long rank = limit / numThreads;
    long residue = limit % numThreads;

    //Creación de array de la estructura creada
    ThreadData threadsData[numThreads];

    //Creación de hilos y asignación de datos a emplear
    for (int i = 0; i < numThreads; i++) {
        threadsData[i].start = i * rank; //Inicio de rango
        //Fin de rango, varía en caso de existir elementos restantes de la division
        threadsData[i].end = (i == numThreads - 1) ? (i + 1) * rank + residue : (i + 1) * rank;

        int rc = pthread_create(&threadID[i], NULL, primeTest, &threadsData[i]);
        if (rc) {
            cout << "No se pudo crear el hilo " << i << endl;
            exit(-1);
        }
    }

2. Función De Compass 
    #include <unistd.h>
    void compass(int number);


    void compass(int number) {
         for (int i = 0; i < number; i++) {
            sleep(5);
            printf("Gracias por usar Compass, buen viaje");
        }
    }




3. Paralelizar función en main 
    #Pragma parallel 
    compass(a)




funcion_compass(Num_de_carros a){
    for (int i = 0; i < a; i++) {
            blablabla bla bla        

    }
}



*/



int main(int argc, char const *argv[])
{
    //Pide los datos
    printf("Cuantos carros quieres para Compass: \n");
    scanf("%d", numAutosConCompass);
    printf("Cuantos carros quieres para Efectivo:\n");
    scanf("%d", numAutosEfectivo);

    //Hace la función con los carros Compass
    


    
    //Hace la función con los carros Efectivo



    return 0;
}
