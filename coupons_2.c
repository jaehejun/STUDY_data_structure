#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_CUSTOMERS 10000

// Structure representing a coupon
typedef struct Coupon {
    int discount_percentage;
} Coupon;

// Structure representing a customer
typedef struct Customer {
    int discount_percentage;
    Coupon coupon;
} Customer;

// Structure representing the coupon market
typedef struct CouponMarket {
    Customer customers[MAX_CUSTOMERS];
    int front;
    int rear;
    int size;
} CouponMarket;

// Function to initialize the coupon market
CouponMarket* createCouponMarket() {
    CouponMarket* market = (CouponMarket*)malloc(sizeof(CouponMarket));
    market->front = 0;
    market->rear = 0;
    market->size = 0;
    return market;
}

// Function to add a new customer to the publish queue
void click_button(CouponMarket* market, int discount_percentage) {
    if (market->size == MAX_CUSTOMERS) {
        printf("Coupon market is full. Cannot add more customers.\n");
        return;
    }

    market->customers[market->rear].discount_percentage = discount_percentage;
    market->rear = (market->rear + 1) % MAX_CUSTOMERS;
    market->size++;
}

// Function to generate the coupons for each customer in the publish queue
void process_publish_queue(CouponMarket* market) {
    if (market->size == 0) {
        printf("No customers in the publish queue.\n");
        return;
    }

    int numCustomers = market->size;
    int numCoupons[11] = {1, 3000, 2000, 1000, 500, 300, 200, 100, 50, 30, 10};
    int couponIndex = 0;

    // Generate coupons for each customer in the publish queue
    for (int i = 0; i < numCustomers; i++) {
        int index = (market->front + i) % MAX_CUSTOMERS;
        int discountPercentage = market->customers[index].discount_percentage;

        int numAvailableCoupons = numCoupons[couponIndex];
        if (numAvailableCoupons <= 0) {
            couponIndex++;
            numAvailableCoupons = numCoupons[couponIndex];
        }

        market->customers[index].coupon.discount_percentage = discountPercentage;
        numCoupons[couponIndex]--;
    }

    printf("Coupons generated for %d customers.\n", market->size);

    // Reset the publish queue
    market->front = market->rear;
    market->size = 0;
}

// Example usage:
int main() {
    CouponMarket* market = createCouponMarket();

    int numCustomers = 10000;

    // Simulating customers entering the waiting line and clicking the "publish" button
    for (int i = 0; i < numCustomers; i++) {
        int discountPercentage = (rand() % 90) + 10; // Generate a random discount percentage between 10 and 99
        click_button(market, discountPercentage);
    }

    // Process the publish queue and generate the coupons
    process_publish_queue(market);

    // Printing the generated coupons
    for (int i = 0; i < numCustomers; i++) {
        printf("Customer %d: Discount Percentage: %d, Coupon Percentage: %d\n", i + 1, market->customers[i].discount_percentage, market->customers[i].coupon.discount_percentage);
    }

    free(market);
    return 0;
}