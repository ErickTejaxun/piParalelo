#include <iostream>
#include <time.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include "mramd.h"
#include "MersenneTwister.h"
using namespace std;


int main(int argc, char * argv[])
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
	for(int cont =0 ; cont < n ; cont++)
	{
		MTRand r(time(NULL));;
		rands[cont] = r;
		printf("pruba %f\n",rands[cont].rand());
	}
	if(libreria==1)
	{
		printf("Librería seleccionada Srand()\n");
		srand (time(NULL));	
		tiempoInicio = omp_get_wtime();
		#pragma omp parallel for num_threads(numeroHilo) reduction(+:contador) private(x,y)
		for(int i = 0 ; i < numeroIteraciones; i++)
		{
			x= (float)rand() / RAND_MAX;			
			y= (float)rand() / RAND_MAX;		
			//printf("%d) %f : %f \n",i,x,y);		
			float d = sqrt( pow(x,2) + pow(y,2));
			if(d<=1)
			{
				contador++;
			}
		}
	}
	if(libreria==2)
	{				
		printf("Librería seleccionada Sramd() vector\n");		
		int estado;				
		estado = estados[omp_get_thread_num()];	
		sramd(&estado, time(NULL));
		tiempoInicio = omp_get_wtime();					
		#pragma omp parallel for num_threads(numeroHilo) reduction(+:contador)		
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

	if(libreria==4)
	{				
		printf("Librería seleccionada MTRand() vector\n");
		tiempoInicio = omp_get_thread_num();	
		int estado;
		//estado = omp_get_thread_num();						
		tiempoInicio = omp_get_wtime();					
		#pragma omp parallel for num_threads(numeroHilo) reduction(+:contador)		
		for(int i = 0 ; i < numeroIteraciones; i++)
		{
			
			//x=(float) rands[].rand();					
			/*y=(float) rands[estado].rand();	
			//printf("%d) \t%f : %f \n",i,x,y);
			float d = sqrt( pow(x,2) + pow(y,2));
			if(d<=1)
			{
				contador++;
			}*/
		}
	}	

	if(libreria==5)
	{				
		printf("Librería seleccionada MTRand() variable privada\n");
		tiempoInicio = omp_get_wtime();	
		int estado;		
		estado = omp_get_thread_num();
		sramd(&estado, time(NULL));	
		MTRand r(time(NULL));
		MTRand r2(time(NULL));					
		#pragma omp parallel for num_threads(numeroHilo) reduction(+:contador) private(y,x,r,r2)
		for(int i = 0 ; i < numeroIteraciones; i++)
		{

			x= r.rand();						
			y= r2.rand();
			//printf("%d) \t%f : %f \n",i,x,y);
			float d = sqrt( pow(x,2) + pow(y,2));
			if(d<=1)
			{
				contador++;
			}
		}		
	}


	float pi = (float)contador*4/numeroIteraciones;
	double tiempoFinal = omp_get_wtime();
	cout << "El valor de pi es : "<< pi <<endl;
	cout << "El tiempo necesitado fue: " << tiempoFinal- tiempoInicio<<endl;
	return 0;
}
