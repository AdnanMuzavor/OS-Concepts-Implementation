///Disk Schedulling C-Look
///Adnan Ismail Shah Muzavor
#include<stdio.h>
#include<stdlib.h>
#define MAX 1000;
int i;
int Min_Val(int n,int *ele)
{
    int i,min_ele=MAX;
    for(i=0; i<n; i++)
    {
        if(ele[i]<min_ele)
        {
            min_ele=ele[i];
        }
    }
    return min_ele;
}
int Max_Val(int n,int *ele)
{
    int i,max_ele=-1;
    for(i=0; i<n; i++)
    {
        if(ele[i]>max_ele)
        {
            max_ele=ele[i];
        }
    }
    return max_ele;
}

int Prev_Left_Val_From_CH(int n,int ch,int *ele)
{
    int val=-1,min_diff=MAX;
    for(i=0; i<n; i++)
    {
        if(ele[i]<=ch && abs(ele[i]-ch)<min_diff)
        {
            val=ele[i];
            min_diff=abs(ele[i]-ch);
        }
    }
   /// printf("\nValue nearest to %d from left is: %d and min_val: %d",ch,val,Min_Val(n,ele));
    return val;
}

int Next_Right_Val_From_CH(int n,int ch,int *ele)
{
    int val=-1,min_diff=MAX;
    for(i=0; i<n; i++)
    {
        if(ele[i]>=ch && abs(ele[i]-ch)<min_diff)
        {
            val=ele[i];
            min_diff=abs(ele[i]-ch);
        }
    }
   /// printf("\nValue nearest to %d from right is: %d and min_val: %d",ch,val,Max_Val(n,ele));

    return val;
}
void SCAN(int n,int ch,int d,int *range,int *e)
{
    int HM=0; /// => Head Movements
    int *vis=(int*)malloc(sizeof(int)*n);
    for(i=0; i<n; i++)
        vis[i]=0;
    if(d==1)
    {
        printf("\n--------------------------------------------");
        printf("\nDisk Direction is Towards Left");
        /// Logic is that since direction is left,from ch first we shall move to
        /// lower limit in range hence
        HM=abs(Min_Val(n,e)-ch);
        /// Then from minimum range i.e left we shall move towards the highest value in the queue
        HM+=abs(Min_Val(n,e)-Max_Val(n,e));
        /// Then from higher value in queue we cover till value nearest greater then [INITIAL HEAD]
        HM+=abs(Max_Val(n,e)-Next_Right_Val_From_CH(n,ch,e));
    }
    else
    {
        printf("\n--------------------------------------------");
        printf("\nDisk Direction is Towards Right");
        /// Logic is that since direction is right,from ch first we shall move to
        /// highr / upper limit in range hence
        HM=abs(Max_Val(n,e)-ch);
        /// Then from higher limit i.e right we shall move towards the lowest value in the queue
        HM+=abs(Max_Val(n,e)-Min_Val(n,e));
        ///Then from lowest value we cover remaining values left before starting [INITIAL HEAD POSITION]
        HM+=abs(Min_Val(n,e)-Prev_Left_Val_From_CH(n,ch,e));
    }
    printf("\n--------------------------------------------");
    printf("\nBy Disk Schedulling C-Look Algorithm");
    printf("\n--------------------------------------------");
    printf("\nNumber of Disk Head Movements : %d",HM);
    printf("\n--------------------------------------------");
}
int main()
{
    int n,Current_head,d;
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
    printf("\nEnter the direction of disk movement (1)=>Left, (2)=>Right: ");
    scanf("%d",&d);
    SCAN(n,Current_head,d,range,ele);
    return 1;
}
