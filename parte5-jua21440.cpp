/*
* -----------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERÍA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACIÓN
* CC3086 - Programacion de Microprocesadores
* Fabian Juárez 21440
*------------------------------------------
* Descripción: Crear 3 hilos posix 
* Solicitar al usuario una velocidad
*
* Hilo1: Imprimir el valor de un contador
* iniciando en 0 y terminando en 50
* antes de contar realizara un sleep de 2 segundos.
*
* Hilo2: Lee el valor actual del contador y lo
* ingresa a la formula D= v/t; donde t es el contador y
* v es la velocidad ingresada
*
* Hilo3: Realizar la revision de la distancia recorrida
* cada 5 metros recorridos, mostrar que se han recorrido
* esos mismos 5 metros.
*------------------------------------------
*/ #include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>
using namespace std;
//Creacion de variables que se utilizaran de manera global
void *hilo1(void *ptr);
void *hilo2(void *ptr);
void *hilo3(void *ptr);
int velocidad; //Variable para saber la velocidad en m/s
int contador; //Variable para saber el contador del numero
int distancia;
int main()
{
  cout << "Escribe la velocidad a la que va en m/s: \n"; //Se pide la velocidad a ingresar
  cin >> velocidad; // variable en la que se guardara la velocidad
  
  // Declaramos las variables tipo pthread_t
     pthread_t thread1, thread2, thread3;
     char const *message1 = "Thread 1";
     char const *message2 = "Thread 2";
     char const *message3 = "Thread 3";
    // Se crean los hilos de manera independiente el cual ejecutara la misma funcion
     pthread_create( &thread1, NULL, hilo1, (void*) message1);
     pthread_create( &thread2, NULL, hilo2, (void*) message2);
     pthread_create( &thread3, NULL, hilo3, (void*) message3);
    // Esperar a que cada thread termine en orden
     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 
     pthread_join( thread3, NULL); 
     exit(0);
  
}

// Funcion para el primer thread el cual se encarga de imprimir el valor de un 
// contador que inicia en 0 y termina en 50 realizando un sleep de 2 segundos
// entre cada valor.
void *hilo1(void *ptr){
    contador = 0;
//Ciclo para recorrer el contador y mostrarlo en pantalla
    for (int i = 0; i < 51; i++){
        printf("valor del hilo 1 es: %d segundos\n", contador);
        sleep(2);
        contador++;
    }
    return 0;
}

// Funcion para el segundo thread el cual se encarga de leer el valor actual del contador
// e ingresarlo a la formula D=v/t donde v es la velocidad ingresada al inicio y t el contador.
// se debe imprimir que en t segundos la distancia recorrida es: valor
void *hilo2(void *ptr){
    while(contador < 51){
        if (contador>0){
            distancia = velocidad*contador; 
            printf("En %d segundos, la distancia recorrida es: %d metros\n",contador,distancia);
            sleep(2);
        }
    }
    return 0;
}

// Funcion para el tercer thread el cual se encarga de la revision de la 
// distancia recorrida, cada 5 metros recorridos se mostrara que se a
// recorrido 5 metros
void *hilo3(void *ptr){
    int divisible = 0;
    bool cambioDistancia = false;
    int ultimaDistancia = 0;
    while(contador<51){
        //Ciclo para verificar si el numero cuantas veces recorrio 5 metros
        if(ultimaDistancia!=distancia){
            cambioDistancia = true;
            ultimaDistancia = distancia;
        }
        else{
            cambioDistancia=false;
        }
        if(cambioDistancia){
            divisible = 0;
            while(divisible <= distancia){
                if(divisible>=5 &&){
                    printf("Se han recorrido 5 metros\n");
                }
                divisible = divisible + 5;
            }
        }
    }
    return 0;
}