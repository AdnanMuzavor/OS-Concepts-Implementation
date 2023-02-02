
#include<stdio.h>
#include<stdlib.h>
/// -> Round Robin Schedulling
/// -> Adnan Ismail Shah Muzavor
float avg(int *arr,int n)
{
    int i=0;
    float sum=0.0;
    for(i=0; i<n; i++) sum+=(float)(arr[i]);
    return sum/(float)n;
}
void display(int *tt,int *wt,int n)
{
    int i;

    printf("\nProcess \t Waiting Time \t Turnaround Time");
    for(i=0; i<n; i++)
    {
        printf("\n %d \t\t %d \t\t %d",i+1,wt[i],tt[i]);
    }
    printf("\n Avg \t\t %.2f \t\t %.2f",avg(wt,n),avg(tt,n));
}
void RR(int *pb,int n,int ts,int *rem_btime)
{
    int *wt=(int*)malloc(sizeof(int)*n);
    int *tt=(int*)malloc(sizeof(int)*n);
    int *gantt_processno=(int*)malloc(sizeof(int)*50);
    int *gantt_time=(int*)malloc(sizeof(int)*50);
    int time=0,i=0,gantt_len=0;
    for(i=0; i<n; i++)
    {
        wt[i]=0;
        tt[i]=0;
    }
    while(1)
    {
        int c=1; ///Assume all processes are done/completed

        ///Every tiem loop will start from process 01 i.e first process
        for(i=0; i<n; i++)
        {
            if(rem_btime[i]>0) c=0; ///Process is left

            ///Processs has sufficent burst time left
            if(rem_btime[i]>=ts)
            {
                rem_btime[i]-=ts; ///Process executed for given time slice
                gantt_processno[gantt_len]=i;
                gantt_time[gantt_len]=time;
                gantt_len++;
                time+=ts;

                if(rem_btime[i]==0)
                {
                    ///Process completed, find TT and WT
                    wt[i]=time-pb[i]; ///Method in reference text book
                    tt[i]=wt[i]+pb[i];///TT=WT+BT
                    continue;
                }
            }
            ///Process remaining time is lesser then time slice
            else if(rem_btime[i]!=0 && rem_btime[i]<ts)
            {

                gantt_processno[gantt_len]=i;
                gantt_time[gantt_len]=time;
                gantt_len++;
                time+=rem_btime[i]; ///Burst time lesser then time slice hence we add the btime

                rem_btime[i]=0;
                wt[i]=time-pb[i]; ///Method in reference text book
                tt[i]=wt[i]+pb[i];///TT=WT+BT
            }
        }
        if(c==1)
        {
            ///Completed is true, hence break the outer loop
            break;
        }
    }
    display_gantt(gantt_processno,gantt_time,time,gantt_len);
    display(tt,wt,n);

}
void display_gantt(int *gantt_processno,int * gantt_time,int time,int gantt_len)
{
    int i;
    printf("\n");
    for(i=0; i<gantt_len; i++)
    {
        printf("-----");

    }
    printf("\n");
    for(i=0; i<gantt_len; i++)
    {
        printf("| p%d ",gantt_processno[i]+1);

    }
    printf("|");
    printf("\n");
    for(i=0; i<gantt_len; i++)
    {
        printf("-----");

    }
    printf("\n");
    for(i=0; i<gantt_len; i++)
    {
        if(gantt_time[i]>=10) printf("%d   ",gantt_time[i]);
        else printf(" %d   ",gantt_time[i]);

    }
    printf("%d",time);
    printf("\n");
}

int main()
{
    int n,i,first_p,ts;
    int min_a=1000,min_p=-1,min_b=1000; ///choose process which arrive first.If 2?choose one with min b_time
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    int *p_btime=(int*)malloc(sizeof(int)*n); ///number of processes
    int *btime_cpy=(int*)malloc(sizeof(int)*n); ///Manipulative burst time
    int *pr_order=(int*)malloc(sizeof(int)*n); ///For storing process order
    printf("\nEnter the burst time for each process: \n");
    for(i=0; i<n; i++)
    {
        printf("process: %d : ",i+1);
        scanf("%d",&p_btime[i]);
        btime_cpy[i]=p_btime[i];
    }
    printf("\nEnter the time slice: ");
    scanf("%d",&ts);
    printf("\n");
    printf("Process \t Burst Time");
    for(i=0; i<n; i++)
    {
        printf("\np%d \t\t %d",i+1,p_btime[i]);
    }
    printf("\n");
    printf("\nAfter Round Robin Schedulling: ");
    printf("\n");
    RR(p_btime,n,ts,btime_cpy);

    return 0;
}
