#include<stdio.h>
#include<stdlib.h>

int main(){
    int i, j, p, r, alloc[20][20], need[20][20], max[20][20], avail[10], finish[10], ind = 0, safe[10], flag;
    
    printf("Enter no of processes: ");
    scanf("%d", &p);
    printf("Enter no of resources: ");
    scanf("%d", &r);
    
    printf("Enter allocation matrix:\n");
    for(i = 0; i < p; i++){
        finish[i] = -1;
        for(j = 0; j < r; j++){
            scanf("%d", &alloc[i][j]);
        }
    }
    
    printf("Enter max matrix:\n");
    for(i = 0; i < p; i++){
        for(j = 0; j < r; j++){
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("Need matrix:\n");
    for(i = 0; i < p; i++){
        for(j = 0; j < r; j++){
            need[i][j] = max[i][j] - alloc[i][j];
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
    
    printf("Enter available resources:\n");
    for(i = 0; i < r; i++){
        scanf("%d", &avail[i]);
    }
    
    for(i = 0; i < p; i++){
        for(j = 0; j < p; j++){
            if(finish[j] == -1) {
                flag = 0;
                for(int k = 0; k < r; k++){
                    if(need[j][k] > avail[k]){
                        flag = 1;
                        break;
                    }
                }
                
                if(flag == 0){
                    safe[ind++] = j;  // Corrected line
                    finish[j] = 0;
                    for(int z = 0; z < r; z++){
                        avail[z] += alloc[j][z];
                    }
                }
            }
        }
    }
    
    if(ind != p){
        printf("Deadlock detected!\n");
        exit(0);
    }
    
    printf("Safe sequence: ");
    for(i = 0; i < ind; i++){
        printf("P%d ", safe[i]);
        if(i < ind - 1) printf("-> ");
    }
    printf("\n");
    
    return 0;
}
