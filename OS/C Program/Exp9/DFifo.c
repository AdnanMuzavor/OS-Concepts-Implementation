///Disk Schedulling First In First Out Algorithm
///Adnan Ismail Shah Muzavor
#include<stdio.h>
#include<stdlib.h>
int i;
void FIFO(int n,int ch,int *r,int *e)
{
    int HM=0; /// => Head Movements
    for(i=0; i<n; i++)
    {
        if(i==0) HM+=abs(e[i]-ch);
        else HM+=abs(e[i]-e[i-1]);
    }
    printf("\n---------------------------------------------------");
    printf("\nBy Disk Schedulling First Come First Serve Algorithm");
    printf("\n---------------------------------------------------");
    printf("\nNumber of Disk Head Movements : %d",HM);
    printf("\n---------------------------------------------------");
}
int main()
{
    int n,Current_head;
    printf("Enter the number of elements in disk queue: ");
    scanf("%d",&n);
    int *ele=(int*)malloc(sizeof(int)*n);
    printf("\nEnter the elements in disk queue: ");
    for(i=0; i<n; i++)
    {
        scanf("%d",&ele[i]);
    }
    int *range=(int*)malloc(sizeof(int)*2);
    printf("\nEnter the range of cylinder: ");
    scanf("%d",&range[0]);
    scanf("%d",&range[1]);
    printf("\nEnter the position of current head: ");
    scanf("%d",&Current_head);
    FIFO(n,Current_head,range,ele);
    return 1;
}
