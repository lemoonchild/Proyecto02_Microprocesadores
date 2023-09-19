
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

// Creacion de función Estadísticas
void estadisticas(int number);

// Creacion de función Estadísticas
void distribucionAutos(int number);

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
    printf("Bienvenido a la estacion: \n");
    //Pide los datos
    printf("Cuantos carros quieres para Compass: \n");
    scanf("%d", &numAutosConCompass);
    printf("Cuantos carros quieres para Efectivo:\n");
    scanf("%d", &numAutosEfectivo);

    //Hace la función con los carros Compass
    distribucionAutos(numAutosConCompass);
    
    //Hace la función con los carros Efectivo



    return 0;
}


void compass(int number) {
    for (int i = 0; i < number; i++) {
        sleep(5);
        printf("Gracias por usar Compass, buen viaje\n");
    }
}

void efectivo(int number) {
 //Parte Naho 
}

void estadisticas(int number) {
 //Parte Sofi 
}

//Repartir el total de autos en los hilos que tenemos
void distribucionAutos(int total_number){
    #pragma omp parallel num_threads(3)
    {
        int thread_id = omp_get_thread_num();
        int carros_por_hilo = total_number / 3;
        int carros_extra = total_number % 3;

        if (carros_extra != 0)
        {
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
        
        

        // Llama a compass una vez por hilo con la cantidad total a procesar
        
    }
}