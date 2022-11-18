// Dylan Sarell
// Banker's Algorithm
// 11/16/22

#include <stdio.h>
int main(int argc, char** argv) {
    
    int n = 5; // Number of Processes (P0, P1, P2, P3, P4)
    int m = 3; // Number of Resources

    FILE* ptr;
    int num = 0;
    if (argc != 2) {
        printf("Please provide Input File Name: \n");
        return (0);
    }

    ptr = fopen(argv[1], "r"); // Reads and gets the numbers from the input file. 
    // Matrix of each type of resource allocated to each process
    printf("Allocation\n");
    int allocation[n][m];
    for (int pIndex = 0; pIndex < n; pIndex++) {
        for (int rIndex = 0; rIndex < m; rIndex++) { 
            fscanf(ptr, "%d", &num);
            allocation[pIndex][rIndex] = num;
            printf("%d ", allocation[pIndex][rIndex]);
        }
        printf("\n");
    }
    // Matrix of the Max amount of each resource type that each process can request
    printf("Max\n");
    int max[n][m];
    for (int pIndex = 0; pIndex < n; pIndex++) {
        for (int rIndex = 0; rIndex < m; rIndex++) {
            fscanf(ptr, "%d", &num);
            max[pIndex][rIndex] = num;
            printf("%d ", max[pIndex][rIndex]);
        }
        printf("\n");
    }
    // Vector (array) of istances of each resource type that is available
    printf("Available\n");
    int available[m];
    for (int rIndex = 0; rIndex < m; rIndex++) {
        fscanf (ptr, "%d", &num);
        available[rIndex] = num;
        printf("%d ", available[rIndex]);
    }
    printf("\n");
    fclose(ptr);

    // Finish is initialized as a vector of all 0's (false) of length n (Number of Proceses). 
    int finish[n], answer[n], index = 0;
    for (int x = 0; x < n; x++) {
        finish[x] = 0;
    }

    // Need matrix = max - alloaction. Resources that might need to be alloacted to each process
    int need[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
    for (int y = 0; y < n; y++) {
        for (int z = 0; z < n; z++) {
            if (finish[z] == 0) { // checks if process is not finished. (doesn't have all required Resources).
                int flag = 0;
                for (int w = 0; w < m; w++) {
                    if (need[z][w] > available[w]) { // Process needs more Resources then that are Available
                        flag = 1; // process can't be finished (insufficent resources)
                        break;
                    }
                }
                if (flag == 0) { // Process can be finished and gives back its resources.
                    answer[index++] = z;
                    for (int v = 0; v < m; v++) {
                        available[v] = available[v] + allocation[z][v];
                    }
                    finish[z] = 1;
                }
            }
        }
    }
    int flag = 1;

    for (int d = 0; d < n; d++) {
        if (finish[d] == 0) { // Checks if all proceses are finished (finished = 1). If not, then system is in a deadlock. 
            flag = 0;
            printf("The System is not safe. [There Exists a Deadlock]: ");
            break;
        }
    }
    if (flag == 1) {
        printf("The System is Safe. This is the Safe Sequence:\n");
        for (int e = 0; e < n - 1; e++) {
            printf(" P%d -> ", answer[e]);
        }
        printf(" P%d", answer[n-1]);
    }
    printf("\n");
    return (0);
}
