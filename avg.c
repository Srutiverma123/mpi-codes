#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
// size of array
#define n 10000
// Temporary array for slave process
float arr[n];
int main(int argc, char* argv[])
{
int pid, np, k, nRec;
MPI_Status status;
MPI_Init(&argc, &argv);
MPI_Comm_rank(MPI_COMM_WORLD, &pid);
MPI_Comm_size(MPI_COMM_WORLD, &np);
if (pid == 0) 
{
	srand(time(0));
	float a[n];
	for (int i = 0; i < n;i++)
		a[i] = rand()%1000;
	int index, i;
	k = n /(np-1);
	if (np > 1)
	{
		for (i = 1; i < np - 1; i++)
		{
			index = (i-1) * k;
			MPI_Send(&k,  1, MPI_INT, i, 0,MPI_COMM_WORLD);
			MPI_Send(&a[index],  k,  MPI_FLOAT, i, 0,MPI_COMM_WORLD);
		}
		index = (i-1) * k;
		int rem = n - index;
		MPI_Send(&rem,  1, MPI_INT,  i, 0,  MPI_COMM_WORLD);		
		MPI_Send(&a[index],  rem,  MPI_FLOAT, i, 0,MPI_COMM_WORLD);
	}
	float sum = 0;
	float tmp = 0;
	for (i = 1; i < np; i++) 
	{
		MPI_Recv(&tmp, 1, MPI_FLOAT, MPI_ANY_SOURCE, 0,MPI_COMM_WORLD, &status);
		sum += tmp;
	}
	sum /= n;
	printf("Average of array is : %f\n", sum);
}
else 
{
	MPI_Recv(&nRec, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,&status);
	MPI_Recv(&arr, nRec, MPI_FLOAT, 0, 0, MPI_COMM_WORLD,&status);
	float pavg = 0;
	for (int i = 0; i < nRec; i++)
		pavg += arr[i];
	MPI_Send(&pavg, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
}
MPI_Finalize();
return 0;
}
