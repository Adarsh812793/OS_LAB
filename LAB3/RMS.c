#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Process {
    int pid;
    int burst;
    int period;
    int remaining;
};

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int n;
    printf("Enter the number of processes:");
    scanf("%d", &n);

    struct Process p[n];
    printf("Enter the CPU burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].burst);
        p[i].pid = i + 1;
        p[i].remaining = 0; // Initialize remaining time
    }

    printf("Enter the time periods:\n");
    int hyperPeriod = 1;
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].period);
        hyperPeriod = lcm(hyperPeriod, p[i].period);
    }

    printf("LCM=%d\n\n", hyperPeriod);

    // Print process table
    printf("Rate Monotone Scheduling:\n");
    printf("PID\tBurst\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\n", p[i].pid, p[i].burst, p[i].period);
    }

    // Calculate Utilization and Bound
    double U = 0.0;
    for (int i = 0; i < n; i++) {
        U += (double)p[i].burst / p[i].period;
    }
    double bound = n * (pow(2.0, 1.0 / n) - 1);
    printf("\n%.6f <= %.6f =>%s\n", U, bound, (U <= bound ? "true" : "false"));
    printf("Scheduling occurs for %d ms\n\n", hyperPeriod);

    // Simulation Loop
    int prev_chosen = -2; // Used to track context switches (-1 will mean idle)

    for (int t = 0; t < hyperPeriod; t++) {

        // 1. Check for new arrivals / period resets
        for (int i = 0; i < n; i++) {
            if (t % p[i].period == 0) {
                p[i].remaining = p[i].burst;
            }
        }

        // 2. Find the highest priority process (Shortest Period) that is ready to run
        int chosen = -1;
        int min_period = 999999; // Arbitrarily large number

        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0 && p[i].period < min_period) {
                min_period = p[i].period;
                chosen = i;
            }
        }

        // 3. Print only if there is a context switch (change in running process)
        if (chosen != prev_chosen) {
            if (chosen != -1) {
                printf("%dms onwards: Process %d running\n", t, p[chosen].pid);
            } else {
                printf("%dms onwards: CPU is idle\n", t);
            }
            prev_chosen = chosen;
        }

        // 4. Execute the chosen process for 1ms
        if (chosen != -1) {
            p[chosen].remaining--;
        }
        }

    printf("\n USN:1BM24CS014");
    return 0;
}
