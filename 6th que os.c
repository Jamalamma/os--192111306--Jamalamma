#include <stdlib.h>

struct process {
    int pid;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int remaining_time;
    int arrival_time;
};

void swap(struct process *a, struct process *b) {
    struct process temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n, i, j, time = 0, total_waiting_time = 0, total_turnaround_time = 0;
    float avg_waiting_time, avg_turnaround_time;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process *processes = (struct process *)malloc(n * sizeof(struct process));

    for (i = 0; i < n; i++) {
        printf("Enter the arrival time, burst time and priority of process %d: ", i + 1);
        scanf("%d%d%d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].pid = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
    }

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                swap(&processes[i], &processes[j]);
            }
        }
    }

    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (processes[i].arrival_time == processes[j].arrival_time && processes[i].priority < processes[j].priority) {
                swap(&processes[i], &processes[j]);
            }
        }
    }

    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");

    for (i = 0; i < n; i++) {
        while (processes[i].remaining_time > 0) {
            printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
            processes[i].remaining_time--;
            time++;

            for (j = 0; j < n; j++) {
                if (processes[j].arrival_time <= time && processes[j].remaining_time > 0 && processes[j].priority > processes[i].priority) {
                    processes[i].waiting_time++;
                    break;
                }
            }
        }

        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    avg_waiting_time = (float)total_waiting_time / n;
    avg_turnaround_time = (float)total_turnaround_time / n;

    printf("\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f", avg_turnaround_time);

    return 0;
}