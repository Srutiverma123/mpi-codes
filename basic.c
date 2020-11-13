#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
void my_bcast(void* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator)
{
	int world_rank;
	MPI_Comm_rank(communicator, &world_rank); 
	int world_size;
	MPI_Comm_size(communicator, &world_size);
	if(world_rank == root)
	{
		printf("18bce1005 sruti verma\n");
		int i;
		for(i =0;i<world_size; i++)
		{
			if(i != world_rank)
			{
				MPI_Send(data, count, datatype, i, 0, communicator);
				printf("The message is sent by process: %d\nThe data address: %p\n\n", world_rank, data);
			}
		}
	}
	else
	{
		MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
		printf("The message is received by process: %d\nThe data address: %p\n\n", world_rank, data);
	}
}
void main(int argc, char* argv)
{
	MPI_Init(NULL, NULL);
	int dataNumber = 10;
	my_bcast(&dataNumber, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Finalize();
}

