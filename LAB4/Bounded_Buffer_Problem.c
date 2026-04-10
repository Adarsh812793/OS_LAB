#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// semaphore variables
int mutex = 1;
int full = 0;
int empty = BUFFER_SIZE;

// wait and signal functions
void wait(int *s) {
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void producer(int next_prod) {
    //Overflow
    if (empty != 0 && mutex == 1) {
        wait(&empty);
        wait(&mutex);

        buffer[in] = next_prod;
        printf("Producer produced: %d at position %d\n", next_prod, in);
        in = (in + 1) % BUFFER_SIZE;

        signal(&mutex);
        signal(&full);
    } else {
        printf("Buffer full, producer waiting...\n");
    }
}

void consumer() {
    int next_cons;
    if (full != 0 && mutex == 1) {
        wait(&full);
        wait(&mutex);

        next_cons = buffer[out];
        printf("Consumer consumed: %d from position %d\n", next_cons, out);
        out = (out + 1) % BUFFER_SIZE;

        signal(&mutex);
        signal(&empty);
    } else {
        printf("Buffer empty, consumer waiting...\n");
    }
}

int main() {
    int choice, item;

    while (1) {
        printf("\n1. Produce\n2. Consume\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter item to produce: ");
                scanf("%d", &item);
                producer(item);
                break;
            case 2:
                consumer();
                break;
            case 3:
                printf("USN:1BM24CS014");2
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
