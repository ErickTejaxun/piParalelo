#include <iostream>
#include <time.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char * argv[])
{
	int numeroIteraciones = 1000000000;
	cout << "Ejecutar de la forma pi [numeroIteraciones]"<<endl;
	if(argc < 2)
	{		
		cout << "Número de interaciones por defecto :"<< numeroIteraciones << endl;
	}
	else
	{
		numeroIteraciones =atoi(argv[1]);
		cout << "Número de interaciones :"<< numeroIteraciones << endl;
	}	
	int contador = 0;	
	srand (time(NULL));
	float x = 0; 
	float y = 0;
	//Tiempo de inicio 
	int numeroHilo = omp_get_thread_num();
	double tiempoInicio = omp_get_wtime();
	for(int i = 0 ; i < numeroIteraciones; i++)
	{
		x = (float)rand() / RAND_MAX;
		y = (float)rand() / RAND_MAX;
		//cout << "X:" << x <<"   y: " << y << endl;
		float d = sqrt( pow(x,2) + pow(y,2)); // Distancia del punto (x,y) hacia el origen (0,0)
		if(d<=1) // Si la distancia es menor a 1, significa que el punto está dentro del área del cuadrante
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
