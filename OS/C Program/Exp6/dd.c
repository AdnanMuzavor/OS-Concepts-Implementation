///DEadlock detection algorithm
///Adnan Ismail Shah Muzavor
#include<stdio.h>
#include<stdlib.h>

typedef struct process
{
    int act; ///Resources allocated
    int req; ///REsources requested
} Pr;

void input(int np,int nr,Pr p1[np][nr],int *available)
{
    int i=0,j=0; ///No of processes ,No of resources
    printf("Enter the number of resource avaialble: ");
    for(i=0; i<nr; i++)
    {
        scanf("%d",&available[i]);
        if(i==nr-1) break;
    }
    printf("\nEnter the number of resources allocated to process\n");

    for(i=0; i<np; i++)
    {
        printf("p%d: ",i);
        for(j=0; j<nr; j++)
        {
            scanf("%d",&p1[i][j].act); ///Enter number of resources type(j) allocated to i}
        }
}
        printf("\nEnter the number of maximum resources requested by process\n");
        for(i=0; i<np; i++)
        {
            printf("p%d: ",i);
            for(j=0; j<nr; j++)
            {
                scanf("%d",&p1[i][j].req); ///Enter number of resources type(j) allocated to i}
            }
        }
        }
        void dd(int np,int nr,Pr p1[np][nr],int *a)
        {
            int *work=(int*)malloc(sizeof(int)*nr);
            int* finish=(int*)malloc(sizeof(int)*np);
            int i=0,j=0;
            ///Make work matrix equals avaiable matrix
            for(i=0; i<nr; i++)
            {
                work[i]=a[i];
            }
            ///Make finish of all processes false(0)
            for(i=0; i<np; i++)
            {
                finish[i]=0;
            }

            ///initially assume there is deadlock so set dd=1 (true)
            int dd=1;
            do
            {
                ///printf("\nIN LOOP AGAIN\n");

                int no_i=1; ///No i is found yet
                ///Find if there exist nay process whose finish is false(0)
                for(i=0; i<np; i++)
                {
                    if(finish[i]==0)
                    {
                        ///printf("\nCHECKING FOR %d\n",i+1);

                        ///Check if request[i]<=work[i]
                        for(j=0; j<nr; j++)
                        {
                            if(p1[i][j].req>work[j])
                            {
                                ///printf("\np%d false\n",i+1);
                                break;
                            }
                        }
                        ///If j==nr means req[i]<=work[i] wrt all reasources
                        ///Hence we set finish of this process to true
                        if(j==nr)
                        {
                            ///work=work+allocated

                            ///printf("\np%d is true\n",i+1);
                            for(j=0; j<nr; j++)
                            {
                                work[j]+=(p1[i][j].act);
                            }
                            finish[i]=1;
                            no_i=0; ///We found an i with both conditions true
                            continue;
                        }

                    }
                }

                ///If we had not found any i with both consition true
                if(no_i==1)
                {
                    ///and finish[i]==false(0)  for any process means deadlock exists
                    for(i=0; i<np; i++)
                    {
                        if(finish[i]==0)
                        {
                            dd=1; ///deadlock exists

                            ///printf("\nDD exists\n");

                            break;
                        }
                    }
                }
                ///Else if any processes were selected,means work was updated
                else
                {

                    int cont=0; ///Not relooping
                    for(i=0; i<np; i++)
                    {
                        ///And we have some processes unfinihsd
                        ///there are chances that they can finish now
                        if(finish[i]==0)
                        {
                            dd=0; ///No deadlock, as we are checking again

                            ///printf("\nSINCE PROCESSES WERE SELECTED => WORK UPDATED => SO LOOPING AGAIN\n");

                            cont=1; ///Choosing to reloop
                            break;
                        }
                    }
                    ///If cont==0 means all processes have executed withut any deadlock
                    if(cont==0)
                    {
                        dd=0; ///No dd
                        break;
                    }
                }
            }
            while(!dd); ///Loop until no deadlock is found

            if(dd)
            {
                printf("----------------------------------------------------");
                printf("\nThere is deadlock in the system.");
                printf("\n----------------------------------------------------");
            }
            else
            {
                printf("----------------------------------------------------");
                printf("\nThere is no deadlock in the system.");
                printf("\n----------------------------------------------------");
            }
        }
        int main()
        {
            int np,nr;///No of processes ,No of resources
            printf("Enter the number of processs: ");
            scanf("%d",&np);
            printf("Enter the number of resources: ");
            scanf("%d",&nr);
            Pr p1[np][nr];
            int*available=(int*)malloc(sizeof(int)*nr);
            input(np,nr,p1,available);
            dd(np,nr,p1,available);
            return 1;
        }
