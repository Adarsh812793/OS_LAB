#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int main() {
    int n, m;

    // n = number of processes
    // m = number of resource types
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];

    // Input Allocation matrix
    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Max matrix
    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available array
    printf("\nEnter Available Resources:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }

    // Calculate Need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    bool finish[MAX_PROCESSES] = {false};
    int safeSequence[MAX_PROCESSES];

    int work[MAX_RESOURCES];

    // Work = Available
    for (int j = 0; j < m; j++) {
        work[j] = available[j];
    }

    int count = 0;

    while (count < n) {
        bool found = false;

        // Try to find a process that can execute
        for (int i = 0; i < n; i++) {

            // Skip already finished processes
            if (finish[i] == false) {

                bool canExecute = true;

                // Check if Need <= Work
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                // If process can execute
                if (canExecute) {

                    // Release allocated resources
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[count] = i;
                    count++;

                    finish[i] = true;
                    found = true;
                }
            }
        }

        // No process could execute
        if (!found) {
            break;
        }
    }

    // Check if system is safe
    if (count == n) {
        printf("\nSystem is in SAFE state.\n");
        printf("Safe Sequence: ");

        for (int i = 0; i < n; i++) {
            printf("P%d", safeSequence[i]);

            if (i != n - 1) {
                printf(" -> ");
            }
        }

        printf("\n");
    }
    else {
        printf("\nSystem is NOT in safe state.\n");
    }

    return 0;
}