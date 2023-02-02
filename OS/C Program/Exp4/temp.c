#include<stdio.h>
///With Arrival First Come First Serve
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
        printf(" p%d \t\t%d\t\t\t%d\n",order[i]+1,wt[i],tt[i]);
    }
    printf("avg \t\t%f\t\t%f\n",avg(wt,n),avg(tt,n));
}

void merge(int l,int m,int h,Prc p1[],int order[])
{
    ///id s_key is one use sort key else sort directly
    int temp[h-l+1];
    int temp2[h-l+1];
    int new_order[h-l+1];
    int i=l,j=m+1,k=0;
    while(i<=m && j<=h)
    {

        if(p1[i].a_time<=p1[j].a_time)
        {
            temp[k]=p1[i].b_time;
            temp2[k]=p1[i].a_time;
            new_order[k]=order[i];
            i++;
            k++;
        }
        else
        {
            temp[k]=p1[j].b_time;
            temp2[k]=p1[j].a_time;
            new_order[k]=order[j];
            j++;
            k++;
        }
    }
    ///Add remaining elemnts
    while(i<=m)
    {
        temp[k]=p1[i].b_time;
        temp2[k]=p1[i].a_time;
        new_order[k]=order[i];
        k++;
        i++;
    }
    ///Add remaining elemnts
    while(j<=h)
    {
        temp[k]=p1[j].b_time;
        temp2[k]=p1[j].a_time;
        new_order[k]=order[j];
        k++;
        j++;
    }
    ///Modify original array
    i=l,k=0;
    while(i<=h)
    {
        p1[i].b_time=temp[k];
        p1[i].a_time=temp2[k];
        order[i]=new_order[k];
        i++;
        k++;
    }
}

///sort p1 based on a_key i.e arrival time
void mergesort(int i,int j,Prc p1[],int order[])
{
    if(i<j)
    {
        int m=(i+j)/2;
        mergesort(i,m,p1,order);
        mergesort(m+1,j,p1,order);
        merge(i,m,j,p1,order);

    }
}

///Display the input/sorted/processed input
void raw_display(int order[],Prc p1[],int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        printf(" p%d \t\t%d\t\t\t%d\n",order[i]+1,p1[i].a_time,p1[i].b_time);
    }
}

void FCFS_A(Prc p1[],int order[],int n)
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
    ///Before doing anything for sort processes based on arrival time
    ///As process which arrived first will be served first
    mergesort(0,n-1,p1,order);
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

    printf("\nEnter the BURST time and ARRIVAL time for: \n");
    for(i=0; i<n; i++)
    {
        printf("Process %d: ",i+1);
        scanf("%d",&p1[i].b_time);
        scanf("%d",&p1[i].a_time);
        p1[i].s_key=-1;
    }
    printf("Process\t\tArrival time\t\tBurst time\n");
    raw_display(pr_order,p1,n);
    printf("Aftre Firts Come First Serve Schedulling: ");
    FCFS_A(p1,pr_order,n);
    return 0;
}
