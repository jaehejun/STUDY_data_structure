#include <stdio.h>
#include <stdlib.h>

#define MAX_ORDER_SIZE 100

struct Queue {
    int front, rear, size;
    unsigned capacity;
    char** orders;
};

struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->orders = (char**)malloc(capacity * sizeof(char*));
    return queue;
}

int isFull(struct Queue* queue) {
    return (queue->size == queue->capacity);
}

int isEmpty(struct Queue* queue) {
    return (queue->size == 0);
}

void enqueue(struct Queue* queue, char* order) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue order: %s\n", order);
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->orders[queue->rear] = order;
    queue->size++;
    printf("Order %s added to the queue.\n", order);
}

char* dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return NULL;
    }
    char* order = queue->orders[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return order;
}

void processOrders(struct Queue* queue) {
    while (!isEmpty(queue)) {
        char* order = dequeue(queue);
        printf("Processing order: %s\n", order);
        // Add your code here to process the order (e.g., prepare the food, calculate the total, etc.)
        printf("Order %s processed.\n", order);
        free(order);
    }
}

void destroyQueue(struct Queue* queue) {
    free(queue->orders);
    free(queue);
}

int main() {
    struct Queue* orderQueue = createQueue(MAX_ORDER_SIZE);

    enqueue(orderQueue, "Cheeseburger");
    enqueue(orderQueue, "French Fries");
    enqueue(orderQueue, "Soda");

    processOrders(orderQueue);

    destroyQueue(orderQueue);

    return 0;
}
