#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
int main()
{
MPI_Init(NULL, NULL);
int ntasks,rank;
MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
int token;
if (rank != 0)
{
	MPI_Recv(&token, 1, MPI_INT, rank - 1 , 10,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("Node %d Received token %d from Node%d\n",rank,token,rank-1);
}
else
{
	token = 1;
}
MPI_Send(&token, 1, MPI_INT, (rank + 1) % ntasks , 10,MPI_COMM_WORLD);
if(rank == 0)
{
	MPI_Recv(&token, 1, MPI_INT, ntasks - 1, 10, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	printf("Node %d Received token %d from Node%d\n",rank,token,ntasks-1);
}
MPI_Finalize();
return 0;
}
