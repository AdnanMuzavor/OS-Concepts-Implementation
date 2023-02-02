///Page replacement First in First Out Alogorithm
///Adnan Ismail Shah Muzavor
#include<stdio.h>
#include<stdlib.h>

int Check_if_in(int n,int *frame,int key)
{
    int i;
    for(i=0; i<n; i++)
    {
        if(frame[i]==key) return 1;
    }
    return 0;
}
void display(int n,int pageno,int *frame)
{
    int i;
    printf("  %d    |   ",pageno);
    for(i=0; i<n; i++) frame[i]<0?printf("%d ",frame[i]):printf(" %d ",frame[i]);
    printf("\n------------------------\n");
}
void FIFO(int n,int fsz,int *frame,int *pgs)
{
    printf("\n__Applying Page Replacement First Come First Serve Algorithm__");
    printf("\n------------------------\n");
    printf(" Page  |    Frame");
    printf("\n------------------------");
    int inserter=0,i,faults=0;
    printf("\n");
    for(i=0; i<n; i++)
    {
        if(!Check_if_in(fsz,frame,pgs[i]))
        {
            frame[inserter]=pgs[i];
            inserter=(inserter+1)%fsz;
            faults++;
        }

        display(fsz,pgs[i],frame);
    }
     printf("\n------------------------\nNumber of page Faults: %d\n------------------------",faults);
}


int main()
{
    int n,i,fsz;
    printf("Enter the number of pages referenced: ");
    scanf("%d",&n);
    int *pgs=(int*)malloc(sizeof(int)*n);
    printf("\nEnter the pages that are referenced: ");
    for(i=0; i<n; i++)
    {
        scanf("%d",&pgs[i]);
    }
    printf("\nEnter the number of frames: ");
    scanf("%d",&fsz);
    int *frame=(int*)malloc(sizeof(int)*fsz);
    for(i=0; i<fsz; i++) frame[i]=-1;
    FIFO(n,fsz,frame,pgs);
    return 1;
}
