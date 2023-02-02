
#include<stdio.h>
///With Arrival Non Pre-emtive priority
///Adnan Ismail Shah Muzavor


#include<stdlib.h>

/// Sorting key will help in sorting
/// when we want to sort values based  on some
/// some other aspect

typedef struct array
{
    int b_time; ///burst_time
    int a_time; ///arrival time
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
void display(int *order,int *wt,int *tt,int n)
{
    int i;
    printf("Process\t\tWaiting time\t\tTurnaround time\n");
    for(i=0; i<n; i++)
    {
        printf("p%d \t\t%d\t\t\t%d\n",order[i]+1,wt[i],tt[i]);
    }
    printf("avg \t\t%.2f\t\t\t%.2f\n",avg(wt,n),avg(tt,n));
}



///Display the input/sorted/processed input
void raw_display(int order[],Prc p1[],int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        printf(" p%d \t\t%d\t\t\t%d\t\t\t%d\n",order[i]+1,p1[i].a_time,p1[i].b_time,p1[i].s_key);
    }
}

int decide_first(Prc p1[],int processed[],int n,int prev_burst_time)
{
    int first_p=-1,min_arrival_time=1000,highest_priority=1000,i=0,min_b_time=1000; ///this is used only when processes hv sme priority

    ///Choose the first process to execute
    if(prev_burst_time==-1)
    {

        for(i=0; i<n; i++)
        {
            ///THe proces has arrival time lesser thn minimum arrival time so far
            if(p1[i].a_time!=min_arrival_time && p1[i].a_time<min_arrival_time)
            {
                min_arrival_time=p1[i].a_time;
                highest_priority=p1[i].s_key;
                first_p=i;
            }
            ///If process has same minimum arrival time, thn check for burst time
            ///Consider the one with minimum burst time
            else if(p1[i].a_time==min_arrival_time && p1[i].s_key<highest_priority)
            {
                min_arrival_time=p1[i].a_time;
                highest_priority=p1[i].s_key;
                first_p=i;

            }
        }
    }
    else
    {
        ///No process executed therefore return process that will execute first

        for(i=0; i<n; i++)
        {
            ///If this process is not already included
            if(!processed[i])
            {

                ///If proces had arrived while prev was executing
                if( p1[i].a_time<prev_burst_time)
                {
                    ///If we have not selected any process as of now
                    if(first_p==-1)
                    {
                        first_p=i; ///Choose this process and thn look for other process;
                        highest_priority=p1[i].s_key;
                        min_b_time=p1[i].b_time;
                        continue;
                    }
                    ///If this process has lesser burst time thn proces we had arrived during this within same range
                    ///i.e while prev process was executing
                    if(p1[i].s_key<highest_priority)
                    {

                        highest_priority=p1[i].s_key;
                        min_b_time=p1[i].b_time;
                        first_p=i;
                    }
                     else if(p1[i].s_key==highest_priority && p1[i].b_time<min_b_time){
                        min_b_time=p1[i].b_time;
                        first_p=i;
                     }
                }
            }
        }
    }
    ///No new process found to be arrive within given burst time
        if(first_p==-1)
    {
        int min_till_now=1000;
        highest_priority=10000;
        for(i=0; i<n; i++)
        {
            if(!processed[i])
            {
                int min_diff=p1[i].a_time-prev_burst_time;
                if(min_diff<min_till_now && p1[i].s_key<highest_priority )
                {
                    first_p=i;
                    min_till_now=min_diff;
                    highest_priority=p1[i].s_key;

                }
                else if(min_diff==min_till_now && p1[i].s_key<highest_priority){
                    first_p=i;
                    highest_priority=p1[i].s_key;
                }
            }
        }
    };
    if(first_p==-1) return -1;
    processed[first_p]=1;
    return first_p;

}
int max(int a,int b)
{
    if(a>b) return a;

    return b;
}
void decide_order(Prc p1[],int order[],int n)
{
    int soln[n]; ///Processes as per order of execution
    Prc soln_p[n];
    int new_order[n];
    int k=0,i=0;

    ///To keep track of process to be executed first
    int prev_process,max_b_time,min_arrival_time=1000,min_burst_time=1000;

    int processed[n+1]; ///Non of pocesses are processed
    for(i=0; i<n; i++) processed[i]=0;

    ///k<n i/e while all n processes are not scheduled
    i=0;
    while(i<n)
    {
        if(k==0)
        {
            soln[k]=decide_first(p1,processed,n,-1);
            new_order[k]=soln[k];
            prev_process=soln[k];
            max_b_time=p1[soln[k]].a_time;
            k++;
            i++;
        }
        else
        {
            max_b_time+=p1[prev_process].b_time;
            int p=decide_first(p1,processed,n,max_b_time);
            if(p==-1)
            {
                i++;
                continue; ///No iteration
            }
            new_order[k]=p;
            soln[k]=p;
            prev_process=soln[k];
            k++;
            i++;
        }
    }
    ///As per solution order design the arrange the processes
    for(i=0; i<n; i++)
    {
        soln_p[i]=p1[soln[i]];
    }
    ///Rearrange processes
    for(i=0; i<n; i++)
    {
        p1[i]=soln_p[i];
        order[i]=new_order[i];
    }
}
void NPP_A(Prc p1[],int order[],int n)
{
    int i,sum=0,gt_itr=0;
    int*wt=(int*)malloc(sizeof(int)*n);
    int*tt=(int*)malloc(sizeof(int)*n);
    int*bb=(int*)malloc(sizeof(int)*n);
    int*gt=(int*)malloc(sizeof(int)*n);
    for(i=0; i<n; i++)
    {
        bb[i]=0;
        gt[i]=0;
    }
    decide_order(p1,order,n);
    ///On this order run first come firts serve aogorithm
    wt[0]=0;            ///Initially waiting time is zero for first process in p1
    gt[0]=p1[0].a_time; ///As we will be executing processes right from first process which min arrival time
    ///It's not necesssary that this arrival time will always be zero
    sum=p1[0].a_time;   ///AHence w eare adding up this time in sum as well!!
    for( i=0; i<n; i++)
    {
        ///Calculate waiting time
        if(i>0)
        {
            /// for i=0, we already know waiting time is zero
            /// otherwise it is burst time of prev process
            sum=sum+p1[i-1].b_time; /// Burst time of ith process
            wt[i]=(sum-p1[i].a_time);
            ///If process arrived much later while prev process was executing
            if(p1[i].a_time>sum)
            {
                ///Thr process doent has to wait
                wt[i]=0;
                bb[i]=100;
                gt[gt_itr]=sum;
                gt_itr++;
                ///Add to burst time and time of this blank slot
                sum+=(p1[i].a_time-sum); //Add time taken by blank slot

            }
            gt[gt_itr]=sum;

        }
        ///Calculate turnround time
        tt[i]=p1[i].b_time+wt[i];
        gt_itr++;
    }
    ///Add burst time of last process
    gt[gt_itr]=sum+p1[n-1].b_time;
    gt_itr++;
    printf("\n");
    display(order,wt,tt,n);
    ganttchart(order,gt,bb,n,gt_itr);
}

