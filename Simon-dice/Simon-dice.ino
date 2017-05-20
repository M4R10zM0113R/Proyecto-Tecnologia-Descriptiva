/*
Tecnología Descriptiva Sección B

Integrantes: (Nombre, Carnet)
	Mario Möller, 16012890
	Juan Pablo Gomez, 17003071

Archivo del programa Simón Dice
*/

// Declaración de posiciones en el Arduino
//// Entradas
const int boton_rojo = 9;
const int boton_azul = 10;
const int boton_amarillo = 11;
const int boton_verde = 12;
const int boton_random = 13;
//// Salidas
const int led_rojo = 2;
const int led_azul = 3;
const int led_amarillo = 4;
const int led_verde = 5;
const int led_random = 6;
const int zumbador = 7;

// Declaración de variables
//// Zumbador
int notas = 15;							// Cantidad de notas en la melodía
char melodia[] = "cacaffeggeeddc";				// Melodía, dada en notación musical GABCDEF
int tiempos[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 4 };	// Tiempos por nota
int tempo = 100;						// Tiempo por nota
//// Otros
int puntuacion_maxima = 20;					// Cantidad de pasos a recordar antes de ganar
long secuencia[puntuacion_maxima];				// La variable para almacenar la secuencia
int contador = 0;						// Contador para recorrer la secuencia mientras se juegue
int input = 5;							// Para indicar el botón pulsado
int despliegue = 500;						// Tiempo en ms para desplegar cada LED en secuencia
