#include<stdio.h>
///Non-Arrival First Come First Serve
///Adnan Ismail Shah Muzavor


#include<stdlib.h>

/// Sorting key will help in sorting
/// when we want to sort values based  on some
/// some other aspect

typedef struct array
{
    int b_time; ///burst_time
    int s_key;  ///sorting key eg priority
} Prc;

///To find average
float avg(int *arr,int n)
{
    float avg=0.0;
    int i=0;
    for(i=0; i<n; i++) avg+=(float)arr[i];
    return (avg/(float)n);
}

///To display the result
void display(int *wt,int *tt,int n)
{
    int i;
    printf("Process\t\tWaiting time\t\tTurnaround time\n");
    for(i=0; i<n; i++)
    {
        printf("  p%d \t\t%d\t\t\t%d\n",i+1,wt[i],tt[i]);
    }
         printf(" avg \t\t%.2f\t\t\t%.2f\n",avg(wt,n),avg(tt,n));
}

void FCFS(Prc p1[],int n)
{
    int*wt=(int*)malloc(sizeof(int)*n);
    int*tt=(int*)malloc(sizeof(int)*n);
    int*gt=(int*)malloc(sizeof(int)*n);
    int sum=0,i,gt_itr=0;
    for(i=0;i<n;i++) gt[i]=0;
    wt[0]=0; //Initially waiting time is zero for first process in p1
    gt[gt_itr]=0;

    for( i=0; i<n; i++)
    {
        ///Calculate waiting time
        if(i>0)
        {
            /// for i=0, we already know waiting time is zero
            /// otherwise it is burst time of prev process
            sum=sum+p1[i-1].b_time; /// Burst time of ith process
            wt[i]=sum;

        }
        ///Calculate turnround time
        tt[i]=p1[i].b_time+sum;
        gt[gt_itr]=sum;
        gt_itr++;
    }
    gt[gt_itr]=sum+p1[n-1].b_time;
    gt_itr++;
    display(wt,tt,n);
    ganttchart(p1,gt,n,gt_itr);
}

void ganttchart(Prc *p,int*gt,int n,int n2){
    int i;
    printf("\nGantt chart is: \n");
    for(i=0;i<n;i++){
        printf("------");
    }
    printf("\n");
    for(i=0;i<n;i++){
        printf(" p%d  |",i+1);
    }
    printf("\n");
        for(i=0;i<n;i++){
        printf("------");
    }
      printf("\n");
    for(i=0; i<n2; i++)
    {
        printf("%d    ",gt[i]);
    }
}
int main()
{
    int n,i;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    Prc *p1=(Prc*)malloc(sizeof(Prc)*n);
    printf("\nEnter the burst time for: \n");
    for(i=0; i<n; i++)
    {
        printf("Process %d: ",i+1);
        scanf("%d",&p1[i].b_time);
        p1[i].s_key=-1;
        //printf("\n");
    }
    printf("Process\t\tBurst time\n");
    for(i=0; i<n; i++)
    {
        printf("  p%d \t\t%d\n",i+1,p1[i].b_time);
    }
    printf("\nFirst Come First Serve:\n");
    FCFS(p1,n);

    return 0;
}
