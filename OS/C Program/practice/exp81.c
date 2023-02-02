#include<stdio.h>

void display(int v,int m,int frame[])
{
    printf("\n________________");
    printf("\n%d | ",v);
    int i;
    for(i=0; i<m; i++)
    {
        printf(" %d",frame[i]);
    }
    printf("\n________________");

}
int check(int k,int m,int f[]){
 int i;
 for(i=0;i<m;i++){
    if(f[i]==k) {
            printf("\n %d in frame",k);
            return 1;
    }
 }
   printf("\n %d not in frame",k);
 return 0;
}
int main()
{
    int n,m,i,insert=0,faults=0;
    printf("\nEnter page references,frame size: ");
    scanf("%d %d",&n,&m);
    int ref[n],frame[m];
    printf("\nEnter page refernece string: ");
    for(i=0; i<n; i++)
    {
        scanf("%d ",&ref[i]);

    }
    for(i=0;i<m;i++){
        frame[i]=-1;
    }
     printf("\nFrame initially");
     display(-1,m,frame);
     for(i=0;i<n;i++){
        if(!check(ref[i],m,frame)){
            frame[insert]=ref[i];
            insert=(insert+1)%m;
            faults++;
        }
        display(ref[i],m,frame);

     }
     printf("\nFaults: %d",faults);

    return 0;
}
