#include<stdio.h>

typedef struct process
{
    int b_time;
    int a_time;
} prc;
//Without Arrival
void FCFS(prc p[],int n)
{
    int wt[n],tt[n],i,sum=0;
    float wtsum=0.0,ttsum=0.0;
    for(i=0; i<n; i++)
    {
        wt[i]=0;
        tt[i]=0;
    }
    printf("\nProcess \t waiting time \t Turnaround time");
    for(i=0; i<n; i++)
    {
        printf("\n %d",i+1);
        if(i>0)
        {
            sum=sum+p[i-1].b_time;
            wt[i]=sum;
            wtsum+=(float)sum;

        }
        printf("\t\t %d",wt[i]);
        tt[i]=wt[i]+p[i].b_time;
        printf("\t\t %d",tt[i]);
        ttsum+=(float)tt[i];
    }


    printf("\nAVG \t\t %.2f \t\t%.2f",wtsum/n,ttsum/n);

}

//With Arrival
void FCFS_A(prc p[],int n)
{
//Sort based on arrival time
    int i,sum=0,tt[n],wt[n];
    for(i=0; i<n; i++)
    {
        tt[i]=wt[i]=0;
    }
    float avgwt=0.0,avgtt=0.0;
    for(i=0; i<n; i++)
    {
        for(int j=0; j<n-1-i; j++)
        {
            if(p[j].a_time>p[j+1].a_time)
            {
                prc temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }

    }
    printf("\n\n After Sorting based on arrival \nPrc \t Btime \t Atime");
    for(i=0; i<n; i++)
    {
        printf("\n%d \t %d \t %d",i+1,p[i].b_time,p[i].a_time);
    }

    printf("\n\n Output \nPrc \t WT \t TT");
    for(i=0; i<n; i++)
    {
        printf("\n %d",i+1);
        if(i>0)
        {
            sum=sum+p[i-1].b_time;
            wt[i]=(sum-p[i].a_time);
            avgwt+=(float)wt[i];
        }

        tt[i]=wt[i]+p[i].b_time;
        avgtt+=(float)tt[i];
        printf("\t %d \t %d",wt[i],tt[i]);
    }
    printf("\nAvg \t %.2f \t %.2f",avgwt/n,avgtt/n);


}
int main()
{
    int n,i;
    printf("Enter processes\n");
    scanf("%d",&n);
    prc p[n];
    printf("Enter B,A time for processes\n");
    for(i=0; i<n; i++)
    {
        printf("%d ",i+1);
        scanf("%d",&p[i].b_time);
        scanf("%d",&p[i].a_time);
    }
    printf("\n INPUT: \n Prc \t Btime \t Atime");
    for(i=0; i<n; i++)
    {
        printf("\n%d \t %d \t %d",i+1,p[i].b_time,p[i].a_time);
    }
    printf("\n Without Arrival \n");
    FCFS(p,n);
    printf("\n With Arrival \n");
    FCFS_A(p,n);
}
