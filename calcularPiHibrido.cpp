#include <mpi.h>
#include <iostream>
#include <stdio.h>
#include <omp.h>
#include "MersenneTwister.h"

using namespace std;

int main(int argc,char* argv[])
{
	if(argc < 4)
	{		
		cout << "Ejecute de la forma "<<argv[0]<<" [numeroIteraciones] [numeroHilo] [libreria]"<< endl;
		return 0;
	}	 	
	int numeroHilo = atoi(argv[2]);
	int numeroIteraciones = atoi(argv[1]);
	int libreria = atoi(argv[3]);
	int contador = 0;		
	float x = 0;
	float y = 0;		
	int n = numeroHilo;
	double tiempoInicio = omp_get_wtime();
	if(n> 8)
	{
		n = n / 8;
	}
	int estados[n];
	MTRand rands[n];
    int done = 0, n, my_rank, num_threads, i;
    double PI25DT = 3.141592653589793238462643;
    double mypi, pi, h, sum, x;    


    MPI_Init(&argc, &argv); // Inicializamos las hebras
    int number_amount;
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&world_rank);
    int I = 0;
    if (world_rank == 0) 
    {
        const int MAX_NUMBERS = 100;
        int numbers[MAX_NUMBERS];
        for (int i=0; i<MAX_NUMBERS; i++)
        numbers[i]=I;
        srand(time(NULL));
        number_amount = (rand() / (float)RAND_MAX) * MAX_NUMBERS;
        MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("0 sent %d numbers to 1\n", number_amount);
    } 
    else if (world_rank == 1) 
    {
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &number_amount);
        int* number_buf = (int*)malloc(sizeof(int) * number_amount);
        MPI_Recv(number_buf, number_amount, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if(libreria==3)
        {				
            printf("Librería seleccionada Sramd() variable privada\n");
            tiempoInicio = omp_get_wtime();	
            int estado;		
            estado = omp_get_thread_num();
            sramd(&estado, time(NULL));				
            #pragma omp parallel for num_threads(numeroHilo) reduction(+:contador) private(estado,y,x)
            for(int i = 0 ; i < numeroIteraciones; i++)
            {
                
                x=(float)ramd(&estado)/ MRAND_MAX;						
                y=(float)ramd(&estado)/ MRAND_MAX;
                //printf("%d) \t%f : %f \n",i,x,y);
                float d = sqrt( pow(x,2) + pow(y,2));
                if(d<=1)
                {
                    contador++;
                }
            }		
        }
    }
    MPI_Finalize();
    double tiempoFinal = omp_get_wtime(); // Fin de ejecucion paralela;
	float pi = (float)contador*4/numeroIteraciones;
	double tiempoFinal = omp_get_wtime();
	cout << "El valor de pi es : "<< pi <<endl;
	cout << "El tiempo necesitado fue: " << tiempoFinal- tiempoInicio<<endl;
	return 0;


}