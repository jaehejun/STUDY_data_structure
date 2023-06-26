#include <stdio.h>
#include <stdlib.h>

#define MAX_ORDERS 10000000

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

void reorder(OrderQueue* queue, int orderNumber, int newPosition) {
    int i, j;
    Order reorderedOrder;
    for (i = queue->front, j = 0; j < queue->size; i = (i + 1) % queue->capacity, j++) {
        if (queue->orders[i].orderNumber == orderNumber) {
            reorderedOrder = queue->orders[i];
            break;
        }
    }
    // Move the order to the new position
    int destIndex = (queue->front + newPosition - 1) % queue->capacity;
    queue->orders[destIndex] = reorderedOrder;
    printf("Order %d has been reordered to position %d.\n", orderNumber, newPosition);
}

void printQueue(OrderQueue* queue) {
    int i, j;
    printf("Queue: ");
    for (i = queue->front, j = 0; j < queue->size; i = (i + 1) % queue->capacity, j++) {
        printf("%d ", queue->orders[i].orderNumber);
    }
    printf("\n");
}

void freeQueue(OrderQueue* queue) {
    free(queue->orders);
    free(queue);
}

int main() {
    OrderQueue* queue = createQueue(MAX_ORDERS);

    // Example usage
    Order order1;
    order1.orderNumber = 1;
    enqueue(queue, order1);
    printQueue(queue);

    Order order2;
    order2.orderNumber = 2;
    enqueue(queue, order2);
    printQueue(queue);

    Order order3;
    order3.orderNumber = 3;
    enqueue(queue, order3);
    printQueue(queue);

    Order dequeuedOrder = dequeue(queue);
    printf("Dequeued Order Number: %d\n", dequeuedOrder.orderNumber);
    printQueue(queue);

    cancelOrder(queue, 2);
    printQueue(queue);

    reorder(queue, 3, 1);
    printQueue(queue);

    freeQueue(queue);

    return 0;
}