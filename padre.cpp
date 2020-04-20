/*
* Erick Roberto Tejaxún
* Universidad de Extremadura 
*/
#include <mpi.h>
#include <iostream>
#include <stdio.h>
#include <mpi.h>
#include <omp.h>
#include <stdlib.h>
#include "MersenneTwister.h"

using namespace std;

int main(int argc,char* argv[])
{
	if(argc < 5)
	{		
		cout << "Ejecute de la forma "<<argv[0]<<" ./hijo [numeroIteraciones] [numeroHilos] [numeroProcesosHijos]"<< endl;
		return 0;
	}	 		
	int numeroIteraciones = atoi(argv[2]);
    int numeroHilos = atoi(argv[3]);
	int numeroProcesos = atoi(argv[4]);	
	double tiempoInicio, tiempoFinal;    

    MPI_Init(&argc, &argv);
    int rank, size, ack;
    MPI_Comm interComunicador;
    MPI_Comm_size(MPI_COMM_WORLD, &size); // 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //
    tiempoInicio = omp_get_wtime(); //Tiempo de inicio.

    MPI_Comm_spawn(argv[1],MPI_ARGV_NULL,numeroProcesos,
        MPI_INFO_NULL,0,MPI_COMM_SELF,&interComunicador, MPI_ERRCODES_IGNORE); // Creamos los procesos hijos

    printf("Se han lanzado %d procesos hijos.\n", numeroProcesos);
    int contador = 0, temporal = 0;
    int iteracionesProceso = numeroIteraciones / numeroProcesos; // Numero de iteraciones por proceso.
    int hilosProceso = numeroHilos / numeroProcesos;

    /*Le enviamos los parametros de la ejecución a cada proceso*/
    for(int i = 0 ; i < numeroProcesos; i++)
    {
        MPI_Send(&hilosProceso,1,MPI_INT,i,0,interComunicador);           //1.Enviamos el número de hilos
        MPI_Send(&iteracionesProceso,1,MPI_INT,i,0,interComunicador);     //2.Enviamos el número de iteraciones                
    }

    /*Recolectamos los resultados*/
    for(int i = 0 ; i < numeroProcesos; i++)
    {
        MPI_Recv(&temporal,1,MPI_INT,i,0,interComunicador,MPI_STATUS_IGNORE);
        //printf("Recibiendo %d)  %d\n",i,temporal);
        contador+=temporal;
    }

    float pi = (float) contador* 4 /numeroIteraciones;
    tiempoFinal = omp_get_wtime();

    /*Indicamos que terminen los procesos hijos.*/
    for(int i = 0 ; i< numeroProcesos; i++)
    {
        MPI_Send(&ack,1,MPI_INT,i,0,interComunicador);
    }
    printf("El valor de pi es: %f \n",pi);
    printf("El tiempo necesitado fue: %f \n",tiempoFinal-tiempoInicio);
    MPI_Finalize();
	return 0;
}