#include<mpi.h>
#include<stdio.h>
int main(int argc, char *argv[])
{
int myid, numprocs, left, right;
int buffer[10], buffer2[10];
MPI_Request request, request2;
MPI_Status status;
MPI_Init(&argc, &argv);
MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
MPI_Comm_rank(MPI_COMM_WORLD, &myid);
right = (myid + 1) % numprocs;
left = myid -1;
if(left < 0) left = numprocs - 1;
MPI_Irecv(buffer, 10, MPI_INT,left ,123, MPI_COMM_WORLD, &request);
MPI_Isend(buffer2, 10, MPI_INT, right, 123, MPI_COMM_WORLD, &request2);
MPI_Wait(&request, &status);
MPI_Wait(&request2, &status);
MPI_Finalize();
printf("Process status: %d\n----Success on sruti 18bce1005 machine-----\n\n", myid);
return 0;
}
