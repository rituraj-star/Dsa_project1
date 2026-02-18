#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRIORITY_QUEUE_SIZE 100
#define CIRCULAR_QUEUE_SIZE 10

typedef struct {
    char baggage_id[50];
    int priority;
} PriorityNode;

PriorityNode priorityQueue[MAX_PRIORITY_QUEUE_SIZE];
int pqSize = 0;


char circularQueue[CIRCULAR_QUEUE_SIZE][50];
int front = 0, rear = 0, count = 0;

void enqueue_priority(char baggage_id[], int priority);
char* dequeue_priority();
char* peek_priority();
void enqueue_circular(char baggage_id[]);
char* dequeue_circular();
char* peek_circular();
void baggage_system();
void swap(PriorityNode *a, PriorityNode *b);
void heapify_up(int index);
void heapify_down(int index);

void enqueue_priority(char baggage_id[], int priority) {
    if (pqSize == MAX_PRIORITY_QUEUE_SIZE) {
        printf("Priority queue is full!\n");
        return;
    }
    strcpy(priorityQueue[pqSize].baggage_id, baggage_id);
    priorityQueue[pqSize].priority = priority;
    heapify_up(pqSize);
    pqSize++;
    printf("Baggage %s added to priority queue with priority %d.\n", baggage_id, priority);
}

char* dequeue_priority() {
    if (pqSize == 0) {
        printf("Priority queue is empty!\n");
        return NULL;
    }
    static char baggage_id[50];
    strcpy(baggage_id, priorityQueue[0].baggage_id);
    priorityQueue[0] = priorityQueue[--pqSize];
    heapify_down(0);
    return baggage_id;
}

char* peek_priority() {
    if (pqSize == 0) return NULL;
    return priorityQueue[0].baggage_id;
}

void heapify_up(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (priorityQueue[parent].priority >= priorityQueue[index].priority) break;
        swap(&priorityQueue[parent], &priorityQueue[index]);
        index = parent;
    }
}

void heapify_down(int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < pqSize && priorityQueue[left].priority > priorityQueue[largest].priority)
    largest = left;
    if (right < pqSize && priorityQueue[right].priority > priorityQueue[largest].priority)
    largest = right;
    
    if (largest != index) {
        swap(&priorityQueue[index], &priorityQueue[largest]);
        heapify_down(largest);
    }
}

void swap(PriorityNode *a, PriorityNode *b) {
    PriorityNode temp = *a;
    *a = *b;
    *b = temp;
}

void enqueue_circular(char baggage_id[]) {
    if (count == CIRCULAR_QUEUE_SIZE) {
        printf("Circular queue is full!\n");
        return;
    }
    strcpy(circularQueue[rear], baggage_id);
    rear = (rear + 1) % CIRCULAR_QUEUE_SIZE;
    count++;
    printf("Baggage %s added to circular queue.\n", baggage_id);
}
char* dequeue_circular() {
    if (count == 0) {
        printf("Circular queue is empty!\n");
        return NULL;
    }
    static char baggage_id[50];
    strcpy(baggage_id, circularQueue[front]);
    front = (front + 1) % CIRCULAR_QUEUE_SIZE;
    count--;
    return baggage_id;
}
char* peek_circular() {
    if (count == 0) return NULL;
    return circularQueue[front];
}

void baggage_system() {
    while (1) {
        printf("\nAirport Baggage System\n");
        printf("1. Add baggage to priority queue\n");
        printf("2. Add baggage to circular queue\n");
        printf("3. Process baggage from priority queue\n");
        printf("4. Process baggage from circular queue\n");
        printf("5. View next baggage to be processed\n");
        printf("6. Exit\n");
        
        int choice;
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {     
            printf("Invalid input! Please enter a number between 1-6.\n");
            while (getchar() != '\n');
            continue;
        }
        char baggage_id[50];
        int priority;
        char* baggage;
        switch (choice) {
            case 1:
            printf("Enter baggage ID: ");
            scanf("%s", baggage_id);
            printf("Enter priority (1-10, 10 is highest priority): ");
            if (scanf("%d", &priority) != 1 || priority < 1 || priority > 10) {
                printf("Invalid priority! Enter a number between 1 and 10.\n");
                while (getchar() != '\n');
                continue;
            }
            enqueue_priority(baggage_id, priority);
            break;
            case 2:
            printf("Enter baggage ID: ");
            scanf("%s", baggage_id);
            enqueue_circular(baggage_id);
            break;
            case 3:
            baggage = dequeue_priority();
            if (baggage) printf("Baggage %s processed from priority queue.\n", baggage);
            break;
            case 4:
            baggage = dequeue_circular();
            if (baggage) printf("Baggage %s processed from circular queue.\n", baggage);
            break;
            case 5:
            printf("Next baggage in priority queue: %s\n", peek_priority() ? peek_priority() : "None");
            printf("Next baggage in circular queue: %s\n", peek_circular() ? peek_circular() : "None");
            break;
            case 6:
            printf("Exiting the baggage system.\n");
            return;
            default:
            printf("Invalid choice. Please enter a number between 1-6.\n");
        }
    }
}
int main() {
    baggage_system();
    return 0;
}
