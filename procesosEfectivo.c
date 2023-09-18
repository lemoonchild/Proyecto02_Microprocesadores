/*--------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓ
* CC3086 Programación de Microprocesadores
* 
* Proyecto 02 - Fase 02 
* Fecha: 21/09/2023
* Descripción: Procesos Efectivo
* --------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

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