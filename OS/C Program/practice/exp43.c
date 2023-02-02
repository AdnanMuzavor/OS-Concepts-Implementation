#include<stdio.h>

typedef struct process
{
    int b_time;
    int a_time;
    int prty;
} prc;
//Without Arrival
void NPP(prc p[],int n)
{
    int wt[n],tt[n],i,sum=0;
    float wtsum=0.0,ttsum=0.0;
    for(i=0; i<n; i++)
    {
        wt[i]=0;
        tt[i]=0;
    }
    for(i=0; i<n; i++)
    {
        for(int j=0; j<n-1-i; j++)
        {
            if(p[j].prty>p[j+1].prty)
            {
                prc temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }

    }
    printf("\n\n After Sorting based on Priority \nPrc \t Btime \t Atime \t Prty");
    for(i=0; i<n; i++)
    {

        printf("\n%d \t %d \t %d  \t %d",i+1,p[i].b_time,p[i].a_time,p[i].prty);

    }
    printf("\n\n Output: \nProcess \t waiting time \t Turnaround time");
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
void NPP_A(prc p[],int n)
{
//Sort based on arrival time
    int i,sum=0,tt[n],wt[n],processed[n];
    float wtsum=0.0,ttsum=0.0;
    for(i=0; i<n; i++)
    {
        tt[i]=wt[i]=processed[i]=0;
    }
    printf("\n\n Output \nPrc \t WT \t TT");
    //___________________________________________________
    int t=0,c=0,prev_select=-1;
    while(1)
    {
        int select=-1,selected_prty=-1;
        for(i=0; i<n; i++)
        {

            if(select==-1 && selected_prty==-1)
            {
                if(!processed[i] && p[i].a_time<=t)
                {

                    select=i;
                    selected_prty=p[i].prty;

                }
            }
            else
            {
                if(!processed[i] && p[i].prty<selected_prty && p[i].a_time<=t)
                {
                    select=i;
                    selected_prty=p[i].prty;

                }

            }
        }
        if(select==-1)
        {
            printf("\n_____No process selected");
            t++;
            sum++;
            continue;
        }

        t+=p[select].b_time;

        processed[select]=1;

        printf("\n%d \t",select);
        if(c>0)
        {
            sum=sum+p[prev_select].b_time;
            wt[select]=(sum-p[select].a_time);
            wtsum+=(float)wt[select];
        }
        tt[select]=wt[select]+p[select].b_time;
        ttsum+=(float)tt[select];
        prev_select=select;
        printf(" %d \t %d",wt[select],tt[select]);
        c++;
        if(c==n) break;
    }
    printf("\nAvg \t %.2f \t %.2f",wtsum/n,ttsum/n);
    //________________________________________________


}
int main()
{
    int n,i;
    printf("Enter processes\n");
    scanf("%d",&n);
    prc p[n];
    printf("Enter B,A,P time for processes\n");
    for(i=0; i<n; i++)
    {
        printf("%d ",i+1);
        scanf("%d",&p[i].b_time);
        scanf("%d",&p[i].a_time);
        scanf("%d",&p[i].prty);
    }
    printf("\n INPUT: \n Prc \t Btime \t Atime \t Prty");
    for(i=0; i<n; i++)
    {
        printf("\n%d \t %d \t %d \t %d",i+1,p[i].b_time,p[i].a_time,p[i].prty);
    }
    printf("\n Without Arrival \n");
    //  NPP(p,n);
    printf("\n With Arrival \n");
    NPP_A(p,n);
}
