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
int input = 6;							// Para indicar el botón pulsado
int despliegue = 500;						// Tiempo en ms para desplegar cada LED en secuencia

// Configuración inicial del Arduino
void setup() {
	// Entradas
	pinMode(boton_rojo, INPUT);
	pinMode(boton_azul, INPUT);
	pinMode(boton_amarillo, INPUT);
	pinMode(boton_verde, INPUT);
	pinMode(boton_random, INPUT);
	// Salidas
	pinMode(led_rojo, OUTPUT);
	pinMode(led_azul, OUTPUT);
	pinMode(led_amarillo, OUTPUT);
	pinMode(led_verde, OUTPUT);
	pinMode(zumbador, OUTPUT);
	// Resistencias de pullup, ya que los botones son normalmente abiertos
	digitalWrite(boton_rojo, HIGH);
	digitalWrite(boton_azul, HIGH);
	digitalWrite(boton_amarillo, HIGH);
	digitalWrite(boton_rojo, HIGH);
	digitalWrite(boton_rojo, HIGH);
	// Melodía al inicio
	melodia();
}

// El ciclo de repetición
void loop() {
	ver_secuencia();					// Reproduce la secuencia
	recibir_secuencia();					// Lee la secuencia
	delay(1000);						// Espera 1 segundo para procesar la secuencia recibida
}

// Función que define las notas y frecuencias
void playnota(char nota, int duracion) {
	char nombres[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };		// Notas Musicales con su notación GABCDEF
	int tonos[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };	// Tonalidad en el espectro que el zumbador puede reproducir

	for (int i = 0; i < 8; i++) {
		if (nombres[i] == nota) {
			playtone(tonos[i], duracion);
		}
	}
}

// Función que define las notas según su duración y el tono
void playtono(int tono, int duracion) {
	for(long i = 0; i < duracion * 1000L; i += tono *2) {
		digitalWrite(zumbador, HIGH);
		delayMicroseconds(tono);
		digitalWrite(zumbador, LOW);
		delayMicroseconds(tono);
	}
}

// Funciones para encender LEDs y reproducir el tono correspondiente
void destello_rojo() {
	digitalWrite(led_rojo, HIGH);
	playtono(2273,wait);
	digitalWrite(led_rojo, LOW);
}
void destello_azul() {
	digitalWrite(led_azul, HIGH);
	playtono(1700,wait);
	digitalWrite(led_azul, LOW);
}
void destello_amarillo() {
	digitalWrite(led_amarillo, HIGH);
	playtono(1275,wait);
	digitalWrite(led_amarillo, LOW);
}
void destello_verde() {
	digitalWrite(led_verde, HIGH);
	playtono(1136,wait);
	digitalWrite(led_verde, LOW);
}

// Función para mostrar qué boton se tenía que presionar en caso de error del jugador
void cual_era_correcto(long led) {
	switch (led) {
			case 0;
			destello_rojo();
			break;
			case 1;
			destello_verde();
			break;
			case 2;
			destello_amarillo();
			break;
			case 3;
			destello_azul();
			break;
	}
	delay(50);
}

// Función para reproducir melodía al iniciar el arduino
void melodia() {
	digitalWrite(led_rojo, HIGH);
	digitalWrite(led_verde, HIGH);
	digitalWrite(led_amarillo, HIGH);
	digitalWrite(led_azul, HIGH);
	
	for (int i = 0; i < length; i++) {
		if(notas[i] == ' ') {
			delay(pulsos[i] * tempo);			// Retraso por nota
		}else {
			playnota(notas[i], pulsos[i] * tempo);
		}
		delay(tempo / 2);
	}
	delay(1000);							// Espera un segundo
	digitalWrite(led_rojo, LOW);					// Reestablece la condición inicial de los LEDs
	digitalWrite(led_verde, LOW);
	digitalWrite(led_amarillo, LOW);
	digitalWrite(led_azul, LOW);
	resetearcontador();						// Reinicio del juego
}
