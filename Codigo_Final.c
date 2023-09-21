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
omp_lock_t lock; 

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
        sleep(3);      
        #pragma omp critical
        {
            printf("\n\tEl auto esta pagando con efectivo."); 
            printf("\n\tEsperando pago en efectivo...");
            sleep(2);
            printf("\n\tGracias por pagar con efectivo, tenga buen viaje\n");
        }
        double end_time = omp_get_wtime();  
        int thread_id = omp_get_thread_num();
        tiempoTotalEfectivo[thread_id] += (end_time - start_time);
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
    printf("\nTiempo total de la estacion: %f segundos\n\n", number);
}

void distribucionAutos(int total_compass, int total_efectivo) {
    int numKioscos = 3;

    int autosPorKioscoCompass = total_compass / numKioscos;
    int autosExtraCompass = total_compass % numKioscos;

    int autosPorKioscoEfectivo = total_efectivo / numKioscos;
    int autosExtraEfectivo = total_efectivo % numKioscos;

    #pragma omp parallel for
    for (int i = 0; i < numKioscos; i++) {
        for (int j = 0; j < (autosPorKioscoCompass + (i < autosExtraCompass ? 1 : 0) + autosPorKioscoEfectivo + (i < autosExtraEfectivo ? 1 : 0)); j++) {
            if (j % 2 == 0) {
                if (j/2 < autosPorKioscoEfectivo + (i < autosExtraEfectivo ? 1 : 0)) {
                    efectivo(1);
                } else {
                    compass(1);
                }
            } else {
                if (j/2 < autosPorKioscoCompass + (i < autosExtraCompass ? 1 : 0)) {
                    compass(1);
                } else {
                    efectivo(1);
                }
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    printf("\nBienvenido a la estacion de pago de la VAS\n");
    printf("\nPor favor indica cuantos carros desea pagar con Compass: ");
    scanf("%d", &numAutosConCompass);
    printf("\nPor favor indica cuantos carros deseas pagar con efectivo: ");
    scanf("%d", &numAutosEfectivo);

    omp_init_lock(&lock);
    double start_time = omp_get_wtime(); 
    distribucionAutos(numAutosConCompass, numAutosEfectivo);
    double end_time = omp_get_wtime(); 
    estadisticas(end_time - start_time);  
    omp_destroy_lock(&lock);

    return 0;
}
