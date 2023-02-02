///Disk Schedulling Shortest Seek Time First
///Adnan Ismail Shah Muzavor
#include<stdio.h>
#include<stdlib.h>
#define MAX 1000;
int i;
int Give_nearest(int *vis,int *ele,int n,int from_ele)
{
    int index=-1,i;
    int min_val=MAX;
    for(i=0; i<n; i++)
    {
        if(!vis[i])
        {
            if(abs(from_ele-ele[i])<min_val)
            {
                min_val=abs(from_ele-ele[i]);
                index=i;
            }
        }
    }

    //printf("\nThe element %d is min diff from ele %d",ele[index],from_ele);
    return index;
}
void SSTF(int n,int ch,int *r,int *e)
{
    int HM=0; /// => Head Movements
    int *vis=(int*)malloc(sizeof(int)*n);
    for(i=0; i<n; i++) vis[i]=0;
    for(i=0; i<n; i++)
    {
        //printf("THe prev ele is: %d",ch);
        int index=Give_nearest(vis,e,n,ch);
        if(index==-1)
        {
            printf("\nUnwanted error!!");
            break;
        }
        vis[index]=1;
        HM+=abs(e[index]-ch);
        ch=e[index];
    }
    printf("\n--------------------------------------------");
    printf("\nBy Disk Schedulling Shortest Seek Time First");
    printf("\n--------------------------------------------");
    printf("\nNumber of Disk Head Movements : %d",HM);
    printf("\n--------------------------------------------");
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
    SSTF(n,Current_head,range,ele);
    return 1;
}
