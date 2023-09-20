
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

// Declaraciones previas

void compass(int number);
void efectivo(int number);
void estadisticas(int number);
void distribucionAutosCompass(int total_number);
void distribucionAutosEfectivo(int total_number);

// Variables para la cantidad de autos que pagarán con Compass y Efectivo.
int numAutosConCompass;
int numAutosEfectivo;

// Variables para representar el tiempo de procesamiento de cada kiosco.
double tiempoKiosconCompass;
double tiempoKiosconEfectivo;

// Variables para representar el tiempo total utilizado por cada kiosco.
double tiempoTotalCompass;
double tiempoTotalEfectivo;

// Variables para la cantidad total de autos y el tiempo total de procesamiento.
int totalAutos;
double tiempoTotal;

//Variables para realizar la simulación de paso de autos.

int idAuto; // para identificar cada auto
double tiempoInicio; // para registrar el tiempo de inicio de paso por un kiosco


void compass(int number) {
    for (int i = 0; i < number; i++) {
        
        sleep(2);
        int localIdAuto;
        int localNumAutosConCompass;
        
        #pragma omp atomic capture
        localIdAuto = idAuto++;

        #pragma omp atomic capture
        localNumAutosConCompass = --numAutosConCompass;
        
        printf("\n\tEl auto numero %d esta usando Compass.", localIdAuto, localNumAutosConCompass);
        printf("\n\tGracias por usar Compass, tenga buen viaje\n");
    }
}

void efectivo(int number) {
    for (int i = 0; i < number; i++) {

        sleep(2);
        int localIdAuto;
        int localNumAutosEfectivo;
        
        #pragma omp atomic capture
        localIdAuto = idAuto++;

        #pragma omp atomic capture
        localNumAutosEfectivo = --numAutosEfectivo;
        
        printf("\n\tEl auto numero %d esta pagando con efectivo.", localIdAuto, localNumAutosEfectivo);
        printf("\n\tGracias por pagar con efectivo, tenga buen viaje\n");
    }
}



void estadisticas(int number) {
    // Parte de Sofi
}

void distribucionAutosCompass(int total_number) {
    #pragma omp parallel num_threads(3)
    {
        int thread_id = omp_get_thread_num();
        int carros_por_hilo = total_number / 3;
        int carros_extra = total_number % 3;

        if (carros_extra != 0) {
            #pragma omp for
            for (int i = 0; i < 3; i++) {
                if (thread_id == i) {
                    if (i == 0) {
                        compass(carros_por_hilo + 1);
                    } else if (i == 1) {
                        carros_extra -= 1;
                        compass(carros_por_hilo + carros_extra);
                    } else {
                        compass(carros_por_hilo);
                    }
                }
            }
        } else compass(carros_por_hilo);
    }
}

void distribucionAutosEfectivo(int total_number) {
    #pragma omp parallel num_threads(3)
    {
        int thread_id = omp_get_thread_num();
        int carros_por_hilo = total_number / 3;
        int carros_extra = total_number % 3;

        if (carros_extra != 0) {
            #pragma omp for
            for (int i = 0; i < 3; i++) {
                if (thread_id == i) {
                    if (i == 0) {
                        efectivo(carros_por_hilo + 1);
                    } else if (i == 1) {
                        carros_extra -= 1;
                        efectivo(carros_por_hilo + carros_extra);
                    } else {
                        efectivo(carros_por_hilo);
                    }
                }
            }
        } else efectivo(carros_por_hilo);
    }
}


int main(int argc, char const *argv[]) {
    printf("\nBienvenido a la estacion de pago de la VAS\n");
    printf("\nPor favor indica cuantos carros desea pagar con Compass: ");
    scanf("%d", &numAutosConCompass);
    printf("\nPor favor indica cuantos carros deseas pagar con efectivo: ");
    scanf("%d", &numAutosEfectivo);

    distribucionAutosCompass(numAutosConCompass);
    distribucionAutosEfectivo(numAutosEfectivo); 

    return 0;
}
