
/*--------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓ
* CC3086 Programación de Microprocesadores
* Programadores: Sofía Velásquez, Fabiola Contreras, Madeline Castro, Maria José Villafuerte 
* Proyecto 02 - Fase 02 
* Fecha: 21/09/2023
* Descripción: Simulacion de la VAS
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
void distribucionAutos(int total_compass, int total_efectivo);

// Variables para la cantidad de autos que pagarán con Compass y Efectivo.
int numAutosConCompass, numAutosEfectivo;

// Variables para representar el tiempo de procesamiento de cada kiosco.
double tiempoTotalCompass[3] = {0}; 
double tiempoTotalEfectivo[3] = {0}; 

double tiempoInicio; 
int nextAutoType = 0; 

void compass(int number) {
    for (int i = 0; i < number; i++) {
        double start_time = omp_get_wtime(); 
        sleep(3);  
        #pragma omp critical
        {
            printf("\n\tEl auto esta usando Compass.");
            printf("\n\tGracias por usar Compass, tenga buen viaje\n");
        }
        double end_time = omp_get_wtime();  
        int thread_id = omp_get_thread_num();
        tiempoTotalCompass[thread_id] += (end_time - start_time);
    }
}

void efectivo(int number) {
    for (int i = 0; i < number; i++) {
        double start_time = omp_get_wtime(); 
        sleep(4);      
        #pragma omp critical
        {
            printf("\n\tEl auto esta pagando con efectivo."); 
            printf("\n\tGracias por pagar con efectivo, tenga buen viaje\n");
        }
        double end_time = omp_get_wtime();  
        int thread_id = omp_get_thread_num();
        tiempoTotalEfectivo[thread_id] += (end_time - start_time);
    }
}

void estadisticas(double number) {
    printf("\n--- Estadisticas de la simulacion ---\n");
    for (int i = 0; i < 3; i++) {
        printf("Tiempo del kiosco Compass %d: %f segundos\n", i+1, tiempoTotalCompass[i]);
    }
    for (int i = 0; i < 3; i++) {
        printf("Tiempo del kiosco Efectivo %d: %f segundos\n", i+1, tiempoTotalEfectivo[i]);
    }
    printf("\nTiempo total de la estacion: %f segundos\n\n", number);
}

void distribucionAutos(int total_compass, int total_efectivo) {

    #pragma omp parallel num_threads(6)
    { //6 Hilos que hacen este proceso
        int thread_id = omp_get_thread_num();
            int numKioscos = 3;

        int autosPorKioscoCompass = total_compass / numKioscos;
        int autosExtraCompass1 = (total_compass % numKioscos != 0 ) ? 1: 0; //Si hay residuo se suma 1 carro al hilo
        int autosExtraCompass2 = (total_compass % numKioscos == 2 ) ? 1: 0;

        int autosPorKioscoEfectivo = total_efectivo / numKioscos;
        int autosExtraEfectivo1 = (total_efectivo % numKioscos != 0 ) ? 1: 0;
        int autosExtraEfectivo2 = (total_efectivo % numKioscos == 2 ) ? 1: 0;
        #pragma omp for
        for (int i = 0; i < 6; i++) {
            if (thread_id == i) {
                if (i == 0) {
                    compass(autosPorKioscoCompass + autosExtraCompass1);
                } else if (i == 1) {
                    compass(autosPorKioscoCompass + autosExtraCompass2);
                } else if (i == 2) {
                    compass(autosPorKioscoCompass);
                } else if (i == 3) {
                    efectivo(autosPorKioscoEfectivo + autosExtraEfectivo1);
                } else if (i == 4) {
                    efectivo(autosPorKioscoEfectivo + autosExtraEfectivo2);
                } else if (i == 5) {
                    efectivo(autosPorKioscoEfectivo);
                }
            }
        }
        
    }
}

int main(int argc, char const *argv[]) {
    printf("\nBienvenido a la simulacion de estacion de pago de la VAS\n");
    printf("\nPor favor indica cuantos carros desea pagar con Compass: ");
    scanf("%d", &numAutosConCompass);
    printf("\nPor favor indica cuantos carros deseas pagar con efectivo: ");
    scanf("%d", &numAutosEfectivo);
    printf("\nComenzando simulacion...\n");

    double start_time = omp_get_wtime(); 
    distribucionAutos(numAutosConCompass, numAutosEfectivo);
    double end_time = omp_get_wtime(); 

    printf("\nFinalizando simualcion...\n"); 
    estadisticas(end_time - start_time);  

    return 0;
}
