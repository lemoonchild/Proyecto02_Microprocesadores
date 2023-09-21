
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

// Función principal, solicita los datos requeridos al usuario y llama a función secundaria
// para ejecutar el resto del programa. Además toma el tiempo general de ejecución e indica
// cuando se ha finalizado el proceso.
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

// Proceso para kioskos de pago con Compass.
void compass(int number) { //number es el total de autos que pasan por el kiosko
    for (int i = 0; i < number; i++) { //Se repite hasta culminar con los autos
        double start_time = omp_get_wtime(); 
        sleep(3);  //"Tiempo de pago del auto"
        #pragma omp critical //Pone prioridad a la impresión del texto
        {
            printf("\n\tEl auto esta usando Compass.");
            printf("\n\tGracias por usar Compass, tenga buen viaje\n");
        }
        double end_time = omp_get_wtime();  
        int thread_id = omp_get_thread_num();
        //Toma el tiempo de ejecución y lo guarda en la posición adecuada del array
        tiempoTotalCompass[thread_id] += (end_time - start_time); 
    }
}

// Proceso para kioskos de pago con efectivo.
void efectivo(int number) { //number es el total de autos que pasan por el kiosko
    for (int i = 0; i < number; i++) {
        double start_time = omp_get_wtime(); 
        sleep(4); //"Tiempo de pago del auto"
        #pragma omp critical //Pone prioridad a la impresión del texto
        {
            printf("\n\tEl auto esta pagando con efectivo."); 
            printf("\n\tGracias por pagar con efectivo, tenga buen viaje\n");
        }
        double end_time = omp_get_wtime();  
        int thread_id = omp_get_thread_num();
        //Toma el tiempo de ejecución y lo guarda en la posición adecuada del array
        tiempoTotalEfectivo[thread_id - 3] += (end_time - start_time);
    }
}

// Proceso para toma de tiempo en el programa. Recibe el tiempo total del programa
void estadisticas(double number) {
    printf("\n--- Estadisticas de la simulacion ---\n");
    for (int i = 0; i < 3; i++) { //Muestra tiempo de cada hilo (kiosko) con Compass
        printf("Tiempo del kiosco Compass %d: %f segundos\n", i+1, tiempoTotalCompass[i]);
    }
    for (int i = 0; i < 3; i++) { //Muestra tiempo de cada hilo (kiosko) con efectivo
        printf("Tiempo del kiosco Efectivo %d: %f segundos\n", i+1, tiempoTotalEfectivo[i]);
    }
    //Muestra el tiempo de ejecución de la simulación
    printf("\nTiempo total de la estacion: %f segundos\n\n", number);
}

// Distribuye los autos dados por el usuario en los tres kioskos (hilos) con los que se cuentan
void distribucionAutos(int total_compass, int total_efectivo) {
    #pragma omp parallel num_threads(6)
    { //6 Hilos que hacen este proceso
        int thread_id = omp_get_thread_num(); //Necesario para asignarle las tareas a cada hilo

        int autosPorKioscoCompass = total_compass / 3; //Autos que deben pasar en un kiosko (de los 3 existentes)
        int autosExtraCompass1 = (total_compass % 3 != 0 ) ? 1: 0; //Si hay residuo se sumará 1 carro al hilo
        int autosExtraCompass2 = (total_compass % 3 == 2 ) ? 1: 0;

        int autosPorKioscoEfectivo = total_efectivo / 3; //Autos que deben pasar en un kiosko (de los 3 existentes)
        int autosExtraEfectivo1 = (total_efectivo % 3 != 0 ) ? 1: 0; //Si hay residuo se sumará 1 carro al hilo
        int autosExtraEfectivo2 = (total_efectivo % 3 == 2 ) ? 1: 0;
        #pragma omp for
        for (int i = 0; i < 6; i++) {
            if (thread_id == i) { //Limitamos a que se usen los hilos con id's del 0 al 5
                if (i == 0) { //Llama a la función con el total de autos que deben pasar por el kiosko
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


