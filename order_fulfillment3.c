#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ORDERS 10000000
#define CANCEL_ORDERS 3000

typedef struct {
    // Order structure definition
    // Modify this structure according to your needs
    int orderNumber;
    // Add other order attributes as necessary
} Order;

typedef struct {
    Order *orders;
    int front;
    int rear;
    int size;
    int capacity;
} OrderQueue;

OrderQueue* createQueue(int capacity) {
    OrderQueue* queue = (OrderQueue*)malloc(sizeof(OrderQueue));
    queue->orders = (Order*)malloc(capacity * sizeof(Order));
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

int isFull(OrderQueue* queue) {
    return queue->size == queue->capacity;
}

int isEmpty(OrderQueue* queue) {
    return queue->size == 0;
}

void enqueue(OrderQueue* queue, Order order) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue order.\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->orders[queue->rear] = order;
    queue->size++;
}

Order dequeue(OrderQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue order.\n");
        Order emptyOrder;
        emptyOrder.orderNumber = -1; // Return an empty order as a placeholder
        return emptyOrder;
    }
    Order dequeuedOrder = queue->orders[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return dequeuedOrder;
}

void cancelOrder(OrderQueue* queue, int orderNumber) {
    int i, j;
    for (i = queue->front, j = 0; j < queue->size; i = (i + 1) % queue->capacity, j++) {
        if (queue->orders[i].orderNumber == orderNumber) {
            // Mark the order as canceled (assuming -1 indicates canceled)
            queue->orders[i].orderNumber = -1;
            printf("Order %d has been canceled.\n", orderNumber);
            return;
        }
    }
    printf("Order %d not found. Cannot cancel.\n", orderNumber);
}

void freeQueue(OrderQueue* queue) {
    free(queue->orders);
    free(queue);
}

int main() {
    OrderQueue* queue = createQueue(MAX_ORDERS);

    // Adding 10 million orders to the queue
    int i;
    for (i = 1; i <= MAX_ORDERS; i++) {
        Order order;
        order.orderNumber = i;
        enqueue(queue, order);
    }
    printf("10 million orders added to the queue.\n");

    // Canceling 3000 randomly selected orders
    srand(time(NULL));  // Initialize random number generator
    for (i = 0; i < CANCEL_ORDERS; i++) {
        int randomOrderNumber = rand() % MAX_ORDERS + 1;  // Generate a random order number
        cancelOrder(queue, randomOrderNumber);
    }
    printf("3000 orders canceled.\n");

    freeQueue(queue);

    return 0;
}