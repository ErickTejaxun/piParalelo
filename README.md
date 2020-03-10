# Cálculo de PI a través de números aleatorios con Método Montecarlo
Práctica #2 de laboratorio de Computación Paralela, UEx 2020

Los programas dentro de esta práctica son los siguientes:
# piSecuencial.cpp : 
Algoritmo en forma secuencial. 

Ejecución:
	./piSecuencial [numeroIteraciones]

Dependencias:
	- Librerías standar C++
	- Librería SRand para generación de números aleatorios.

# piParalelo1.cpp: 
Algoritmo para cálculo de PI de forma paralela utilizando OpenMP para su implementación.

Ejecución:
	./piParalelo1 [numeroIteraciones] [numeroHilos]

Dependencias:
	- Librerías standar C++
	- Librería SRand para generación de números aleatorios.

# piParalelo2.cpp:
Implementación del algoritmo de forma paralela utilizando OpenMP para su implementación.

Ejecución:
	./piParalelo2 [numeroIteraciones] [numeroHilos] [flag]

Donde flag hace referencia la manera de generación de número aleatorios de la siguiente manera:
	- 1. Utilización de la librería Srand.
	- 2. Utilización de la librería Ramd a través de vector para separación de valores entre hilos.
	- 3. Utilización de la librería Ramd a través de utilizar variables privadas para separación entre hilos.
	- 4. Utilización de la librería MTRand a través de vector para separación de valores entre hilos.
	- 5. Utilización de la librería MTRand a través de utilizar variables privadas para separación entre hilos.

Dependencias:
        - Librerías standar C++
        - Librería SRand para generación de números aleatorios.
        - Librería Ramd para generación de números aleatorios.
        - Librería MersenneTwister.h para generación de números aleatorios.


# piHibrido.cpp
Implementación del algoritmo de forma paralela utilizando OpenMP y MPI para su implementación, creando una implementación híbrida 
de computación paralela por paso de mensajes y computación paralela por multi hilos. 

Ejecución:
        mipexec ./piHibrido  [numeroIteraciones] [numeroHilos] [flag]

Donde flag hace referencia la manera de generación de número aleatorios de la siguiente manera:
        - 1. Utilización de la librería Srand.
        - 2. Utilización de la librería Ramd a través de vector para separación de valores entre hilos.
        - 3. Utilización de la librería Ramd a través de utilizar variables privadas para separación entre hilos.
        - 4. Utilización de la librería MTRand a través de vector para separación de valores entre hilos.
        - 5. Utilización de la librería MTRand a través de utilizar variables privadas para separación entre hilos.

Dependencias:
        - Librerías standar C++
        - Librería SRand para generación de números aleatorios.
        - Librería Ramd para generación de números aleatorios.
        - Librería MersenneTwister.h para generación de números aleatorios.
 


# Utilización
	1. Instalar MPI en el host [ver link: https://www.mpich.org/downloads/versions]
	2. Compilar a través del comando make
	3. Ejecutar


# Licencia 
  MIT :v

