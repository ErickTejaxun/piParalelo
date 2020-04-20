/*
* Erick Roberto Tejaxún
* Universidad de Extremadura 
*/
#include <iostream>
#include <time.h>
#include <math.h>
#include <omp.h>
#include <mpi.h>
#include <stdlib.h>
#include "mramd.h"
#include "MersenneTwister.h"

using namespace std;

int main(int argc, char * argv[])
{	
	int rank, size, numeroIteraciones, numeroHilos, ack;
	MPI_Init(&argc, &argv); 	
	int contador = 0;
	float x, y;		
	MPI_Comm parent; 				// Intercomunicador hacia el padre.
	MPI_Comm_get_parent(&parent);	// Obtenemos el comunicador.
	
	if(parent == MPI_COMM_NULL)
	{
		printf("Error: no se ha creado desde un padre.\n");
		return 0;
	}
	MPI_Comm_rank(parent, &rank);
	/*Recibimos el número de hilos*/
	MPI_Recv(&numeroHilos,1,MPI_INT,0,0,parent,MPI_STATUS_IGNORE);

	/*Ahora recibimos el número de iteraciones*/
	MPI_Recv(&numeroIteraciones,1, MPI_INT, 0,0, parent,MPI_STATUS_IGNORE);

	//printf("%d) Librería seleccionada Sramd() privada No. Iterciones: %d \t No. Hilos: %d\n",rank,numeroIteraciones,numeroHilos);
	//printf("Librería seleccionada MTRand() variable privada\n");		
	MTRand r(time(NULL));							
	#pragma omp parallel for num_threads(numeroHilos) reduction(+:contador) private(y,x,r)
	for(int i = 0 ; i < numeroIteraciones; i++)
	{
		x= r.rand();						
		y= r.rand();		
		float d = sqrt( pow(x,2) + pow(y,2));
		if(d<=1)
		{
			contador++;
		}
	}
	//printf("Resultado %d %d\n",rank,contador);
	/*Enviamos el resultado*/	
	MPI_Send(&contador,1,MPI_INT,0,0,parent);

	/*Esperamos que nos indiquen que la iteracion terminó*/
	MPI_Recv(&ack,1,MPI_INT,0,0,parent,MPI_STATUS_IGNORE);
	MPI_Finalize();
	return 0;
}
