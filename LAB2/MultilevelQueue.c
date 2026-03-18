
#include <stdio.h>

#define MAX 10

typedef struct {
	int pid, at, bt, rt, ct, tat, wt, queue;
} Process;

int main() {
	Process p[MAX];
	int n, i, time = 0, completed = 0;
	int tq = 2;

	printf("Enter number of processes: ");
	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		printf("\nP%d\n", i + 1);
		p[i].pid = i + 1;

		printf("Arrival Time: ");
		scanf("%d", &p[i].at);

		printf("Burst Time: ");
		scanf("%d", &p[i].bt);

		printf("Queue (1-System, 2-User): ");
		scanf("%d", &p[i].queue);

		p[i].rt = p[i].bt;
	}

	printf("\nGantt Chart:\n");

	while (completed < n) {

		int executed = 0;

		for (i = 0; i < n; i++) {
			if (p[i].queue == 1 && p[i].rt > 0 && p[i].at <= time) {

				executed = 1;

				if (p[i].rt > tq) {
					printf("P%d ", p[i].pid);
					time += tq;
					p[i].rt -= tq;
				} else {
					printf("P%d ", p[i].pid);
					time += p[i].rt;
					p[i].rt = 0;
					p[i].ct = time;
					completed++;
				}
			}
		}

		if (!executed) {
			for (i = 0; i < n; i++) {
				if (p[i].queue == 2 && p[i].rt > 0 && p[i].at <= time) {

					executed = 1;

					printf("P%d ", p[i].pid);
					p[i].rt--;
					time++;

					if (p[i].rt == 0) {
						p[i].ct = time;
						completed++;
					}

					break;
				}
			}
		}

		if (!executed) {
			time++;
		}
	}

	float total_tat = 0, total_wt = 0;

	printf("\n\nPID\tAT\tBT\tCT\tTAT\tWT\n");

	for (i = 0; i < n; i++) {
		p[i].tat = p[i].ct - p[i].at;
		p[i].wt = p[i].tat - p[i].bt;

		total_tat += p[i].tat;
		total_wt += p[i].wt;

		printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
		       p[i].pid, p[i].at, p[i].bt,
		       p[i].ct, p[i].tat, p[i].wt);
	}

	printf("\nAverage TAT = %.2f", total_tat / n);
	printf("\nAverage WT = %.2f\n", total_wt / n);

	return 0;
}