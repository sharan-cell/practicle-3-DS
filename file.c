#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

#define n 10

int a[]={1,2,3,4,5,6,7,8,9,10};
int a2[1000];

int main(int argc,char *argv[]){

int pid,np,element_per_process,n_element_received;
MPI_Status status;
MPI_Init(&argc , &argv);

MPI_Comm_rank(MPI_COMM_WORLD, &pid);
MPI_Comm_size(MPI_COMM_WORLD, &np);

if(pid==0){

int index, i;
element_per_process = (n / np);

if(np>1){

for(int i=0;i<np-1;i++){

index=i*element_per_process;

MPI_Send(&element_per_process,1,MPI_INT,i,0,MPI_COMM_WORLD);
MPI_Send(&a[index],1,MPI_INT,i,0,MPI_COMM_WORLD);

}
index=i*element_per_process;
int element_left = n-index;

MPI_Send(&element_left ,1,MPI_INT,i,0,MPI_COMM_WORLD);
MPI_Send(&a[index],element_left,MPI_INT,i,0,MPI_COMM_WORLD);
}

int sum=0;
for(int i=0;i<element_per_process;i++)
{

sum+=a[i];
}
int temp;
for(int i=1;i<np;i++)

{
MPI_Recv(&temp,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&status);
int sender =status.MPI_SOURCE;
sum+=temp;
}
printf("Sum of array is %d \n",sum);

}

else{

MPI_Recv(&n_element_received,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
}
return 0;
}


