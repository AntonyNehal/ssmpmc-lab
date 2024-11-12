#include<stdio.h>
#include <stdlib.h>
#include <string.h>
struct block{
    int blockno;
    struct block *next;
};
struct files{
    int size;
    char name[20];
    struct block *startblock;
}p[100];
int main(){
    int i,j,block,blocks[100]={0},n;
    printf("enter no of files");
    scanf("%d",&n);
    for(i=0;i<n;i++){
        printf("enter name of the file");
        scanf("%s",p[i].name);
        printf("enter size of the file");
        scanf("%d",&p[i].size);
        struct block *prevblock=NULL;
        for(j=0;j<p[i].size;j++){
            printf("enter the block");
            scanf("%d",&block);
            if(blocks[block]==0){
                blocks[block]=1;
                struct block *new=(struct block*)malloc(sizeof(struct block));
                new->blockno=block;
                new->next=NULL;
                if(j==0){
                    p[i].startblock=new;
                }
                else{
                    prevblock->next=new;
                }
                prevblock=new;
            }
            else {
               printf("Block %d is already allocated. Please enter a different block.\n", block);
              j--;
           }
        }
    }
    
    printf("\nFile Allocation Table:\n");
    printf("FileName\tBlocks\n");
  printf("-------------------------------\n");
   for (i =0; i < n; i++) {
        printf("%s\t\t", p[i].name);
        struct block *currentBlock = p[i].startblock;
       while (currentBlock != NULL) {
           printf("%d -> ", currentBlock->blockno);
            currentBlock = currentBlock->next;
        }
        printf("NULL\n");
    }

}