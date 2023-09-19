
/*--------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓ
* CC3086 Programación de Microprocesadores
* 
* Proyecto 02 - Fase 02 
* Fecha: 21/09/2023
* Descripción: Estadisticas de la Simulacion de la VAS
* --------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <unistd.h>


// Creacion de función Compass
void compass(int number);

// Creacion de función Efectivo
void efectivo(int number);

// Creacion de función Efectivo
void estadisticas(int number);

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


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}


void compass(int number) {
    for (int i = 0; i < number; i++) {
        sleep(5);
        printf("Gracias por usar Compass, buen viaje");
    }
}

void efectivo(int number) {
 //Parte Naho 
}

void estadisticas(int number) {
 //Parte Sofi 
}

