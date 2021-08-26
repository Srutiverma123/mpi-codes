#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>

void my_bcast(int* data, int count, MPI_Datatype datatype, int root, MPI_Comm communicator)
{
	int world_rank;
	MPI_Comm_rank(communicator, &world_rank); 
	int world_size;
	MPI_Comm_size(communicator, &world_size);
	if(world_rank == root)
	{
		printf("Hello i am root i am sending data,my rank is%d\n",world_rank);
		int i;
		for(i =0;i<world_size; i++)
		{
			if(i != world_rank)
			{
				MPI_Send(data, count, datatype, i, 0, communicator);
				printf("The message is sent to process: %d\nTheis node has finished stock: %d\n\n", i, *data);
			}
		}
	}
	else
	{
		MPI_Recv(data, count, datatype, root, 0, communicator, MPI_STATUS_IGNORE);
		printf("The message is received by process: %d\nThe node which has finished stock is: %d\n\n",world_rank, *data);
	}
}
void display(int* arr)
{
for(int i=0;i<4;i++)
{
printf("status of node %d is %d\n",i,arr[i]);
}
}
void funct(int id,int* arr,int count,int z,int fin)

{
arr[id]--;
printf("value of %d is %d\n",id,arr[id]);
if(arr[id]==0){
printf("hi");
z=1;
}
if(z==1 && id==0){
z=0;
int var;
	int *dataNumber=&var;
	*dataNumber = 10;
	my_bcast(dataNumber, 1, MPI_INT, 0, MPI_COMM_WORLD);
}
int var=arr[id];
int* arr1=NULL;
if (id == 0) {
  arr1=malloc(sizeof(int) *4);
}
MPI_Gather(&var, 1, MPI_INT,arr1, 1, MPI_INT, 0,
           MPI_COMM_WORLD);
if (id == 0) {
  display(arr1);
}

}



int main()

{

MPI_Init(NULL,NULL);

int arr[4]={25,25,25,25};

int count=0;

int id,p;
int z=0,fin;
MPI_Comm_rank(MPI_COMM_WORLD,&id);

MPI_Comm_size(MPI_COMM_WORLD,&p);

for(int i=id;i<100;i=i+p)

{
count++;
funct(id,arr,count,z,fin);
}
MPI_Finalize();
}
