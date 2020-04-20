all:	
	@g++ calcularPi.cpp -o piSecuencial -fopenmp
	@g++ calcularPiParalelo.cpp -o piParalelo1 -fopenmp
	@g++ calcularPiParaleloLib.cpp -o piParalelo2 -fopenmp
	@mpic++ padre.cpp -o padre  -fopenmp
	@mpic++ hijo.cpp -o hijo -fopenmp	

hibrido: 
	mpic++ padre.cpp -o padre  -fopenmp
	mpic++ hijo.cpp -o hijo -fopenmp


clean:
	rm piSecuencial piParalelo1 piParalelo2 padre hijo


pruebas:
	./piParalelo2 100000000 2 2
	./piParalelo2 100000000 4 2
	./piParalelo2 100000000 8 2
	./piParalelo2 100000000 16 2
	./piParalelo2 100000000 2 3
	./piParalelo2 100000000 4 3
	./piParalelo2 100000000 8 3 
	./piParalelo2 100000000 16 3 
	./piParalelo2 100000000 2 4 
	./piParalelo2 100000000 4 4 
	./piParalelo2 100000000 8 4 
	./piParalelo2 100000000 16 4 
	./piParalelo2 100000000 2 5
	./piParalelo2 100000000 4 5
	./piParalelo2 100000000 8 5
	./piParalelo2 100000000 16 5

pruebas-hibrido:
	mpiexec -n 1 ./padre ./hijo 100000000 2 2 -f direcciones.txt 
	mpiexec -n 1 ./padre ./hijo 100000000 2 4 -f direcciones.txt
	mpiexec -n 1 ./padre ./hijo 100000000 2 8 -f direcciones.txt
	mpiexec -n 1 ./padre ./hijo 100000000 2 16 -f direcciones.txt
	mpiexec -n 1 ./padre ./hijo 100000000 4 2 -f direcciones.txt 
	mpiexec -n 1 ./padre ./hijo 100000000 4 4 -f direcciones.txt
	mpiexec -n 1 ./padre ./hijo 100000000 4 8 -f direcciones.txt
	mpiexec -n 1 ./padre ./hijo 100000000 4 16 -f direcciones.txt
	mpiexec -n 1 ./padre ./hijo 100000000 8 2 -f direcciones.txt 
	mpiexec -n 1 ./padre ./hijo 100000000 8 4 -f direcciones.txt
	mpiexec -n 1 ./padre ./hijo 100000000 8 8 -f direcciones.txt
	mpiexec -n 1 ./padre ./hijo 100000000 8 16 -f direcciones.txt		
