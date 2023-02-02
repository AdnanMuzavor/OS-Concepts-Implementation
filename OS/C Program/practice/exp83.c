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
int give_index(int start,int n,int key,int ref[]){
     int min_index=10000;
     int i;
     for(i=start;i<n;i++){
        if(ref[i]==key){
               return i;
        }
     }
     return 10000;

}
int main()
{
    int n,m,i,insert=0,faults=0,j;
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
                faults++;
           int lrf_index=-10000,insert_at=-1,flag=0;
           for(j=0;j<m;j++){
                //Empty slot case
            if(frame[j]==-1){
                frame[j]=ref[i];
                flag=1;
                break;
            }
              ///no empty slot
              int index=give_index(i+1,n,frame[j],ref);
           if(index>lrf_index){
            lrf_index=index;
            insert_at=j;
           }
           }
           ///Not inserted yet
           if(flag==0){
              if(insert_at==-1){
                frame[0]=ref[i];
              }
              else{
                frame[insert_at]=ref[i];
              }
           }

        }
        display(ref[i],m,frame);

     }
     printf("\nFaults: %d",faults);

    return 0;
}


