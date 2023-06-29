#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ItemNode {
    char item_name[50];
    int item_number;
    float price;
    int stock_S;
    int stock_M;
    int stock_L;
    struct ItemNode* left;
    struct ItemNode* right;
} ItemNode;

ItemNode* createItemNode(char item_name[], int item_number, float price, int stock_S, int stock_M, int stock_L) {
    ItemNode* newNode = (ItemNode*)malloc(sizeof(ItemNode));
    strcpy(newNode->item_name, item_name);
    newNode->item_number = item_number;
    newNode->price = price;
    newNode->stock_S = stock_S;
    newNode->stock_M = stock_M;
    newNode->stock_L = stock_L;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

ItemNode* insertItem(ItemNode* root, char item_name[], int item_number, float price, int stock_S, int stock_M, int stock_L) {
    if (root == NULL) {
        return createItemNode(item_name, item_number, price, stock_S, stock_M, stock_L);
    }

    if (item_number < root->item_number) {
        root->left = insertItem(root->left, item_name, item_number, price, stock_S, stock_M, stock_L);
    } else if (item_number > root->item_number) {
        root->right = insertItem(root->right, item_name, item_number, price, stock_S, stock_M, stock_L);
    } else {
        root->stock_S += stock_S;
        root->stock_M += stock_M;
        root->stock_L += stock_L;
    }
    return root;
}

void searchItem(ItemNode* root, int item_number) {
    if (root == NULL) {
        printf("Item not found.\n");
        return;
    }

    if (item_number < root->item_number) {
        searchItem(root->left, item_number);
    } else if (item_number > root->item_number) {
        searchItem(root->right, item_number);
    } else {
        printf("Item Name: %s\n", root->item_name);
        printf("Item Number: %d\n", root->item_number);
        printf("Price: %.2f\n", root->price);
        printf("Size S, Stock: %d\n", root->stock_S);
        printf("Size M, Stock: %d\n", root->stock_M);
        printf("Size L, Stock: %d\n", root->stock_L);
    }
}

void orderItem(ItemNode* root, int item_number, char size) {
    if (root == NULL) {
        printf("Item not found.\n");
        return;
    }

    if (item_number < root->item_number) {
        orderItem(root->left, item_number, size);
    } else if (item_number > root->item_number) {
        orderItem(root->right, item_number, size);
    } else {
        int* stock = NULL;
        switch (size) {
            case 'S':
                stock = &(root->stock_S);
                break;
            case 'M':
                stock = &(root->stock_M);
                break;
            case 'L':
                stock = &(root->stock_L);
                break;
            default:
                printf("Invalid size.\n");
                return;
        }

        if (*stock > 0) {
            (*stock)--;
            printf("Order placed. New stock for item %d, size %c: %d\n", item_number, size, *stock);
        } else {
            printf("Item %d, size %c is sold out.\n", item_number, size);
        }
    }
}

void refundItem(ItemNode* root, int item_number, char size) {
    if (root == NULL) {
        printf("Item not found.\n");
        return;
    }

    if (item_number < root->item_number) {
        refundItem(root->left, item_number, size);
    } else if (item_number > root->item_number) {
        refundItem(root->right, item_number, size);
    } else {
        int* stock = NULL;
        switch (size) {
            case 'S':
                stock = &(root->stock_S);
                break;
            case 'M':
                stock = &(root->stock_M);
                break;
            case 'L':
                stock = &(root->stock_L);
                break;
            default:
                printf("Invalid size.\n");
                return;
        }

        (*stock)++;
        printf("Refund processed. New stock for item %d, size %c: %d\n", item_number, size, *stock);
    }
}

void printInventory(ItemNode* root) {
    if (root == NULL)
        return;

    printInventory(root->left);
    printf("Item Name: %s\n", root->item_name);
    printf("Item Number: %d\n", root->item_number);
    printf("Price: %.2f\n", root->price);
    printf("Size S, Stock: %d\n", root->stock_S);
    printf("Size M, Stock: %d\n", root->stock_M);
    printf("Size L, Stock: %d\n", root->stock_L);
    printInventory(root->right);
}

void freeInventory(ItemNode* root) {
    if (root == NULL)
        return;

    freeInventory(root->left);
    freeInventory(root->right);
    free(root);
}

int main() {
    ItemNode* root = NULL;
    int choice;

    while (1) {
        printf("Inventory Management System\n");
        printf("1. Insert Item\n");
        printf("2. Search Item\n");
        printf("3. Order Item\n");
        printf("4. Refund Item\n");
        printf("5. Print Inventory\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char item_name[50];
                int item_number;
                float price;
                int stock_S, stock_M, stock_L;

                printf("Enter item name: ");
                scanf("%s", item_name);
                printf("Enter item number: ");
                scanf("%d", &item_number);
                printf("Enter price: ");
                scanf("%f", &price);
                printf("Enter stock for size S: ");
                scanf("%d", &stock_S);
                printf("Enter stock for size M: ");
                scanf("%d", &stock_M);
                printf("Enter stock for size L: ");
                scanf("%d", &stock_L);

                root = insertItem(root, item_name, item_number, price, stock_S, stock_M, stock_L);
                printf("Item inserted successfully.\n");
                break;
            }
            case 2: {
                int item_number;
                printf("Enter item number to search: ");
                scanf("%d", &item_number);
                searchItem(root, item_number);
                break;
            }
            case 3: {
                int item_number;
                char size;
                printf("Enter item number to order: ");
                scanf("%d", &item_number);
                printf("Enter size (S/M/L): ");
                scanf(" %c", &size);
                orderItem(root, item_number, size);
                break;
            }
            case 4: {
                int item_number;
                char size;
                printf("Enter item number for refund: ");
                scanf("%d", &item_number);
                printf("Enter size (S/M/L): ");
                scanf(" %c", &size);
                refundItem(root, item_number, size);
                break;
            }
            case 5: {
                printf("Inventory:\n");
                printInventory(root);
                break;
            }
            case 6: {
                freeInventory(root);
                printf("Exiting the program.\n");
                return 0;
            }
            default:
                printf("Invalid choice. Please try again.\n");
        }

        printf("\n");
    }
}
