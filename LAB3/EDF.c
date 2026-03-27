#include <stdio.h>

struct Task {
    int pid;
    int burst;
    int deadline;
    int period;
    int rem;
    int abs_dl;
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
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Task tks[n];
    int hyperperiod = 1;

    for (int i = 0; i < n; i++) {
        printf("Enter PID, Burst, Deadline, and Period for process %d: ", i + 1);
        scanf("%d %d %d %d", &tks[i].pid, &tks[i].burst, &tks[i].deadline, &tks[i].period);
        tks[i].rem = 0;
        tks[i].abs_dl = 0;
        hyperperiod = lcm(hyperperiod, tks[i].period);
    }

    printf("\nPID\tBurst\tDeadline\tPeriod\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\n", tks[i].pid, tks[i].burst, tks[i].deadline, tks[i].period);
    }
    printf("Scheduling occurs for %d ms\n\n", hyperperiod);

    for (int time = 0; time < hyperperiod; time++) {
        for (int i = 0; i < n; i++) {
            if (time % tks[i].period == 0) {
                tks[i].rem = tks[i].burst;
                tks[i].abs_dl = time + tks[i].deadline;
            }
        }

        int min_dl = 999999;
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (tks[i].rem > 0 && tks[i].abs_dl < min_dl) {
                min_dl = tks[i].abs_dl;
                selected = i;
            }
        }

        if (selected != -1) {
            printf("%dms : Task %d is running.\n", time, tks[selected].pid);
            tks[selected].rem--;
        } else {
            printf("%dms: CPU is idle.\n", time);
        }
    }

    printf("\n USN 1BM24CS014");

    return 0;
}
