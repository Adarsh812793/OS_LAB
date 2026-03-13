#include <stdio.h>

struct Process {
    int pid, at, bt, rt, priority, ct, wt, tat;
};

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i=0; i<n; i++) {
        p[i].pid = i+1;
        printf("Enter AT, BT and Priority for P%d: ", i+1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].rt = p[i].bt;
    }

    int completed = 0, time = 0, min_pri;
    int shortest = -1;
    int check = 0;

    while(completed != n) {
        min_pri = 10000;
        shortest = -1;
        check = 0;

        for(int i=0; i<n; i++) {
            if((p[i].at <= time) && (p[i].rt > 0) && (p[i].priority < min_pri)) {
                min_pri = p[i].priority;
                shortest = i;
                check = 1;
            }
        }

        if(check == 0) {
            time++;
            continue;
        }

        p[shortest].rt--;
        time++;

        if(p[shortest].rt == 0) {
            completed++;
            p[shortest].ct = time;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
        }
    }

    printf("\nPID\tAT\tBT\tPri\tCT\tWT\tTAT\n");
    for(int i=0; i<n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].ct, p[i].wt, p[i].tat);
    }

     //Calculating avg TAT ,WT
    float avg_TAT=0,avg_WT=0;
    for(int i=0;i<n;i++){
        avg_TAT+=p[i].tat;
        avg_WT+=p[i].wt;
    }

    printf("Avg TAT=%.2f\n",avg_TAT/n);
    printf("Avg WT=%.2f",avg_WT/n);

    return 0;
}
