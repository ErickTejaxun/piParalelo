/*
* Erick Roberto Tejaxún
* Universidad de Extremadura 
*/
#include <iostream>
#include <time.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char * argv[])
{
	if(argc < 3)
	{		
		cout << "Ejecute de la forma piParalelo1 numeroIteraciones numeroHilo"<< endl;
		return 0;
	}	
 	//omp_set_num_threads(atoi(argv[2]));
	int numeroHilo = atoi(argv[2]);
	int numeroIteraciones = atoi(argv[1]);
	int contador = 0;	
	srand (time(NULL));
	float x = 0;
	float y = 0;
	//Tiempo de inicio 	
	double tiempoInicio = omp_get_wtime();
	#pragma omp parallel for num_threads(numeroHilo) reduction(+:contador) private(x,y)
	for(int i = 0 ; i < numeroIteraciones; i++)
	{
		x = (float)rand() / RAND_MAX;
		y = (float)rand() / RAND_MAX;
		//cout << "X:" << x <<"   y: " << y << endl;
		float d = sqrt( pow(x,2) + pow(y,2));
		if(d<=1)
		{
			contador++;
		}
	}
	float pi = (float)contador*4/numeroIteraciones;
	double tiempoFinal = omp_get_wtime();
	cout << "El valor de pi es : "<< pi <<endl;
	cout << "El tiempo necesitado fue: " << tiempoFinal- tiempoInicio<<endl;
	return 0;
}
