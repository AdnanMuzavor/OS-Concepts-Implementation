#include<stdio.h>



int main()
{
    int n,r,i,j;
    printf("\nEnter number of processes and resources");
    scanf("%d %d",&n,&r);
    int alloc[n][r];
    int max[n][r];
    printf("\nEnter allocated matrix");
    for(i=0; i<n; i++)
    {
        printf("\nProcess %d : ",i);
        for(j=0; j<r; j++)
        {
            scanf("%d",&alloc[i][j]);
        }

    }
    printf("\nEnter MAX matrix");
    for(i=0; i<n; i++)
    {
        printf("\nProcess %d : ",i);
        for(j=0; j<r; j++)
        {
            scanf("%d",&max[i][j]);
        }

    }
    printf("\nAllocated matrix");
    for(i=0; i<n; i++)
    {
        printf("\nProcess %d : ",i);
        for(j=0; j<r; j++)
        {
            printf("%d ",alloc[i][j]);
        }
        printf("\n");

    }
    printf("\nMAX matrix");
    for(i=0; i<n; i++)
    {
        printf("\nProcess %d : ",i);
        for(j=0; j<r; j++)
        {
            printf("%d ",max[i][j]);
        }
        printf("\n");

    }
    printf("\nNeed matrix is: ");
    int need[n][r];
    for(i=0; i<n; i++)
    {
        for(j=0; j<r; j++)
        {
            need[i][j]=max[i][j]-alloc[i][j];
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }
    int avaiable[r],work[r],finish[n],ss[n];
    printf("\nEnter available resources: ");
    for(i=0; i<r; i++)
    {
        scanf("%d",&avaiable[i]);
        work[i]=avaiable[i];
    }
    printf("\nAvailable resources: ");
    for(i=0; i<r; i++)
    {
        printf("%d ",avaiable[i]);

    }
    for(i=0; i<n; i++)
    {
        finish[i]=0;
        ss[i]=0;
    }
    //Bankers
    int dd=1,sf_index=0;
    do
    {
        int no_i=1;

        for(i=0; i<n; i++)
        {
            ///Provess remainng to finish
            if(finish[i]==0)
            {
                for(j=0; j<r; j++)
                {
                    ///check if satisfy condition to update work
                    if(need[i][j]>work[j])
                    {
                        break;
                    }
                }
                ///if yes update the work
                if(j==r)
                {
                    no_i=0; ///As i is found who can update work
                    ss[sf_index++]=i;
                    finish[i]=1;
                    for(j=0; j<r; j++)
                    {
                        work[j]+=alloc[i][j];
                    }
                    continue;
                }
            }

        }

        if(no_i==1)
        {
            ///Work not updated
            for(i=0; i<n; i++)
            {
                ///+Process remaining to finish
                if(finish[i]==0)
                {
                    /// + means deadlock
                    dd=1;
                    break;
                }
            }
        }
        else
        {
            int loop=0;
            ///work updated
            for(i=0; i<n; i++)
            {
                if(finish[i]==0)
                {
                    /// choose to reloop as process is left
                    loop=1;
                    dd=0;
                    break;
                }
            }
            if(loop==0)
            {
                dd=0;
                break;
            }

        }
    }
    while(!dd);
    if(dd==0){
               printf("\nSys in safe state: seq: ");
        for(i=0;i<n;i++){
            printf("%d ",ss[i]);
        }

    }
    else{
     printf("\ndd in system");
    }
    return 0;
}
