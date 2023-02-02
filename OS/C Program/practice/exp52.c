
#include<stdio.h>

typedef struct process
{
    int b_time;
    int rem_btime;
    int prty;
    int a_time;
} prc;

void RR(prc p[],int n)
{
    int wt[n],tt[n],i=0;
    float avgwt=0.0,avgtt=0.0;
    //assume time slice=2
    int ts=2,t=0;
    for(i=0; i<n; i++)
    {
        wt[i]=tt[i]=0;
    }
    while(1)
    {
        //Assume all done
        int all_done=1;
        //check if any undone
        for(i=0; i<n; i++)
        {
            if(p[i].rem_btime!=0) all_done=0;
            //Execute the current process
            if(p[i].rem_btime>=ts)
            {
                printf("\nselected %d",i);
                p[i].rem_btime-=ts;
                t=t+ts; //As we exeuted a process for certain time
                if(p[i].rem_btime==0)
                {
                    printf("\n%d finished at %d",i,t);
                    wt[i]=t-p[i].b_time;
                    tt[i]=wt[i]+p[i].b_time;
                    avgtt+=tt[i];
                    avgwt+=wt[i];
                    continue;
                }
            }
            else if(p[i].rem_btime!=0 && p[i].rem_btime<ts)
            {
printf("\nselected %d",i);
                t=t+p[i].rem_btime;
                printf("\n%d finished at %d",i,t);
                p[i].rem_btime=0;
                wt[i]=t-p[i].b_time;
                tt[i]=wt[i]+p[i].b_time;
                avgtt+=tt[i];
                avgwt+=wt[i];
            }
        }


        //If all done break
        if(all_done==1) break;
    }
    printf("\n\n Output \nPrc \t WT \t TT");
    for(i=0; i<n; i++)
    {
        printf("\n %d",i+1);

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
    printf("Enter B,A,P time for processes\n");
    for(i=0; i<n; i++)
    {
        printf("%d ",i+1);
        scanf("%d",&p[i].b_time);
        p[i].rem_btime=p[i].b_time;
    }
    printf("\n INPUT: \n Prc \t Btime");
    for(i=0; i<n; i++)
    {
        printf("\n%d \t %d ",i+1,p[i].b_time);
    }
    printf("\n Preemtive Priority \n");
    RR(p,n);

}
