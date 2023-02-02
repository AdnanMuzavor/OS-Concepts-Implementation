
#include<stdio.h>
#include<stdlib.h>
/// -> Preemtive Priority Schedulling
/// -> Adnan Ismail Shah Muzavor

#define MAX 1000
typedef struct array
{
    int b_time; ///burst_time
    int a_time; ///arrival time
    int rem_btime; ///manipulative btime
    int priority; ///priority of process
} Prc;

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
    printf("\n");
    printf("\nProcess \t Waiting Time \t Turnaround Time");
    for(i=0; i<n; i++)
    {
        printf("\n %d \t\t %d \t\t %d",i+1,wt[i],tt[i]);
    }
    printf("\n Avg \t\t %.2f \t\t %.2f",avg(wt,n),avg(tt,n));
}

///Display the input/sorted/processed input
void raw_display(int order[],Prc p1[],int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        printf(" p%d \t\t%d\t\t\t%d\t\t\t%d\n",order[i]+1,p1[i].a_time,p1[i].b_time,p1[i].priority);
    }
}


void PPS(Prc *p,int first_p,int n)
{
    int count=0; ///No processses completed as yet
    int time=0,i=0,gantt_len=0;     ///We will increment timer b y one each time
    int select_process=-1;
    int *wt=(int*)malloc(sizeof(int)*n);
    int *tt=(int*)malloc(sizeof(int)*n);
    int *gantt_processno=(int*)malloc(sizeof(int)*50);
    int *gantt_time=(int*)malloc(sizeof(int)*50);
    for(i=0; i<n; i++)
    {
        wt[i]=0;
        tt[i]=0;
    }

    ///Iterate until all processes are done
    for(time=0; count!=n; time++)
    {
        int small=MAX;
        select_process=-1; ///No process is selected

        ///1) ->  Process selection
        ///Find process which had arrived udring this time
        ///If many consider one with minimum rem_btime
        for(i=0; i<n; i++)
        {

            ///If process had arrived and  it's not completed process
            if(p[i].a_time<=time && p[i].rem_btime!=0)
            {
                ///If no0 processs was selected select this
                if(select_process==-1)select_process=i;

                ///If this process has higher priority, execute it
                else if(p[i].priority<p[select_process].priority) select_process=i;

                ///If this process has same priority but lesser remaining burst time
                else if(p[i].priority==p[select_process].priority && p[i].rem_btime<p[select_process].rem_btime) select_process=i;
            }

        }

        ///2) Since we are executing at rate of 1 second
        ///   decrese the burst time for this process by only if selected

        ///If process was selected
        if(select_process!=-1)
        {

            ///add detials in gantt chart
            gantt_processno[gantt_len]=select_process;
            gantt_time[gantt_len]=time;
            gantt_len++;

            ///decrement it's b time  by one

            p[select_process].rem_btime--;

            ///If process completed it's execution, calculate waiting and turn around time
            if(p[select_process].rem_btime==0)
            {
                wt[select_process]=time-p[select_process].b_time-p[select_process].a_time+1; ///+1 because execution will finish at time+1
                tt[select_process]=wt[select_process]+p[select_process].b_time;
                ///Increment counter by one as one process completed the execution
                count++;
            }
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
}
///To take inputs
void input(Prc *p,int* p_order,int n)
{

    int i;
    int min_a=1000,min_p=-1,min_b=1000; ///choose process which arrive first.If 2?choose one with min b_time
    for(i=0; i<n; i++) p_order[i]=i;


    printf("\nEnter the BURST time, ARRIVAL time and PRIORITY for: \n");
    for(i=0; i<n; i++)
    {
        printf("Process %d: ",i+1);
        scanf("%d",&p[i].b_time);
        scanf("%d",&p[i].a_time);
        scanf("%d",&p[i].priority);
        p[i].rem_btime=p[i].b_time;

    }

    printf("Process\t\tArrival time\t\tBurst time\t\tPriority\n");
    raw_display(p_order,p,n);

}

int main()
{
    int n,i,first_p;
    int min_a=1000,min_p=-1,min_b=1000; ///choose process which arrive first.If 2?choose one with min b_time
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    Prc *p1=(Prc*)malloc(sizeof(Prc)*n);
    int *pr_order=(int*)malloc(sizeof(int)*n); ///For storing process order
    input(p1,pr_order,n);
    printf("\nAfter Preemtive Priority Schedulling Schedulling: ");
    printf("\n");
    PPS(p1,pr_order,n);
    return 0;
}
