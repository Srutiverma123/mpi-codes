#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define n 8

int date[n];

int main(int argc, char* argv[])
{
int pid, np, k, nRec, i;

MPI_Status status;
MPI_Init(&argc, &argv);

MPI_Comm_rank(MPI_COMM_WORLD, &pid);
MPI_Comm_size(MPI_COMM_WORLD, &np);

if (pid == 0) {

printf("Enter Birthday: \n");
for(i = 0; i<n ;i++)
scanf("%i",&date[i]);
int index;
k = n /(np-1);

if (np > 1) {
for (i = 1; i < np - 1; i++) {
index = (i-1) * k;
MPI_Send(&k,  1, MPI_INT, i, 0,  MPI_COMM_WORLD);
MPI_Send(&date[index],  k,  MPI_INT, i, 0, MPI_COMM_WORLD);
}

index = (i-1) * k;
int rem = n - index;
MPI_Send(&rem,  1, MPI_INT,  i, 0,  MPI_COMM_WORLD);
MPI_Send(&date[index],  rem,  MPI_INT, i, 0,  MPI_COMM_WORLD);
}

int sum = 0;
int tmp = 0;
for (i = 1; i < np; i++) {
MPI_Recv(&tmp, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
sum += tmp;
}
printf("Sum of date is : %d\n", sum);

}

else {
MPI_Recv(&nRec, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
MPI_Recv(&date, nRec, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

int sum = 0;
for (int i = 0; i < nRec; i++)
sum += date[i];
MPI_Send(&sum , 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
}
if(pid==0)
printf("18bce1005 Sruti Verma \n");
MPI_Finalize();

return 0;
} 

