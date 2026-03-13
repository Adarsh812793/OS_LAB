#include <stdio.h>

struct Process {
    int pid, at, bt, priority, ct, wt, tat, is_completed;
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
        p[i].is_completed = 0;
    }

    int completed = 0, time = 0, min_pri;
    int selected = -1;

    while(completed != n) {
        min_pri = 10000;
        selected = -1;

        for(int i=0; i<n; i++) {
            if((p[i].at <= time) && (p[i].is_completed == 0) && (p[i].priority < min_pri)) {
                min_pri = p[i].priority;
                selected = i;
            }
        }

        if(selected == -1) {
            time++;
            continue;
        }

        time += p[selected].bt;
        p[selected].ct = time;
        p[selected].tat = p[selected].ct - p[selected].at;
        p[selected].wt = p[selected].tat - p[selected].bt;
        p[selected].is_completed = 1;
        completed++;
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
    printf("Avg WT=%.2f\n",avg_WT/n);
    printf("1BM24CS014");
    return 0;
}
