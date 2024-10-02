#include <stdio.h> // Operaciones de entrada y salida (I/O), como leer y escribir en la consola, archivos, etc.
#include <stdlib.h> // Funciones para la gestión de memoria dinámica, control de procesos, conversiones de tipo y otras utilidades generales.
#include <time.h> // Funciones para manipular y obtener la hora y fecha del sistema.

//definicion de macros
#define CANT_DADOS 5
#define CANT_LANZAMIENTOS 3
#define TURNOSMULTIJUGADOR 22
#define MULTIJUGADOR 2
#define CATEGORIAS 11


char nombreJ1 [15];
char nombreJ2 [15];


void modoJuego (int formaJuego, int dados [], int turno, int jugadasUsadas[], int jugadasUsadasMulti[MULTIJUGADOR][CATEGORIAS], int tabla[], int puntosTotales,int tablaMulti[MULTIJUGADOR][CATEGORIAS], int puntosTotalesJ1, int puntosTotalesJ2);

void lanzamientos (int dados[], int turno, int jugadasUsadas[], int tabla[], int puntosTotales);
void lanzaDados (int dados []);
void mostrarDados (int dados []);
void relanzarDados (int dados []);
void mostrarTabla(char nombreJ1[], int turno, int tabla[], int puntosTotales);
void anotarJugada (int dados[], int anotar, int tabla[]);
void jugadasPosibles (int dados[],int turno, int jugadasUsadas[], int tabla[]);
void reset(int dados[], int turno, int jugadasUsadas[], int tabla[], int puntosTotales);

void lanzamientosMulti (int dados[], int turno, int jugadasUsadasMulti[MULTIJUGADOR][CATEGORIAS], int tablaMulti[MULTIJUGADOR][CATEGORIAS], int puntosTotalesJ1, int puntosTotalesJ2);
void jugadasPosiblesMulti (int dados[], int turno, int jugadasUsadasMulti[MULTIJUGADOR][CATEGORIAS], int tablaMulti[MULTIJUGADOR][CATEGORIAS]);
void anotarJugadaMulti(int dados[], int turno, int jugadasUsadas[MULTIJUGADOR][CATEGORIAS], int anotar, int tablaMulti[MULTIJUGADOR][CATEGORIAS]);
void mostrarTablaMulti(char nombreJ1[],char nombreJ2[], int turno, int tablaMulti[MULTIJUGADOR][CATEGORIAS], int puntosTotalesJ1, int puntosTotalesJ2);
void resetMulti(int dados[], int turno, int jugadasUsadasMulti[MULTIJUGADOR][CATEGORIAS], int tablaMulti[MULTIJUGADOR][CATEGORIAS], int puntosTotalesJ1, int puntosTotalesJ2);

int juegoUno (int dados[]);
int juegoDos (int dados[]);
int juegoTres (int dados[]);
int juegoCuatro (int dados[]);
int juegoCinco (int dados[]);
int juegoSeis (int dados[]);
int juegoEscalera (int dados[]);
int juegoFull (int dados[]);
int juegoPoker (int dados[]);
int juegoGenerala (int dados[]);
int juegoDobleGenerala (int dados[]);



