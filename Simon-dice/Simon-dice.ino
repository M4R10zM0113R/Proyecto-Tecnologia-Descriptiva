/*
Tecnología Descriptiva Sección B

Integrantes: (Nombre, Carnet)
	Mario Möller, 16012890
	Juan Pablo Gomez, 17003071
	Luis Pablo Garabito 17002509

Archivo del programa Simón Dice
*/

// declaran pines de salida 
const int led_rojo = 2;      
const int led_azul = 3;
const int led_amarillo = 4;
const int led_verde = 5;

// Declaramos el pin para el zumbador piezoelectrico
const int zumbador = 6;

// Declaramos los pins de salida para los botones
const int boton_rojo = 9;      
const int boton_azul = 10;
const int boton_amarillo = 11; 
const int boton_verde = 12;

 // Declaramos alguna variables

 long secuencia[20];           // Array que alberga la secuencia
  int contador = 0;            // Contador
  long input = 5;              // Indicador de boton pulsado
  int despliegue = 500;        // Retraso segun la secuencia se incrementa
  int puntuacion_alta = 20;    // Puntuación máxima donde acaba el juego 

  // Declaramos algunas variables para los efectos musicales
  int length = 15;                  // Numero de notas de la melodia
  char notas[] = "ccggaagffeeddc "; // Notas de la melodia (cada letra es una nota distinta)
  int tiempos[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };  // Duracion de cada tono en un array
  int tiempo = 100;  //Tempo de la melodia

  void setup() {
 // Entradas
  pinMode(led_rojo, OUTPUT);      
  pinMode(led_verde, OUTPUT); 
  pinMode(led_amarillo, OUTPUT); 
  pinMode(led_azul, OUTPUT); 
  pinMode(zumbador, OUTPUT);

   // Salidas
  pinMode(boton_rojo, INPUT);    
  pinMode(boton_verde, INPUT);
  pinMode(boton_amarillo, INPUT);
  pinMode(boton_azul, INPUT);

// Resistencias de pullup, ya que los botones son normalmente abiertos
  digitalWrite(boton_rojo, HIGH);
  digitalWrite(boton_verde, HIGH);
  digitalWrite(boton_amarillo, HIGH);
  digitalWrite(boton_azul, HIGH);

// Melodia al inicio    
  melodia();
  }

//Ciclo de repeticion 
  void loop() {
  ver_secuencia();  // Reproduce la sequencia
  recibir_secuencia();     // Lee la sequencia
  delay(1000);          // Espera 1 segundo
  }

  // Funcion para definir las notas y sus frecuencias
  void playnota(char nota, int duracion) {
  char nombres[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int tonos[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  for (int i = 0; i < 8; i++) {
     if (nombres[i] == nota) {
       playnota(tonos[i], duracion);
     }
  }
  }


  //Funcion para definir las notas segun la duración y el tono
  void playnota(int tono, int duracion) {
    for (long i = 0; i < duracion * 1000L; i += tono *2) {
      digitalWrite(zumbador, HIGH);
      delayMicroseconds(tono);
      digitalWrite(zumbador, LOW);
      delayMicroseconds(tono);
    }
  }

  // Funciones para encender los leds y reproducir el tono correspondiente
  void destello_rojo() {
  digitalWrite(led_rojo, HIGH);
  playnota(2273,despliegue);            
  digitalWrite(led_rojo, LOW);
  }

   void destello_azul() {
  digitalWrite(led_azul, HIGH);
  playnota(1700,despliegue);            
  digitalWrite(led_azul, LOW);
  }

  void destello_amarillo() {
  digitalWrite(led_amarillo, HIGH);
  playnota(1275,despliegue);             
  digitalWrite(led_amarillo, LOW);
  } 

  void destello_verde() {
  digitalWrite(led_verde, HIGH);
  playnota(1136,despliegue);             
  digitalWrite(led_verde, LOW);
  }

  // Funcion para mostrar que botón se tenia que pulsar en caso de error del jugador
  void boton_correcto(long led) {
    switch (led) {
        case 0:
          destello_rojo();
          break;
        case 1:
          destello_verde();
          break;
        case 2:
          destello_amarillo();
          break;
        case 3:
          destello_azul();
          break;
      }
      delay(50);
  }

   // Función que reproduce la canción al arrancar el arduino y para el juego cuando se llega a la puntuacion maxima
  void melodia() {
  digitalWrite(led_rojo, HIGH);       
  digitalWrite(led_verde, HIGH);
  digitalWrite(led_amarillo, HIGH);
  digitalWrite(led_azul, HIGH);

   for (int i = 0; i < length; i++) {
   if (notas[i] == ' ') {
     delay(tiempos[i] * tiempo); // rest
   } else {
     playnota(notas[i], tiempos[i] * tiempo);
   }
   delay(tiempo / 2); 
  }

delay(1000);   
  digitalWrite(led_rojo, LOW);      
  digitalWrite(led_verde, LOW);
  digitalWrite(led_amarillo, LOW);
  digitalWrite(led_azul, LOW);
  reinicio_contador();                    
  }

  // Reseteamos contadores
  void reinicio_contador() {
  contador = 0;
  despliegue = 500;
  }

 // Funcion para crear y reproducir los patrones
  void ver_secuencia(){
  
  // Con esto hacemos que la función Random sea aun mas aleatoria
  randomSeed(analogRead(8));

   secuencia[contador] = random(4);       
    for (int i = 0; i < contador; i++) {  
      boton_correcto(secuencia[i]);             
    }
  despliegue = 500 - (contador * 15);        
  contador++;                          
  }

   // Funcion para leer los botones que pulsa el jugador
 void recibir_secuencia() {
   for (int i=1; i < contador; i++) {              
      while (input==5){                          
        if (digitalRead(boton_rojo) == LOW) {    
          input = 0;
        }
        if (digitalRead(boton_verde) == LOW) {  
          input = 1;
        }
        if (digitalRead(boton_amarillo) == LOW) {
          input = 2;
        }
        if (digitalRead(boton_azul) == LOW) {   
          input = 3;
        }
      }

  if (secuencia[i-1] == input) {              
        boton_correcto(input);                           
        if (i == puntuacion_alta) {                        
          melodia();                        
        }
      }    

      else {
          playnota(4545,1500);                  
          delay(500);
          boton_correcto(secuencia[i-1]);                 
          boton_correcto(secuencia[i-1]);                 
          boton_correcto(secuencia[i-1]);
          delay(1000);
          melodia();
          reinicio_contador();                          
      } 
    input = 5;                                   
    }
  }  
