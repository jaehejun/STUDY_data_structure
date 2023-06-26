#include <stdio.h>
#include <stdlib.h>

#define MAX_COUPONS 10000

int	main(void)
{
	int	i = 0;
	static int	coupons[MAX_COUPONS];
	while (i++ < MAX_COUPONS)
	{
		if (coupons[i] != 0)
			printf("%d\n", coupons[i]);
	}
}

void	enqueue()
int arr[MAX_COUPONS];
int front = 0;
int rear = 0;
int size = 0;

void click_button(int discount_percentage)
{
	if (size == MAX_COUPONS)
	{
		printf("Coupon market is full. Cannot add more customers.\n");
		return ;
	}
	arr[rear] = discount_percentage;
	rear = (rear + 1) % MAX_COUPONS;
	size++;
}