int main () {
  
  srand (time(NULL)); // Inicializa el generador de números aleatorios.
 
  int formaJuego;
  int turno;
  int dados [CANT_DADOS];
  int lanzamiento = 1;
  int relanzar;
  int tabla [CATEGORIAS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int puntosTotales;

  int jugadasUsadas [CATEGORIAS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int jugadasUsadasMulti [MULTIJUGADOR][CATEGORIAS] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}; 
  // Checkea si fue anotado en la tabla (0 No, 1 Si).

  int puntosTotalesJ1;
  int puntosTotalesJ2;
  int tablaMulti[MULTIJUGADOR][CATEGORIAS] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

  modoJuego(formaJuego, dados, turno, jugadasUsadas, jugadasUsadasMulti, tabla, puntosTotales, tablaMulti, puntosTotalesJ1, puntosTotalesJ2);

  return 0;
}

void modoJuego (int formaJuego, int dados[], int turno, int jugadasUsadas[], int jugadasUsadasMulti[MULTIJUGADOR][CATEGORIAS], int tabla[], int puntosTotales, int tablaMulti[MULTIJUGADOR][CATEGORIAS], int puntosTotalesJ1, int puntosTotalesJ2) {
  
  printf("'Generala 2024'\n");

  // Variables para calcular tiempo jugado.
  time_t inicio_juego, fin_juego;
  
      //Inicio del "cronometro" similar a srand.
      inicio_juego = time(NULL);
  do {
    printf("* Presione 1 para jugar de forma individual.\n");
    printf("* Presione 2 para jugar de forma multijugador.\n");
    printf("* Presione 0 para salir.\n\n");
    scanf("%d", &formaJuego);

    if (formaJuego == 1) {
      printf("*Juego individual*\n");
      printf("Bienvenid@, ingrese su nombre: ");
      scanf("%s", &nombreJ1);
      lanzamientos(dados, turno, jugadasUsadas, tabla, puntosTotales);
    } else if (formaJuego == 2) {
      printf("*Juego multijugador*\n"); 
      printf("Hola jugador 1, Ingrese su Nombre: \n");
      scanf("%s", &nombreJ1);
      printf("\nHola jugador 2, Ingrese su Nombre: \n");
      scanf("%s", &nombreJ2);
      lanzamientosMulti(dados, turno, jugadasUsadasMulti, tablaMulti, puntosTotalesJ1, puntosTotalesJ2);
    } else if (formaJuego == 0) {
      printf("\nLamentablemente no todo es ocio, te esperamos la proxima!\n");
      exit (0);
    } else {
      printf("\n\n** Valor ingresado no admitido. **\n");
    }
  }  while (formaJuego < 0 || formaJuego > 2);  // El Bucle se ejecuta siempre que la variable sea menor a 0 o mayor a 2.

  fin_juego = time(NULL);

  // Calcular el tiempo transcurrido con difftime.

  int duracion_partida = difftime(fin_juego, inicio_juego);

  printf("La partida tuvo una duracion de: %d minutos.\n", duracion_partida / 60);
  printf("\n");

}


void lanzamientos (int dados[], int turno, int jugadasUsadas[], int tabla[], int puntosTotales) {
  int lanzamiento = 1;
  int relanzar;
  int anotar;

  for (turno = 1; turno <= CATEGORIAS; turno++) {
    lanzaDados (dados);
    for (lanzamiento = 1; lanzamiento <= CANT_LANZAMIENTOS; lanzamiento++){
      if (lanzamiento >= 1) {
        do {
          printf("\n\nJugador: %s", nombreJ1);
          printf ("\nTurno nro: %d", turno);
          printf("\nLanzamiento nro: %d", lanzamiento);
          mostrarDados (dados);
          printf("<|> Presione 1 para relanzar dados.\n<|> Presione 0 para elegir una jugada.\n\n** Si quiere reiniciar la partida presione 5 **\n** Si quiere abandonar la partida presione 9 **\n");
          scanf("%d", &relanzar);
          if(relanzar == 5){
            reset(dados, turno, tabla, jugadasUsadas, puntosTotales);
          }
          if (relanzar == 9) {
            printf("Gracias por jugar %s. Te esperamos la proxima!\n", nombreJ1);
            exit (0);
          }
        } while(relanzar < 0 || relanzar > 1);
        if (relanzar == 1) {
          relanzarDados(dados);
        } else if (relanzar == 0) {
          jugadasPosibles(dados, turno, jugadasUsadas, tabla);
          break;
        } else {
          printf("\n\n** Valor ingresado no admitido. **");
        }
        if (lanzamiento == 3) {
          mostrarDados (dados);
          jugadasPosibles (dados, turno, jugadasUsadas, tabla);
        }
      }
    }

  
    if (turno <= CATEGORIAS) {
      mostrarTabla(nombreJ1, turno, tabla, puntosTotales);
    }

    if (turno < CATEGORIAS){
      printf("\n* Siguiente turno -->");
    }
  }
}


void lanzaDados (int dados []) {  // Crea una nueva tirada entera de dados.
  for (int i = 0; i < CANT_DADOS; i++) {
    dados[i] = (rand() % 6) + 1;
  }
}


void mostrarDados (int dados []) {  // Muestra los dados almacenados al momento que es llamada la funcion "mostrarDados(dados)".
  printf ("\n- Dados:\n");
  for (int i = 0; i < CANT_DADOS; i++) {
    printf("[%d]  ", dados[i]);
  }
  printf("\n");
}


void relanzarDados (int dados[]) {
  int relanzar = 1;
  int lanzamiento = 1;
  mostrarDados (dados); // Muestra los dados al momento que es llamada, en este caso serian los de la tirada original.
 
 
  while (relanzar != 1 && relanzar != 0) {  // Condiciona a poner solo 1 o 0, si quiere relanzar los dados si o no.
    printf("** Valor ingresado no admitido. **\n");
    printf("<|> Presione 1 para relanzar dados.\n<|> Presione 0 para elegir una jugada.\n"); 
    scanf("%d", &relanzar);
    mostrarDados (dados);
  }

  int seleccion[CANT_DADOS] = {0};
  printf("* Responda por cada dado:\n1) Si lo quiere relanzar.  0)Si lo quiere conservar.\n");
  for (int i = 0; i < CANT_DADOS; i++) {  // Recorre los dados uno por uno si los quiere relanzar o no.
    printf("\n.Dado nro %d --> [%d]. Quiere volver a lanzarlo? ", i + 1, dados[i]);
    scanf("%d", &seleccion[i]);
    while (seleccion[i] != 0 && seleccion[i] != 1) {  // Condiciona a que solo ponga 1 o 0.
      printf("\n** Valor ingresado no admitido. Por favor ingrese 1 para relanzar o 0 para no relanzar. **\n");
      printf(".Dado nro %d --> [%d]. Quiere volver a lanzarlo? ", i + 1, dados[i]);
      scanf("%d", &seleccion[i]); 
      // Solicitar nueva entrada.  
    }

    if (seleccion[i] == 1) { // SOLO PARA CONTROL, de que le cargue los valores 0 o 1 a cada dado como decision de relanzarlo o no.
      printf("Dado nro %d relanzado.\n", i + 1, dados[i]);
    } else {
      printf("Dado nro %d no relanzado.\n", i + 1, dados[i]);
    } 
    
    for (int i = 0; i < CANT_DADOS; i++) { // Relanza solo los dados seleccionados con el 1.

      
      if (seleccion[i] == 1) {
        dados[i] = (rand() % 6) + 1;
      }
    }
  }
}


int juegoUno (int dados[]){
  int suma = 0;
  for(int i = 0; i < CANT_DADOS; i++){
    if(dados[i] == 1){
      suma += 1;
    }
  }
  return suma;
}

int juegoDos (int dados[]){
  int suma = 0;
  for(int i = 0; i < CANT_DADOS; i++){
    if(dados[i] == 2){
      suma += 2;
    }
  }
  return suma;
}

int juegoTres (int dados[]){
  int suma = 0;
  for(int i = 0; i < CANT_DADOS; i++){
    if(dados[i] == 3){
      suma += 3;
    }
  }
  return suma;
}

int juegoCuatro (int dados[]){
  int suma = 0;
  for(int i = 0; i < CANT_DADOS; i++){
    if(dados[i] == 4){
      suma += 4;
    }
  }
  return suma;
}

int juegoCinco (int dados[]){
  int suma = 0;
  for(int i = 0; i < CANT_DADOS; i++){
    if(dados[i] == 5){
      suma += 5;
    }
  }
  return suma;
}

int juegoSeis (int dados[]){
  int suma = 0;
  for(int i = 0; i < CANT_DADOS; i++){
    if(dados[i] == 6){
      suma += 6;
    }
  }
  return suma;
}

int juegoEscalera (int dados[]){  // {1, 2, 3, 4, 5} ó {2, 3, 4, 5, 6}.


  int cumple[5] = {0, 0, 0, 0, 0};  // Variable para determinar si se cumple tener uno de los dados necesarios.

  int puntaje = 0;  //Puntaje que va a dar (0 si no cumple, 35 si se cumple)

  for(int i = 0; i < CANT_DADOS; i++){
    if(dados[i] == 2 && cumple[0] == 0){
      cumple[0] = 1;

    }else if(dados[i] == 3 && cumple[1] == 0){
      cumple[1] = 1;

    }else if(dados[i] == 4 && cumple[2] == 0){
      cumple[2] = 1;

    }else if(dados[i] == 5 && cumple[3] == 0){
      cumple[3] = 1;

    }else if((dados[i] == 1 || dados[i] == 6) && cumple[4] == 0){
      cumple[4] = 1;
    }
  }

  for(int i = 0; i < 5; i++){
    puntaje += cumple[i];
  }

  // Puntajes.
  if(puntaje == 5){
    return 35;
  }else{
    return 0;
  }
}

int juegoFull (int dados[]){
  // Tres dados iguales + otros dos dados iguales.

  int cumpleCond1 = 0; // Condicion de tener 3 dados iguales.
  int cumpleCond2 = 0; // Condicion de tener otros 2 dados iguales.

  for(int i = 0; i < CANT_DADOS; i++){
    for(int j = 0; j < CANT_DADOS; j++){
      if(dados[i] == dados[j]){
        cumpleCond1++;
      }
      if(cumpleCond1 == 3){  //En el caso de que cumpla con la primer condicion
        for(int x = 0; x < CANT_DADOS; x++){
          for(int y = 0; y < CANT_DADOS; y++){
            if(dados[i] != dados[x] && dados[x] == dados[y]){
              cumpleCond2++;
            }
            if(cumpleCond2 == 2){
              return 50;
             // Puntaje si se cumplen ambas condiciones.
            }
          }
          cumpleCond2 = 0;
        }
      }
    }
        // Resetea.
    cumpleCond1 = 0;
    cumpleCond2 = 0;
  }
  return 0;
  // Puntaje si no se cumplen las condiciones.
}

int juegoPoker (int dados[]){
  // Cuatro dados iguales.

  int cumpleCond1 = 0; 
  //Condicion de tener 3 dados iguales
  int cumpleCond2 = 0;
  //Condicion de tener otros 2 dados iguales

  for(int i = 0; i < CANT_DADOS; i++){
    for(int j = 0; j < CANT_DADOS; j++){
      if(dados[i] == dados[j]){
        cumpleCond1++;
      }
      if(cumpleCond1 == 4){
        //En el caso de que cumpla con la primer condicion 

        for(int x = 0; x < CANT_DADOS; x++){
          for(int y = 0; y < CANT_DADOS; y++){
            if(dados[i] != dados[x] && dados[x] == dados[y]){
              cumpleCond2++;
            }
            if(cumpleCond2 == 1){
              return 75;
              //Puntaje si se cumplen las condiciones
            }
          }
          cumpleCond2 = 0;
        }
      }
    }
    //Resetea
    cumpleCond1 = 0;
    cumpleCond2 = 0;
  }
  return 0;
  //Puntaje si no se cumplen las condiciones
}

int juegoGenerala (int dados[]){
  //Todos los dados iguales

  int cumple = 0;

  for(int i = 0; i < CANT_DADOS; i++){
    if(dados[0] == dados[i]){
      cumple++;
    }
    if(cumple == 5){
      return 100;
      //Puntaje si se cumplen las condiciones
    }
  }
  return 0;
  //Puntaje si no se cumplen las condiciones
}

int juegoDobleGenerala (int dados[]){
  //Todos los dados iguales + haber hecho generala

  int cumple = 0;

  for(int i = 0; i < CANT_DADOS; i++){
    if(dados[0] == dados[i]){
      cumple++;
    }
    if(cumple == 5){
      return 120;
      //Puntaje si se cumplen las condiciones
    }
  }
  return 0;
  //Puntaje si no se cumplen las condiciones
}

void jugadasPosibles (int dados[], int turno, int jugadasUsadas[], int tabla[]){
  int anotar;
 
 


  do{
    printf("\nIngrese el numero de la jugada que desea realizar:\n");

    if (jugadasUsadas[0] == 0){
    if(juegoUno(dados)){
      printf("1) Anotar %d en Uno.\n", juegoUno(dados));


    }else{
      printf("1) Tachar Uno.\n");
    }
    }




    if(jugadasUsadas[1] == 0)
    {
    if(juegoDos(dados)){
      printf("2) Anotar %d en Dos.\n", juegoDos(dados));
    }else{
      printf("2) Tachar Dos.\n");
    }
    }




   if(jugadasUsadas[2] == 0)
   {
    if(juegoTres(dados)){
      printf("3) Anotar %d en Tres.\n", juegoTres(dados));
    }else {
      printf("3) Tachar Tres.\n");
    }
   }




     if(jugadasUsadas[3] == 0) 
     {
    if(juegoCuatro(dados)){
      printf("4) Anotar %d en Cuatro.\n", juegoCuatro(dados));
    }else {
      printf("4) Tachar Cuatro.\n");
    }
     }




     if(jugadasUsadas[4] == 0) {
    if(juegoCinco(dados)){
      printf("5) Anotar %d en Cinco.\n", juegoCinco(dados));
    }else {
      printf("5) Tachar Cinco.\n");
    }
     }




     if(jugadasUsadas[5] == 0) {
    if(juegoSeis(dados)){
      printf("6) Anotar %d en Seis.\n", juegoSeis(dados));
    }else {
      printf("6) Tachar Seis.\n");
    }
     }




     if(jugadasUsadas[6] == 0) {
    if(juegoEscalera(dados)){
      printf("7) Anotar %d en Escalera.\n", juegoEscalera(dados));
    }else {
      printf("7) Tachar Escalera.\n");
    }
     }




     if(jugadasUsadas[7] == 0) {
    if(juegoFull(dados)){
      printf("8) Anotar %d en Full.\n", juegoFull(dados));
    }else {
      printf("8) Tachar Full.\n");
    }
     }




     if(jugadasUsadas[8] == 0) {
    if(juegoPoker(dados)){
      printf("9) Anotar %d en Poker.\n", juegoPoker(dados));
    }else {
      printf("9) Tachar Poker.\n");
    }
     }



     if(jugadasUsadas[9] == 0) {
    if(juegoGenerala(dados)){
      printf("10) Anotar %d en Generala.\n", juegoGenerala(dados));
    }else {
      printf("10) Tachar Generala.\n");
    }
     }
      


      if(jugadasUsadas[9] == 1 && jugadasUsadas[10] == 0 ){
      if(juegoDobleGenerala(dados)){

        printf("11) Anotar %d en Doble Generala.\n", juegoDobleGenerala(dados));

      }else {
        printf("11) Tachar Doble Generala.\n");

      }
    }else if (jugadasUsadas[10] == 0) {
      printf("11) Tachar Doble Generala.\n");
    }





    scanf("%d", &anotar);
    if ((anotar < 1 || anotar > 11) || (jugadasUsadas[anotar - 1] == 1)){

      printf("**Valor ingresado no admitido. Ingrese una jugada posible.**\n");

    }

  } while ((anotar < 1 || anotar > 11) || (jugadasUsadas[anotar - 1] == 1));

  jugadasUsadas[anotar - 1] = 1;

  anotarJugada(dados, anotar, tabla);

}

void anotarJugada(int dados[], int anotar, int tabla[]){
  

  switch(anotar){

    case 1:
      tabla[0] = juegoUno(dados);
      printf("Se han cargado %d puntos\n", juegoUno(dados));
      break;

    case 2:
      tabla[1] = juegoDos(dados);
      printf("Se han cargado %d puntos\n", juegoDos(dados));
      break;

    case 3:
      tabla[2] = juegoTres(dados);
      printf("Se han cargado %d puntos\n", juegoTres(dados));
      break;

    case 4:
      tabla[3] = juegoCuatro(dados);
      printf("Se han cargado %d puntos\n", juegoCuatro(dados));
      break;

    case 5:
      tabla[4] = juegoCinco(dados);
      printf("Se han cargado %d puntos\n", juegoCinco(dados));
      break;

    case 6:
      tabla[5] = juegoSeis(dados);
      printf("Se han cargado %d puntos\n", juegoSeis(dados));
      break;

    case 7:
      tabla[6] = juegoEscalera(dados);
      printf("Se han cargado %d puntos\n", juegoEscalera(dados));
      break;

    case 8:
      tabla[7] = juegoFull(dados);
      printf("Se han cargado %d puntos\n", juegoFull(dados));
      break;

    case 9:
      tabla[8] = juegoPoker(dados);
      printf("Se han cargado %d puntos\n", juegoPoker(dados));
      break;

    case 10:
      tabla[9] = juegoGenerala(dados);
      printf("Se han cargado %d puntos\n", juegoGenerala(dados));
      break;

    case 11:
      tabla[10] = juegoDobleGenerala(dados);
      printf("Se han cargado %d puntos\n", juegoDobleGenerala(dados));
      break;
  }
}

void mostrarTabla(char nombreJ1[], int turno, int tabla[], int puntosTotales){

  puntosTotales = 0;
  for(int i = 0; i < CATEGORIAS; i++){
    puntosTotales += tabla[i];
  }

  printf("\nTabla de puntajes del jugador 1: %s\n", nombreJ1);
  printf("1)Juego Uno: %d\n", tabla[0]);
  printf("2)Juego Dos: %d\n", tabla[1]);
  printf("3)Juego Tres: %d\n", tabla[2]);
  printf("4)Juego Cuatro: %d\n", tabla[3]);
  printf("5)Juego Cinco: %d\n", tabla[4]);
  printf("6)Juego Seis: %d\n", tabla[5]);
  printf("7) Escalera: %d\n", tabla[6]);
  printf("8)Juego Full: %d\n", tabla[7]);
  printf("9)Juego Poker: %d\n", tabla[8]);
  printf("10)Juego Generala: %d\n", tabla[9]);
  printf("11)Juego Doble Generala: %d\n", tabla[10]);

  printf("\nJugador: %s\nPuntos: %d\n\n", nombreJ1, puntosTotales);

  if (turno == CATEGORIAS) {
    printf("El jugador %s ha terminado la partida con %d puntos. Bien hecho!\n", nombreJ1, puntosTotales);

    if(puntosTotales < 490 && puntosTotales > 360){
      printf("Rango de Puntaje 360 - 490 --> El desempeño del jugador 1 %s ha sido Excelente!\n", nombreJ1);
    }else if(puntosTotales < 360 && puntosTotales > 240){
      printf("Rango de Puntaje 240 - 360 --> El desempeño del jugador 1 %s ha sido Bueno.\n", nombreJ1);
    }else if(puntosTotales < 240 && puntosTotales > 120){
      printf("Rango de Puntaje 120 - 240 --> El desempeño del jugador 1 %s ha sido Regular.\n", nombreJ1);
    }else{
      printf("Rango de Puntaje menor a 120 --> El desempeño del jugador 1 %s ha sido Malo.\n", nombreJ1);
    }
    printf("\n");
  }
}

void reset (int dados[], int turno, int jugadasUsadas[], int tabla[], int puntosTotales) {
    // Reiniciamos la tabla de puntajes del jugador a 0.
  for (int i = 0; i < CATEGORIAS; i++) {
    tabla[i] = 0;
  }

  for (int i = 0; i < CATEGORIAS; i++){
  jugadasUsadas[i] = 0;
  }
  puntosTotales = 0;
  turno = 0;

    // Mostrar un mensaje para indicar que el juego ha sido reseteado.
  printf("\n** Juego reseteado para el jugador %s. **\n", nombreJ1);
  printf("*** Turnos y puntajes han sido reiniciados. ***\n\n");


  // Variables para tiempo.
  time_t inicio_juego, fin_juego;


  // Inicio del "cronometro" similar a srand.
      inicio_juego = time(NULL);

  lanzamientos(dados, turno, jugadasUsadas, tabla, puntosTotales);

  fin_juego = time(NULL);

  // Calcular el tiempo con difftime.

  int duracion_partida = difftime(fin_juego, inicio_juego);

  printf("La partida tuvo una duracion de: %d minutos.\n", duracion_partida / 60);
  printf("\n");


  exit(0);
}






void lanzamientosMulti (int dados[], int turno, int jugadasUsadasMulti[MULTIJUGADOR][CATEGORIAS], int tablaMulti[MULTIJUGADOR][CATEGORIAS], int puntosTotalesJ1, int puntosTotalesJ2) {

  int lanzamiento = 1;
  int relanzar;
  int anotar;

  for (turno = 1; turno <= TURNOSMULTIJUGADOR; turno++) {
    if (turno %2 != 0) {

      lanzaDados (dados);

      for (lanzamiento = 1; lanzamiento <= CANT_LANZAMIENTOS; lanzamiento++){
        if (lanzamiento >= 1) {
          do {
            printf("\n\nJugador 1: %s", nombreJ1);
            printf ("\nTurno nro: %d", turno);
            printf("\nLanzamiento nro: %d", lanzamiento);
            mostrarDados (dados);
            printf("<|> Presione 1 para relanzar dados.\n<|> Presione 0 para elegir una jugada.\n\n** Si quiere reiniciar la partida presione 5 **\n** Si quiere abandonar la partida presione 9 **\n");
            scanf("%d", &relanzar);
            if(relanzar == 5){
            resetMulti(dados, turno, jugadasUsadasMulti, tablaMulti, puntosTotalesJ1, puntosTotalesJ2);
            }
            if(relanzar == 9) {
              printf("Gracias por jugar %s y %s. Los esperamos la proxima!\n", nombreJ1, nombreJ2);
              exit (0);
            }

          } while(relanzar < 0 || relanzar > 1);

          if (relanzar == 1) {

            relanzarDados(dados);

          } else if (relanzar == 0) {

            jugadasPosiblesMulti(dados, turno, jugadasUsadasMulti, tablaMulti);
            break;

          } else {

            printf("\n\n** Valor ingresado no admitido. **");

          }

          if (lanzamiento == 3) {
            mostrarDados (dados);
            jugadasPosiblesMulti(dados, turno, jugadasUsadasMulti, tablaMulti);

          }
        }
      }

      if (turno < TURNOSMULTIJUGADOR) {

        mostrarTablaMulti(nombreJ1, nombreJ2, turno, tablaMulti, puntosTotalesJ1, puntosTotalesJ2);
        printf("\n* Siguiente turno -->");

      }

      if (turno == TURNOSMULTIJUGADOR){
        mostrarTablaMulti(nombreJ1, nombreJ2, turno, tablaMulti, puntosTotalesJ1, puntosTotalesJ2);

      }

    } else if (turno %2 == 0) {

      lanzaDados (dados);

      for (lanzamiento = 1; lanzamiento <= CANT_LANZAMIENTOS; lanzamiento++){

        if (lanzamiento >= 1) {
          do {
            printf("\n\nJugador 2: %s", nombreJ2);
            printf ("\nTurno nro: %d", turno);
            printf("\nLanzamiento nro: %d", lanzamiento);
            mostrarDados (dados);
            printf("<|> Presione 1 para relanzar dados.\n<|> Presione 0 para elegir una jugada.\n\n** Si quiere reiniciar la partida presione 5 **\n** Si quiere abandonar la partida presione 9 **\n");
            scanf("%d", &relanzar);
            if(relanzar == 5){
            resetMulti(dados, turno, jugadasUsadasMulti, tablaMulti, puntosTotalesJ1, puntosTotalesJ2);
            }
            if (relanzar == 9){
              printf("Gracias por jugar %s y %s. Los esperamos la proxima!\n", nombreJ1, nombreJ2);
              exit (0);
            }

          } while(relanzar < 0 || relanzar > 1);

       if (relanzar == 1) { 
        
        relanzarDados(dados); 
       
       } else if (relanzar == 0) { 
        
        jugadasPosiblesMulti(dados, turno, jugadasUsadasMulti, tablaMulti);
        break; 
          } else { 

            printf("\n\n** Valor ingresado no admitido. **");

          }

          if (lanzamiento == 3) {
            mostrarDados (dados);
            jugadasPosiblesMulti (dados, turno, jugadasUsadasMulti, tablaMulti);
          }
        }
      }
      if (turno < TURNOSMULTIJUGADOR) {
        mostrarTablaMulti(nombreJ1, nombreJ2, turno, tablaMulti, puntosTotalesJ1, puntosTotalesJ2);
        printf("\n* Siguiente turno -->");

      }

      if (turno == TURNOSMULTIJUGADOR){

        mostrarTablaMulti(nombreJ1, nombreJ2, turno, tablaMulti, puntosTotalesJ1, puntosTotalesJ2);

      }
    }
  }

  if (turno < TURNOSMULTIJUGADOR) {
    mostrarTablaMulti(nombreJ1, nombreJ2, turno, tablaMulti, puntosTotalesJ1, puntosTotalesJ2);
    printf("\n* Siguiente turno -->");
  }

  if (turno == TURNOSMULTIJUGADOR){
    mostrarTablaMulti(nombreJ1, nombreJ2, turno, tablaMulti, puntosTotalesJ1, puntosTotalesJ2);
  }
}

void jugadasPosiblesMulti (int dados[], int turno, int jugadasUsadasMulti[MULTIJUGADOR][CATEGORIAS], int tablaMulti[MULTIJUGADOR][CATEGORIAS]){
  int anotar;

if (turno %2 != 0) {
  do{
    printf("\nIngrese el numero de la jugada que desea realizar:\n");

    if (jugadasUsadasMulti[0][0] == 0)
    {
    if(juegoUno(dados)){
      printf("1) Anotar %d en Uno.\n", juegoUno(dados));


    }else{
      printf("1) Tachar Uno.\n");
    }
    }




    if (jugadasUsadasMulti[0][1] == 0)
    {
    if(juegoDos(dados)){
      printf("2) Anotar %d en Dos.\n", juegoDos(dados));
    }else{
      printf("2) Tachar Dos.\n");
    }
    }




   if (jugadasUsadasMulti[0][2] == 0)
   {
    if(juegoTres(dados)){
      printf("3) Anotar %d en Tres.\n", juegoTres(dados));
    }else {
      printf("3) Tachar Tres.\n");
    }
   }




   if (jugadasUsadasMulti[0][3] == 0) 
     {
    if(juegoCuatro(dados)){
      printf("4) Anotar %d en Cuatro.\n", juegoCuatro(dados));
    }else {
      printf("4) Tachar Cuatro.\n");
    }
     }




    if (jugadasUsadasMulti[0][4] == 0) 
    {
    if(juegoCinco(dados)){
      printf("5) Anotar %d en Cinco.\n", juegoCinco(dados));
    }else {
      printf("5) Tachar Cinco.\n");
    }
     }




    if (jugadasUsadasMulti[0][5] == 0) 
     {
    if(juegoSeis(dados)){
      printf("6) Anotar %d en Seis.\n", juegoSeis(dados));
    }else {
      printf("6) Tachar Seis.\n");
    }
     }




    if (jugadasUsadasMulti[0][6] == 0)
    {
    if(juegoEscalera(dados)){
      printf("7) Anotar %d en Escalera.\n", juegoEscalera(dados));
    }else {
      printf("7) Tachar Escalera.\n");
    }
     }




    if (jugadasUsadasMulti[0][7] == 0)
    {
    if(juegoFull(dados)){
      printf("8) Anotar %d en Full.\n", juegoFull(dados));
    }else {
      printf("8) Tachar Full.\n");
    }
     }




     if (jugadasUsadasMulti[0][8] == 0)
    {
    if(juegoPoker(dados)){
      printf("9) Anotar %d en Poker.\n", juegoPoker(dados));
    }else {
      printf("9) Tachar Poker.\n");
    }
     }



    if (jugadasUsadasMulti[0][9] == 0)
    {
    if(juegoGenerala(dados)){
      printf("10) Anotar %d en Generala.\n", juegoGenerala(dados));
    }else {
      printf("10) Tachar Generala.\n");
    }
     }
      


      if(jugadasUsadasMulti[0][9] == 1 && jugadasUsadasMulti[0][10] == 0 ){
      if(juegoDobleGenerala(dados)){

        printf("11) Anotar %d en Doble Generala.\n", juegoDobleGenerala(dados));

      }else {
        printf("11) Tachar Doble Generala.\n");

      }
    }else if (jugadasUsadasMulti[0][10] == 0) {
      printf("11) Tachar Doble Generala.\n");
    }





    scanf("%d", &anotar);
    if ((anotar < 1 || anotar > 11) || (jugadasUsadasMulti[0][anotar - 1] == 1)){

      printf("Valor ingresado no admitido. Ingresa una jugada posible.\n");

    }

  } while ((anotar < 1 || anotar > 11) || (jugadasUsadasMulti[0][anotar - 1] == 1));

}


if (turno %2 == 0) {
  do{
    printf("\nIngrese el numero de la jugada que desea realizar:\n");

    if (jugadasUsadasMulti[1][0] == 0)
    {
    if(juegoUno(dados)){
      printf("1) Anotar %d en Uno.\n", juegoUno(dados));


    }else{
      printf("1) Tachar Uno.\n");
    }
    }




    if (jugadasUsadasMulti[1][1] == 0)
    {
    if(juegoDos(dados)){
      printf("2) Anotar %d en Dos.\n", juegoDos(dados));
    }else{
      printf("2) Tachar Dos.\n");
    }
    }




   if (jugadasUsadasMulti[1][2] == 0)
   {
    if(juegoTres(dados)){
      printf("3) Anotar %d en Tres.\n", juegoTres(dados));
    }else {
      printf("3) Tachar Tres.\n");
    }
   }




   if (jugadasUsadasMulti[1][3] == 0) 
     {
    if(juegoCuatro(dados)){
      printf("4) Anotar %d en Cuatro.\n", juegoCuatro(dados));
    }else {
      printf("4) Tachar Cuatro.\n");
    }
     }




    if (jugadasUsadasMulti[1][4] == 0) 
    {
    if(juegoCinco(dados)){
      printf("5) Anotar %d en Cinco.\n", juegoCinco(dados));
    }else {
      printf("5) Tachar Cinco.\n");
    }
     }




    if (jugadasUsadasMulti[1][5] == 0) 
     {
    if(juegoSeis(dados)){
      printf("6) Anotar %d en Seis.\n", juegoSeis(dados));
    }else {
      printf("6) Tachar Seis.\n");
    }
     }




    if (jugadasUsadasMulti[1][6] == 0)
    {
    if(juegoEscalera(dados)){
      printf("7) Anotar %d en Escalera.\n", juegoEscalera(dados));
    }else {
      printf("7) Tachar Escalera.\n");
    }
     }




    if (jugadasUsadasMulti[1][7] == 0)
    {
    if(juegoFull(dados)){
      printf("8) Anotar %d en Full.\n", juegoFull(dados));
    }else {
      printf("8) Tachar Full.\n");
    }
     }




     if (jugadasUsadasMulti[1][8] == 0)
    {
    if(juegoPoker(dados)){
      printf("9) Anotar %d en Poker.\n", juegoPoker(dados));
    }else {
      printf("9) Tachar Poker.\n");
    }
     }



    if (jugadasUsadasMulti[1][9] == 0)
    {
    if(juegoGenerala(dados)){
      printf("10) Anotar %d en Generala.\n", juegoGenerala(dados));
    }else {
      printf("10) Tachar Generala.\n");
    }
     }
      


      if(jugadasUsadasMulti[1][9] == 1 && jugadasUsadasMulti[1][10] == 0 ){
      if(juegoDobleGenerala(dados)){

        printf("11) Anotar %d en Doble Generala.\n", juegoDobleGenerala(dados));

      }else {
        printf("11) Tachar Doble Generala.\n");

      }
    }else if (jugadasUsadasMulti[1][10] == 0) {
      printf("11) Tachar Doble Generala.\n");
    }





    scanf("%d", &anotar);
    if ((anotar < 1 || anotar > 11) || (jugadasUsadasMulti[1][anotar - 1] == 1)){

      printf("**Valor ingresado no admitido. Ingrese una jugada posible.**\n");

    }

  } while ((anotar < 1 || anotar > 11) || (jugadasUsadasMulti[1][anotar - 1] == 1));

}


  anotarJugadaMulti(dados, turno, jugadasUsadasMulti, anotar, tablaMulti);
}

void anotarJugadaMulti(int dados[], int turno, int jugadasUsadasMulti[MULTIJUGADOR][CATEGORIAS], int anotar, int tablaMulti[MULTIJUGADOR][CATEGORIAS]){

  if (turno %2 != 0) {

    jugadasUsadasMulti[0][anotar - 1] = 1;

    switch(anotar){

      case 1:
        tablaMulti[0][0] = juegoUno(dados);
        printf("Se han cargado %d puntos\n", juegoUno(dados));
        break;

      case 2:
        tablaMulti[0][1] = juegoDos(dados);
        printf("Se han cargado %d puntos\n", juegoDos(dados));
        break;

      case 3:
        tablaMulti[0][2] = juegoTres(dados);
        printf("Se han cargado %d puntos\n", juegoTres(dados));
        break;

      case 4:
        tablaMulti[0][3] = juegoCuatro(dados);
        printf("Se han cargado %d puntos\n", juegoCuatro(dados));
        break;

      case 5:
        tablaMulti[0][4] = juegoCinco(dados);
        printf("Se han cargado %d puntos\n", juegoCinco(dados));
        break;

      case 6:
        tablaMulti[0][5] = juegoSeis(dados);
        printf("Se han cargado %d puntos\n", juegoSeis(dados));
        break;

      case 7:
        tablaMulti[0][6] = juegoEscalera(dados);
        printf("Se han cargado %d puntos\n", juegoEscalera(dados));
        break;

      case 8:
        tablaMulti[0][7] = juegoFull(dados);
        printf("Se han cargado %d puntos\n", juegoFull(dados));
        break;

      case 9:
        tablaMulti[0][8] = juegoPoker(dados);
        printf("Se han cargado %d puntos\n", juegoPoker(dados));
        break;

      case 10:
        tablaMulti[0][9] = juegoGenerala(dados);
        printf("Se han cargado %d puntos\n", juegoGenerala(dados));
        break;

      case 11:
        tablaMulti[0][10] = juegoDobleGenerala(dados);
        printf("Se han cargado %d puntos\n", juegoDobleGenerala(dados));
        break;

    }

  } else if ( turno %2 == 0) {
    
    jugadasUsadasMulti[1][anotar - 1] = 1;

    switch(anotar){

      case 1:
        tablaMulti[1][0] = juegoUno(dados);
        printf("Se han cargado %d puntos\n", juegoUno(dados));
        break;

      case 2:
        tablaMulti[1][1] = juegoDos(dados);
        printf("Se han cargado %d puntos\n", juegoDos(dados));
        break;

      case 3:
        tablaMulti[1][2] = juegoTres(dados);
        printf("Se han cargado %d puntos\n", juegoTres(dados));
        break;

      case 4:
        tablaMulti[1][3] = juegoCuatro(dados);
        printf("Se han cargado %d puntos\n", juegoCuatro(dados));
        break;

      case 5:
        tablaMulti[1][4] = juegoCinco(dados);
        printf("Se han cargado %d puntos\n", juegoCinco(dados));
        break;

      case 6:
        tablaMulti[1][5] = juegoSeis(dados);
        printf("Se han cargado %d puntos\n", juegoSeis(dados));
        break;

      case 7:
        tablaMulti[1][6] = juegoEscalera(dados);
        printf("Se han cargado %d puntos\n", juegoEscalera(dados));
        break;

      case 8:
        tablaMulti[1][7] = juegoFull(dados);
        printf("Se han cargado %d puntos\n", juegoFull(dados));
        break;

      case 9:
        tablaMulti[1][8] = juegoPoker(dados);
        printf("Se han cargado %d puntos\n", juegoPoker(dados));
        break;

      case 10:
        tablaMulti[1][9] = juegoGenerala(dados);
        printf("Se han cargado %d puntos\n", juegoGenerala(dados));
        break;

      case 11:
        tablaMulti[1][10] = juegoDobleGenerala(dados);
        printf("Se han cargado %d puntos\n", juegoDobleGenerala(dados));
        break;

    }

  }

}


void mostrarTablaMulti(char nombreJ1[], char nombreJ2[], int turno, int tablaMulti[MULTIJUGADOR][CATEGORIAS], int puntosTotalesJ1, int puntosTotalesJ2){
  
  puntosTotalesJ2 = 0;
  puntosTotalesJ1 = 0;

  for(int i = 0; i < CATEGORIAS; i++){
    puntosTotalesJ1 += tablaMulti[0][i];

  }
  
  for(int j = 0; j < CATEGORIAS; j++){
    puntosTotalesJ2 += tablaMulti[1][j];
  
  }

  printf("\nTabla de puntajes de ambos jugadores:\n");

  printf("1)Juego Uno: %d  |  %d\n", tablaMulti[0][0], tablaMulti[1][0]);
  printf("2)Juego Dos: %d  |  %d\n", tablaMulti[0][1], tablaMulti[1][1]);
  printf("3)Juego Tres: %d  |  %d\n", tablaMulti[0][2], tablaMulti[1][2]);
  printf("4)Juego Cuatro: %d  |  %d\n", tablaMulti[0][3], tablaMulti[1][3]);
  printf("5)Juego Cinco: %d  |  %d\n", tablaMulti[0][4], tablaMulti[1][4]);
  printf("6)Juego Seis: %d  |  %d\n", tablaMulti[0][5], tablaMulti[1][5]);
  printf("7) Escalera: %d  |  %d\n", tablaMulti[0][6], tablaMulti[1][6]);
  printf("8)Juego Full: %d  |  %d\n", tablaMulti[0][7], tablaMulti[1][7]);
  printf("9)Juego Poker: %d  |  %d\n", tablaMulti[0][8], tablaMulti[1][8]);
  printf("10)Juego Generala: %d  |  %d\n", tablaMulti[0][9], tablaMulti[1][9]);
  printf("11)Juego Doble Generala: %d  |  %d\n", tablaMulti[0][10], tablaMulti[1][10]);

  printf("\nJugador 1: %s --> Puntos: %d \nJugador 2: %s --> Puntos: %d\n\n", nombreJ1, puntosTotalesJ1, nombreJ2, puntosTotalesJ2);

  // Evaluacion de quien es el jugador ganador.
  if (TURNOSMULTIJUGADOR == turno){
    if (puntosTotalesJ1 > puntosTotalesJ2){
      printf("Felicidades %s has ganado esta partida con %d puntos\n", nombreJ1, puntosTotalesJ1);

    }else if(puntosTotalesJ1 < puntosTotalesJ2){

      printf("Felicidades %s has ganado esta partida con %d puntos\n", nombreJ2, puntosTotalesJ2);

    }else{
      printf("Se ha producido un empate. \n");
    }

    printf("\n");
  // Evaluacion de rango de desempeño en ambos jugadores.

  if(puntosTotalesJ1 < 490 && puntosTotalesJ1 > 360){
    printf("Rango de Puntaje 360 - 490 --> El desempeño del jugador 1 %s ha sido Excelente!\n", nombreJ1);
  
    }else if(puntosTotalesJ1 < 360 && puntosTotalesJ1 > 240){
      printf("Rango de Puntaje 240 - 360 --> El desempeño del jugador 1 %s ha sido Bueno.\n", nombreJ1);
  
    }else if(puntosTotalesJ1 < 240 && puntosTotalesJ1 > 120){
      printf("Rango de Puntaje 120 - 240 --> El desempeño del jugador 1 %s ha sido Regular.\n", nombreJ1);
  
    }else{
      printf("Rango de Puntaje menor a 120 --> El desempeño del jugador 1 %s ha sido Malo.\n", nombreJ1);
    }

    printf("\n");


    if(puntosTotalesJ2 < 490 && puntosTotalesJ2 > 360){
      printf("Rango de Puntaje 360 - 490 --> El desempeño del jugador 2 %s ha sido Excelente!\n", nombreJ2);
  
    }else if(puntosTotalesJ2 < 360 && puntosTotalesJ2 > 240){
      printf("Rango de Puntaje 240 - 360 --> El desempeño del jugador 2 %s ha sido Bueno.\n", nombreJ2);
  
    }else if(puntosTotalesJ2 < 240 && puntosTotalesJ2 > 120){
      printf("Rango de Puntaje 120 - 240 --> El desempeño del jugador 2 %s ha sido Regular.\n", nombreJ2);
  
    }else{
      printf("Rango de Puntaje menor a 120 --> El desempeño del jugador 2 %s ha sido Malo.\n", nombreJ2);
    }

    printf("\n");

  }

}

void resetMulti (int dados[], int turno, int jugadasUsadasMulti[MULTIJUGADOR][CATEGORIAS], int tablaMulti[MULTIJUGADOR][CATEGORIAS], int puntosTotalesJ1, int puntosTotalesJ2) {
    // Reiniciamos la tabla de puntajes de ambos jugadores a 0.
  for (int i = 0; i < CATEGORIAS; i++) {
    tablaMulti[0][i] = 0;
    for (int j = 0; j < CATEGORIAS; j ++) {
      tablaMulti[1][j] = 0;
    }
  }

for (int i = 0; i < CATEGORIAS; i++){
  jugadasUsadasMulti[0][i] = 0;
  for (int j = 0; j < CATEGORIAS; j++) {
    jugadasUsadasMulti[1][j] = 0;
  }
  }

  puntosTotalesJ1 = 0;
  puntosTotalesJ2 = 0;
  turno = 0;

    // Mostrar un mensaje para indicar que el juego ha sido reseteado.
  printf("\n** Juego reseteado para ambos jugadores, Jugador 1: %s  y  jugador 2: %s. **\n", nombreJ1, nombreJ2);
  printf("*** Turnos y puntajes han sido reiniciados. ***\n\n");

  // Variables para tiempo.
  time_t inicio_juego, fin_juego;


  // Inicio del "cronometro" similar a srand.
      inicio_juego = time(NULL);

  lanzamientosMulti (dados, turno, jugadasUsadasMulti, tablaMulti, puntosTotalesJ1, puntosTotalesJ2);


  fin_juego = time(NULL);

  // Calcular el tiempo con difftime.

  int duracion_partida = difftime(fin_juego, inicio_juego);

  printf("La partida tuvo una duracion de: %d minutos.\n", duracion_partida / 60);
  printf("\n");


  exit(0);
}