all:	
	@g++ calcularPi.cpp -o piSecuencial -fopenmp
	@g++ calcularPiParalelo.cpp -o piParalelo1 -fopenmp
	@g++ calcularPiParaleloLib.cpp -o piParalelo2 -fopenmp
	#@mpic++ calcularPiHibrido.cpp -o piHibrido 

clean:
	rm piSecuencial piParalelo1 piParalelo2 piHibrido

