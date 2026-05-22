#include <stdio.h>
#include <stdlib.h>

void fifo(int pages[], int n, int num_frames) {
    int *frames = (int *)malloc(num_frames * sizeof(int));
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }
    int page_faults = 0;
    int next = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int present = 0;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                present = 1;
                break;
            }
        }

        if (!present) {
            int space_available = 0;
            int empty_slot = -1;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    space_available = 1;
                    empty_slot = j;
                    break;
                }
            }

            if (space_available) {
                frames[empty_slot] = page;
            } else {
                frames[next] = page;
                next = (next + 1) % num_frames;
            }
            page_faults++;
        }
    }
    printf("FIFO Page Hits: %d\n", n - page_faults);
    printf("FIFO Page Misses: %d\n", page_faults);
    free(frames);
}

void lru(int pages[], int n, int num_frames) {
    int *frames = (int *)malloc(num_frames * sizeof(int));
    int *last_used = (int *)malloc(num_frames * sizeof(int));
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
        last_used[i] = -1;
    }
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int present = 0;
        int present_index = -1;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                present = 1;
                present_index = j;
                break;
            }
        }

        if (present) {
            last_used[present_index] = i;
        } else {
            int space_available = 0;
            int empty_slot = -1;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    space_available = 1;
                    empty_slot = j;
                    break;
                }
            }

            if (space_available) {
                frames[empty_slot] = page;
                last_used[empty_slot] = i;
            } else {
                int lru_index = 0;
                int min_time = last_used[0];
                for (int j = 1; j < num_frames; j++) {
                    if (last_used[j] < min_time) {
                        min_time = last_used[j];
                        lru_index = j;
                    }
                }
                frames[lru_index] = page;
                last_used[lru_index] = i;
            }
            page_faults++;
        }
    }
    printf("LRU Page Hits: %d\n", n - page_faults);
    printf("LRU Page Misses: %d\n", page_faults);
    free(frames);
    free(last_used);
}

void optimal(int pages[], int n, int num_frames) {
    int *frames = (int *)malloc(num_frames * sizeof(int));
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }
    int page_faults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int present = 0;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == page) {
                present = 1;
                break;
            }
        }

        if (!present) {
            int space_available = 0;
            int empty_slot = -1;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    space_available = 1;
                    empty_slot = j;
                    break;
                }
            }

            if (space_available) {
                frames[empty_slot] = page;
            } else {
                int replace_index = -1;
                int farthest = i;
                for (int j = 0; j < num_frames; j++) {
                    int next_use = -1;
                    for (int k = i + 1; k < n; k++) {
                        if (pages[k] == frames[j]) {
                            next_use = k;
                            break;
                        }
                    }
                    if (next_use == -1) {
                        replace_index = j;
                        break;
                    }
                    if (next_use > farthest) {
                        farthest = next_use;
                        replace_index = j;
                    }
                }
                frames[replace_index] = page;
            }
            page_faults++;
        }
    }
    printf("Optimal Page Hits: %d\n", n - page_faults);
    printf("Optimal Page Misses: %d\n", page_faults);
    free(frames);
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 1;

    int *pages = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &pages[i]) != 1) return 1;
    }

    int num_frames;
    if (scanf("%d", &num_frames) != 1) return 1;

    fifo(pages, n, num_frames);
    lru(pages, n, num_frames);
    optimal(pages, n, num_frames);

    free(pages);
    return 0;
}