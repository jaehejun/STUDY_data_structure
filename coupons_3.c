#include <stdio.h>
#include <stdlib.h>

#define MAX_COUPONS 10000

typedef struct
{
    int arr[MAX_COUPONS];
    int front;
    int rear;
} Queue;

void initializeQueue(Queue* queue)
{
    queue->front = -1;
    queue->rear = -1;
}

int isQueueEmpty(Queue* queue)
{
    return (queue->front == -1 && queue->rear == -1);
}

int isQueueFull(Queue* queue) {
    return ((queue->rear + 1) % MAX_COUPONS == queue->front);
}

void enqueue(Queue* queue, int item)
{
    if (isQueueFull(queue))
	{
        printf("Queue is full. Cannot enqueue any more items.\n");
        return;
    }

    if (isQueueEmpty(queue))
	{
        queue->front = 0;
        queue->rear = 0;
    }
	else
	{
        queue->rear = (queue->rear + 1) % MAX_COUPONS;
    }

    queue->arr[queue->rear] = item;
}

int dequeue(Queue* queue)
{
    if (isQueueEmpty(queue))
	{
        printf("Queue is empty. Cannot dequeue any more items.\n");
        return -1;
    }

    int item = queue->arr[queue->front];

    if (queue->front == queue->rear)
	{
        queue->front = -1;
        queue->rear = -1;
    }
	else
	{
        queue->front = (queue->front + 1) % MAX_COUPONS;
    }

    return item;
}

void distributeCoupons(int coupons[], int num_coupons)
{
    Queue queue;
    initializeQueue(&queue);

    int i = 0;
    while (i < num_coupons)
	{
        enqueue(&queue, coupons[i]);
        i++;
    }

    while (!isQueueEmpty(&queue))
	{
        int coupon = dequeue(&queue);
        printf("%d번째 쿠폰이 발행되었습니다.\n", coupon);
    }
}

int main()
{
    int coupons[MAX_COUPONS];

    int	i = 0;
	while (i < MAX_COUPONS)
	{
        coupons[i] = i + 1;
		i++;
    }

    distributeCoupons(coupons, MAX_COUPONS);

    return 0;
}