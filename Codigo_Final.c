
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
void estadisticas(double number);
void distribucionAutosCompass(int total_number);
void distribucionAutosEfectivo(int total_number);

// Variables para la cantidad de autos que pagarán con Compass y Efectivo.
int numAutosConCompass;
int numAutosEfectivo;

// Variables para representar el tiempo de procesamiento de cada kiosco.
double tiempoTotalCompass[3] = {0}; // Un arreglo para llevar el registro del tiempo de cada kiosco de Compass
double tiempoTotalEfectivo[3] = {0}; // Un arreglo para llevar el registro del tiempo de cada kiosco de efectivo

//Variables para realizar la simulación de paso de autos.

int idAuto=0; // para identificar cada auto
double tiempoInicio; // para registrar el tiempo de inicio de paso por un kiosco


void compass(int number) {
    for (int i = 0; i < number; i++) {
        double start_time = omp_get_wtime(); // Registrar el tiempo de inicio
        sleep(2);
        int localIdAuto;
        int localNumAutosConCompass;
        
        #pragma omp atomic capture
        localIdAuto = idAuto++;

        #pragma omp atomic capture
        localNumAutosConCompass = --numAutosConCompass;
        
        printf("\n\tEl auto numero %d esta usando Compass.", localIdAuto, localNumAutosConCompass);
        printf("\n\tGracias por usar Compass, tenga buen viaje\n");
        double end_time = omp_get_wtime(); // Registrar el tiempo de finalización
        int thread_id = omp_get_thread_num(); // Obtener el ID del thread
        tiempoTotalCompass[thread_id] += (end_time - start_time); // Actualizar el tiempo total para este kiosco
    }
}

void efectivo(int number) {
    for (int i = 0; i < number; i++) {
        double start_time = omp_get_wtime(); // Registrar el tiempo de inicio
        sleep(2);
        int localIdAuto;
        int localNumAutosEfectivo;
        
        #pragma omp atomic capture
        localIdAuto = idAuto++;

        #pragma omp atomic capture
        localNumAutosEfectivo = --numAutosEfectivo;
        
        printf("\n\tEl auto numero %d esta pagando con efectivo.", localIdAuto, localNumAutosEfectivo);
        printf("\n\tGracias por pagar con efectivo, tenga buen viaje\n");
        double end_time = omp_get_wtime(); // Registrar el tiempo de finalización
        int thread_id = omp_get_thread_num(); // Obtener el ID del thread
        tiempoTotalEfectivo[thread_id] += (end_time - start_time); // Actualizar el tiempo total para este kiosco
    }
}



void estadisticas(double number) {
    printf("\n--- Estadisticas ---\n");
    for (int i = 0; i < 3; i++) {
        printf("Tiempo del kiosco Compass %d: %f segundos\n", i+1, tiempoTotalCompass[i]);
    }

    for (int i = 0; i < 3; i++) {
        printf("Tiempo del kiosco Efectivo %d: %f segundos\n", i+1, tiempoTotalEfectivo[i]);
    }
    printf("Tiempo total de la estacion: %f segundos\n", number);
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
    double start_time = omp_get_wtime(); // Registrar el tiempo de inicio
    distribucionAutosCompass(numAutosConCompass);
    distribucionAutosEfectivo(numAutosEfectivo); 
    double end_time = omp_get_wtime(); // Registrar el tiempo de finalización
    estadisticas(end_time-start_time);  // Llamar a la función para imprimir las estadísticas

    return 0;
}
