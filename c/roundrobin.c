#include<stdio.h>
struct process{
    int ct,at,tt,id,wt,status,bt;
}p[100];
int main(){
    int current_time=0,q[100],rear=-1,front=-1,index,finished=0,quanta,n,i,j,left[10];

    printf("enter no of process");
    scanf("%d",&n);
    printf("enter time quanta");
    scanf("%d",&quanta);
    printf("enter arrival time and burst time of each process");
    for(i=0;i<n;i++)
    {
        printf("Enter arrival time and burst time for P%d: ", i + 1);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].id = i + 1;
        p[i].status=0;
        left[i]=p[i].bt;
    }
    while(finished<n){
        for(i=0;i<n;i++){
            if(p[i].status==0 && p[i].at<=current_time)
            {
                if(front==-1 && rear==-1)
                {
                    front++;
                }
                rear++;
                q[rear]=i;
                p[i].status=1;
            }
        }
        if(front==-1){
            current_time++;
        }
        else{
            index=q[front];
            if(front==rear){
                front=-1;
                rear=-1;
            }
            else{
                front++;
            }
            if(left[index]<=quanta){
                current_time+=left[index];
                p[index].ct=current_time;
                p[index].tt=current_time-p[index].at;
                p[index].wt=p[index].tt-p[index].bt;
                p[index].status=2;
                finished++;
            }
            else
            {
                current_time+=quanta;
                left[index]-=quanta;
                 for(j=0;j<n;j++)
                 {
                     if(p[j].status==0 && p[j].at<=current_time)
                    {
                     if(front==-1 && rear==-1)
                     {
                         front++;
                     }
                     rear++;
                      q[rear]=j;
                      p[j].status=1;
                    }
                 }
                  if(front==-1 && rear==-1)
                {
                    front++;
                }
                rear++;
                q[rear]=index;
            }
        }
    }
     float avwt = 0, avtt = 0;
    printf("\nPROCESS ID\tCOMPLETION TIME (ms)\tWAITING TIME (ms)\tTURNAROUND TIME (ms)\n\n");
    for (i = 0; i < n; i++) {
        printf("   %d\t\t\t%d\t\t\t%d\t\t\t%d\n", p[i].id, p[i].ct, p[i].wt, p[i].tt);
        avwt += (float)p[i].wt;
        avtt += (float)p[i].tt;
    }
    printf("\n\nAVERAGE WAITING TIME : %.2f", (avwt / (float)n));
    printf("\nAVERAGE TURNAROUND TIME : %.2f\n", (avtt / (float)n));
}