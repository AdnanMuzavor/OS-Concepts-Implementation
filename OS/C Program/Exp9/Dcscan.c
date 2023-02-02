///Disk Schedulling C-SCAN
///Adnan Ismail Shah Muzavor
#include<stdio.h>
#include<stdlib.h>
#define MAX 1000;
int i;
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
    return val;
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
    return val;
}
void SCAN(int n,int ch,int d,int *range,int *e)
{
    int HM=0; /// => Head Movements
    int *vis=(int*)malloc(sizeof(int)*n);
    for(i=0; i<n; i++) vis[i]=0;
    if(d==1)
    {
        printf("\n--------------------------------------------");
        printf("\nDisk Direction is Towards Left");
        /// Logic is that since direction is left,from ch first we shall move to
        /// lower limit in range hence
        HM=abs(range[0]-ch);
        /// => We now move from Left to Right i.e lower to upper limit
        HM+=abs(range[0]-range[1]);
        /// Then from higher limit we move toards left again i.e [TILL NEXT GREATER VALUE AFTER INITIAL HEAD]
        HM+=abs(range[1]-Next_Right_Val_From_CH(n,ch,e));
    }
    else
    {
        printf("\n--------------------------------------------");
        printf("\nDisk Direction is Towards Right");
        /// Logic is that since direction is right,from ch first we shall move to
        /// higher / upper limit in range hence
        HM=abs(range[1]-ch);
        /// => We now move from Right to Left i.e  upper to lower limit
        HM+=abs(range[0]-range[1]);
        /// Then from lower move towrads right [TILL ELEMNT NEAREST TO INITIAL HEAD
        HM+=abs(range[0]-Prev_Left_Val_From_CH(n,ch,e));
    }
    printf("\n--------------------------------------------");
    printf("\nBy Disk Schedulling C-Scan Algorithm");
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
