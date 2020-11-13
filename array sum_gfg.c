#include <mpi.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h>

//mpirun -np 5 --hostfile hostfile a.out

#define n 4 //Number of players and nodes

int playerScores[n]; 

int main(int argc, char* argv[]) 
{ 

	int pid = 1, np, i; 

	MPI_Status status; 
	MPI_Init(&argc, &argv); 

	MPI_Comm_rank(MPI_COMM_WORLD, &pid); 
	MPI_Comm_size(MPI_COMM_WORLD, &np); 
	
	if (pid == 0) { 
		srand(time(0));
		int *arr[n];
		for(i=0;i<n;i++)
			arr[i] = (int *)malloc(n * sizeof(int));

		for (i = 0; i < n; i++) { 
			MPI_Recv(&playerScores, n, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status); 
			for(int j = 0; j<n ;j++)				
				arr[i][j] = playerScores[j];
		}
		int sum[n];
		for(i = 0; i<n; i++)
			sum[i] = 0;
		for(i = 0; i<n; i++) {
			printf("Node %d\n",i+1);
			for(int j = 0; j<n ;j++){
				printf("P[%d]: %d\t",j+1,arr[i][j]);
				sum[j] += arr[i][j];
			}
			printf("\n");
		}
		for(i = 0; i<n; i++)
			printf("P[%d] Total is: %d\t",i+1,sum[i]);
		printf("\n");
		
	} 

	else {
		srand(time(0)*pid);
		for(i = 0; i<n; i++){
			playerScores[i] = rand()%10;
		}
		MPI_Send(&playerScores, n, MPI_INT, 0, 0, MPI_COMM_WORLD); 
	} 

	MPI_Finalize(); 

	return 0; 
} 

