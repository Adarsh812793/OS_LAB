#include <stdio.h>

struct Process {
    int id, at, bt, ct, tat, wt, rt, rem;
};

int main() {
    int n;
    printf("Enter no. of process: ");
    scanf("%d", &n);
    
    struct Process p[n];
    for(int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Arrival Time of P%d: ", p[i].id);
        scanf("%d", &p[i].at);
        printf("Burst Time of P%d: ", p[i].id);
        scanf("%d", &p[i].bt);
        p[i].rem = p[i].bt; p[i].rt = -1;
    }
    
    int completed = 0, time = 0, sumTAT = 0, sumWT = 0,sumRT=0;
    
    while (completed != n) {
        int idx = -1, minRem = 1e9;
        
        for(int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rem > 0) {
                if (p[i].rem < minRem) {
                    minRem = p[i].rem;
                    idx = i;
                }
            }
        }
        
        if (idx != -1) {
            if (p[idx].rt == -1) {
                p[idx].rt = time - p[idx].at;
                sumRT += p[idx].rt;
            }
            p[idx].rem--; time++;
            if (p[idx].rem == 0) {
                p[idx].ct = time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                
                sumTAT += p[idx].tat;
                sumWT += p[idx].wt;
                sumRT += p[idx].rt; completed++;
            }
        }
        else { time++; }
    }
    
        printf("Process\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",i+1,p[i].at,p[i].bt,p[i].ct,p[i].wt);
    }

    printf("Avg TAT: %.2f\n", (float)sumTAT/n);
    printf("Avg WT: %.2f\n", (float)sumWT/n);
    printf("Avg RT: %.2f\n", (float)sumRT/n);
    return 0;
}