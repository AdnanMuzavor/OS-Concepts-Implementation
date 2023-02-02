
#include<stdio.h>

typedef struct process
{
    int b_time;
    int rem_btime;
    int prty;
    int a_time;
} prc;
//Without Arrival


//With Arrival
void PP(prc p[],int n)
{
//Sort based on arrival time
    int i,sum=0,tt[n],wt[n],t,c=0;
    for(i=0; i<n; i++)
    {
        tt[i]=wt[i]=0;
    }
    float avgwt=0.0,avgtt=0.0;



    //_________________
    for(t=0; c!=n; t++)
    {
        //Find a process who has arrived
        int selected=-1;
        for(i=0; i<n; i++)
        {
            //If p has arrived
            if(p[i].a_time<=t && p[i].rem_btime!=0)
            {
                //Non selected
                if(selected==-1) selected=i;
                //select one with lesser priority value which means higher priority
                else if( p[i].prty<p[selected].prty) selected=i;
                //if same priority sleect one iwth lesser btime
                else if( p[i].prty==p[selected].prty && p[i].rem_btime<p[selected].rem_btime ) selected=i;
            }
        }
        printf("\nselected process %d at %d",selected,t);
        if(selected!=-1)
        {
            p[selected].rem_btime--;
            if(p[selected].rem_btime==0)
            {
                printf("\n%d findihsed at %d",selected,t);
                wt[selected]=(t-p[selected].b_time-p[selected].a_time+1);  //Formula
                avgwt+=wt[selected];
                tt[selected]=wt[selected]+p[selected].b_time;
                avgtt+=tt[selected];
                c++;
            }
        }
    }

    //_______________
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
        scanf("%d",&p[i].a_time);
        scanf("%d",&p[i].prty);
        p[i].rem_btime=p[i].b_time;
    }
    printf("\n INPUT: \n Prc \t Btime \t Atime");
    for(i=0; i<n; i++)
    {
        printf("\n%d \t %d \t %d",i+1,p[i].b_time,p[i].a_time);
    }
    printf("\n Preemtive Priority \n");
    PP(p,n);

}
