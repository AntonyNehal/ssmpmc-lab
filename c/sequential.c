#include<stdio.h>
struct files{
        char name[20];
    int start,length;
}p[100];
int main()
{
    int i,j,totalblock,start,length,n,block[100];
    printf("enter total no of blocks");
    scanf("%d",&totalblock);
    printf("enter no of files");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        printf("enter name of the file f%d",i+1);
        scanf("%s",p[i].name);
        printf("enter starting add and length %d",i+1);
        scanf("%d%d",&start,&length);
        int available=1;
        for(j=start;j<start+length;j++)
        {
            if(block[j]==1 || j>totalblock)
            {
                available=0;
                break;
            }
        }
        if(available){
            p[i].start=start;
            p[i].length=length;
            for(j=start;j<start+length;j++){
                block[j]=1;
            }

        }
        else {
            printf("The blocks from %d to %d are not available. Please try again.\n", start, start + length - 1);
          i--;
        }
    }
     printf("\nFile Allocation Table:\n");
    printf("FileName\tStartBlock\tSize\tBlocks \n");
    printf("-------------------------------------= ----------------\n");
    for (i =0; i < n; i++) {
        printf("%s\t\t%d\t\t%d\t", p[i].name, p[i].start, p[i].length);
        for (j =p[i].start; j < p[i].start + p[i].length; j++) {
            printf("%d ", j);
        }
      printf("\n");
    }

}