#include<stdio.h>
struct process{
    int id,at,wt,ct,tt,bt,finish;
}p[100],temp;
int main(){
    int i,j,n,time=0;
    printf("enter number of process");
    scanf("%d",&n);
    p[0].id=1;
    for(i=0;i<n;i++)
    {
        printf("enter arrival time burst time of process %d",p[i].id);
        scanf("%d%d",&p[i].at,&p[i].bt);
        p[i+1].id=i+2;
        p[i].finish=-1;
    }
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(p[j].at>p[j+1].at){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        while(p[i].finish==-1)
        {
            if(p[i].at<=time)
            {
                time+=p[i].bt;
                p[i].ct=time;
                p[i].finish=1;
                p[i].tt=p[i].ct-p[i].at;
                p[i].wt=p[i].tt-p[i].bt;
            }
            else
            {
            time++;
            }
        }
    }
    printf("Process arrival time burst time completion time turnaround time waiting time\n");
    for(i=0;i<n;i++){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].tt,p[i].wt);
    }
}