void ganttchart(int *order,int*gt,int* bb,int n,int n2)
{
    int i;
    printf("\nGantt chart is: \n");
    for(i=0; i<n; i++)
    {
        if(bb[i]) printf("-----");
        printf("-----");
    }
    printf("\n");
    for(i=0; i<n; i++)
    {
        if(bb[i]==0) printf(" p%d |",order[i]+1);
        else printf(" --| p%d |",order[i]+1);
    }
    printf("\n");
    for(i=0; i<n; i++)
    {
        if(bb[i]) printf("-----");
        printf("-----");
    }
    printf("\n");
    for(i=0; i<n2; i++)
    {
        printf("%d   ",gt[i]);
    }
}

int main()
{
    int n,i;


    printf("Enter the number of processes: ");
    scanf("%d",&n);
    Prc *p1=(Prc*)malloc(sizeof(Prc)*n);
    int *pr_order=(int*)malloc(sizeof(int)*n); ///For storing process order

    for(i=0; i<n; i++) pr_order[i]=i;


    printf("\nEnter the BURST time,PRIORITY , ARRIVAL time  for: \n");
    for(i=0; i<n; i++)
    {
        printf("Process %d: ",i+1);
        scanf("%d",&p1[i].b_time);
        scanf("%d",&p1[i].s_key);
        scanf("%d",&p1[i].a_time);
    }
    printf("Process\t\tArrival time\t\tBurst time\t\tPriority\n");
    raw_display(pr_order,p1,n);
    ///FCFS_A(p1,pr_order,n);
    NPP_A(p1,pr_order,n);
    return 0;
}
