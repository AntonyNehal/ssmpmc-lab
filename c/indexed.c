#include<stdio.h>
struct files{
    char name[20];
    int size,indexblock,blocks[20];
}p[100];
int main()
{
    int block[100]={0},i,j,n,index,b;
    printf("enter no of files");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("enter name of the file");
        scanf("%s",p[i].name);
        printf("enter size of the file %s",p[i].name);
        scanf("%d",&p[i].size);
        printf("enter index of the file");
        scanf("%d",&index);
        if(block[index]==0)
        {
            block[index]=1;
            p[i].indexblock=index;
        }
        else
         {
          printf("Index block %d is already allocated. Please enter a different index block.\n", index);
           i--;
           continue;
        }
        printf("enter the blocks %s",p[i].name);
        for(j=0;j<p[i].size;j++)
        {
            scanf("%d",&b);
            if(block[b]==0)
            {
                block[b]=1;
                p[i].blocks[j]=b;
            }
            else
             {
               printf("Block %d is already allocated. Please enter a different block.\n", b);
                j--;
            }
        }
    }
     printf("\nFile Allocation Table:\n");
    printf("FileName\tIndexBlock\tBlocks\n");
    printf("---------------------------------------\n");
    for (i = 0; i < n; i++) 
    {
        printf("%s\t\t%d\t\t", p[i].name, p[i].indexblock);
        for (j = 0; j < p[i].size; j++) 
        {
            printf("%d ", p[i].blocks[j]);
        }
        printf("\n");
    }
}