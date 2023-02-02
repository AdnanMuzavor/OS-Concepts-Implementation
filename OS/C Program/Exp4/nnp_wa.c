#include<stdio.h>
///Non-Arrival Non-preemtive priority
///Adnan Ismail Shah Muzavor


#include<stdlib.h>

/// Sorting key will help in sorting
/// when we want to sort values based  on some
/// some other aspect

typedef struct array
{
    int b_time; ///burst_time
    int s_key;  ///sorting key i.e priority
} Prc;


///In THIS ALGO WE NEED TO SORT NUMBERS
///I.E BURST TIME FROM SMALL TO LARGE SO THAT
///SHORTST PROCESS EXECUTES FIRST
void merge(int l,int m,int h,Prc p1[],int order[])
{
    ///id s_key is one use sort key else sort directly
    int temp[h-l+1];
    int new_order[h-l+1];
    int prty[h-l+1];
    int i=l,j=m+1,k=0;
    while(i<=m && j<=h)
    {

            if(p1[i].s_key<=p1[j].s_key)
            {
                temp[k]=p1[i].b_time;
                new_order[k]=order[i];
                prty[k]=p1[i].s_key;
                i++;
                k++;
            }
            else
            {
                temp[k]=p1[j].b_time;
                prty[k]=p1[j].s_key;
                new_order[k]=order[j];
                j++;
                k++;
            }


    }
    ///Add remaining elemnts
    while(i<=m)
    {
        temp[k]=p1[i].b_time;
        prty[k]=p1[i].s_key;
        new_order[k]=order[i];
        k++;
        i++;
    }
    ///Add remaining elemnts
    while(j<=h)
    {
        temp[k]=p1[j].b_time;
        prty[k]=p1[j].s_key;
        new_order[k]=order[j];
        k++;
        j++;
    }
    ///Modify original array
    i=l,k=0;
    while(i<=h)
    {
        p1[i].b_time=temp[k];
        order[i]=new_order[k];
        p1[i].s_key=prty[k];
        i++;
        k++;
    }
}
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


///To find average
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
        printf("  p%d \t\t%d\t\t\t%d\n",order[i]+1,wt[i],tt[i]);
    }
         printf(" avg \t\t%.2f\t\t\t%.2f\n",avg(wt,n),avg(tt,n));
}

void NPP(Prc p1[],int*order,int n)
{
    int*wt=(int*)malloc(sizeof(int)*n);
    int*tt=(int*)malloc(sizeof(int)*n);
    int*gt=(int*)malloc(sizeof(int)*n);
    int sum=0,i,gt_itr=0;
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
    display(order,wt,tt,n);
    ganttchart(p1,order,gt,n,gt_itr);
}


void ganttchart(Prc *p,int*order,int*gt,int n,int n2){
    int i;
    printf("\nGantt chart is: \n");
    for(i=0;i<n;i++){
        printf("-----");
    }
    printf("\n");
    for(i=0;i<n;i++){
        printf(" p%d |",order[i]+1);
    }
    printf("\n");
        for(i=0;i<n;i++){
        printf("-----");
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

    Prc *p1=(Prc*)malloc(sizeof(Prc)*n); ///Storing values of the array
    int *pr_order=(int*)malloc(sizeof(int)*n); ///For storing process order

    for(i=0; i<n; i++) pr_order[i]=i;

    printf("\nEnter the burst time and priority for: \n");
    for(i=0; i<n; i++)
    {
        printf("Process %d: ",i+1);
        scanf("%d%d",&p1[i].b_time,&p1[i].s_key);
    }
    printf("Process\t\tBurst time\t\tPriority\n");
    for(i=0; i<n; i++)
    {
        printf(" p%d \t\t%d\t\t\t%d\n",pr_order[i]+1,p1[i].b_time,p1[i].s_key);
    }
    mergesort(0,n-1,p1,pr_order); ///Sort based on s only s_key i.e priority

    printf("\nAfter Non preemtive Priority Scheduling:\n");
    NPP(p1,pr_order,n);
    return 0;
}
