#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SizeNode {
    char size;
    int stock;
    struct SizeNode* next;
} SizeNode;

typedef struct ItemNode {
    char item_name[50];
    int item_number;
    float price;
    SizeNode* sizes;
    struct ItemNode* left;
    struct ItemNode* right;
} ItemNode;

ItemNode* createItemNode(char item_name[], int item_number, float price) {
    ItemNode* newNode = (ItemNode*)malloc(sizeof(ItemNode)); // Create a new item node in memory
    strcpy(newNode->item_name, item_name); // Copy the item name into the new node
    newNode->item_number = item_number; // Assign the item number to the new node
    newNode->price = price; // Assign the item price to the new node
    newNode->sizes = NULL; // Initialize the sizes linked list as NULL
    newNode->left = NULL; // Initialize the left child pointer as NULL
    newNode->right = NULL; // Initialize the right child pointer as NULL
    return newNode; // Return the newly created item node
}

SizeNode* createSizeNode(char size, int stock) {
    SizeNode* newSizeNode = (SizeNode*)malloc(sizeof(SizeNode)); // Create a new size node in memory
    newSizeNode->size = size; // Assign the size to the new node
    newSizeNode->stock = stock; // Assign the stock to the new node
    newSizeNode->next = NULL; // Initialize the next pointer as NULL
    return newSizeNode; // Return the newly created size node
}

SizeNode* findSizeNode(SizeNode* sizes, char size) {
    SizeNode* current = sizes; // Start from the head of the sizes linked list
    while (current != NULL) {
        if (current->size == size) // If the current size matches the given size, return the current node
            return current;
        current = current->next; // Move to the next node in the sizes linked list
    }
    return NULL; // If the size is not found, return NULL
}

ItemNode* insertItem(ItemNode* root, char item_name[], int item_number, float price, char size, int stock) {
    if (root == NULL) {
        ItemNode* newItemNode = createItemNode(item_name, item_number, price); // Create a new item node
        SizeNode* newSizeNode = createSizeNode(size, stock); // Create a new size node for the given size and stock
        newItemNode->sizes = newSizeNode; // Set the sizes linked list of the new item node to the new size node
        return newItemNode; // Return the newly created item node
    }

    if (item_number < root->item_number) {
        root->left = insertItem(root->left, item_name, item_number, price, size, stock); // Recursively insert the item into the left subtree
    } else if (item_number > root->item_number) {
        root->right = insertItem(root->right, item_name, item_number, price, size, stock); // Recursively insert the item into the right subtree
    } else {
        SizeNode* sizeNode = findSizeNode(root->sizes, size); // Check if the given size already exists for the item
        if (sizeNode != NULL) {
            sizeNode->stock += stock; // If the size exists, update the stock
        } else {
            SizeNode* newSizeNode = createSizeNode(size, stock); // If the size does not exist, create a new size node
            newSizeNode->next = root->sizes; // Add the new size node to the beginning of the sizes linked list
            root->sizes = newSizeNode; // Update the sizes linked list of the item node
        }
    }
    return root; // Return the root of the modified item tree
}

void searchItem(ItemNode* root, int item_number) {
    if (root == NULL) {
        printf("Item not found.\n"); // If the item tree is empty or the item is not found, print a message
        return;
    }

    if (item_number < root->item_number) {
        searchItem(root->left, item_number); // Recursively search for the item in the left subtree
    } else if (item_number > root->item_number) {
        searchItem(root->right, item_number); // Recursively search for the item in the right subtree
    } else {
        printf("Item Name: %s\n", root->item_name); // Print the item details
        printf("Item Number: %d\n", root->item_number);
        printf("Price: %.2f\n", root->price);

        SizeNode* sizeNode = root->sizes; // Traverse the sizes linked list of the item
        while (sizeNode != NULL) {
            printf("Size: %c, Stock: %d\n", sizeNode->size, sizeNode->stock); // Print the size and stock of the item
            sizeNode = sizeNode->next; // Move to the next size node
        }
    }
}

void orderItem(ItemNode* root, int item_number, char size) {
    if (root == NULL) {
        printf("Item not found.\n"); // If the item tree is empty or the item is not found, print a message
        return;
    }

    if (item_number < root->item_number) {
        orderItem(root->left, item_number, size); // Recursively order the item in the left subtree
    } else if (item_number > root->item_number) {
        orderItem(root->right, item_number, size); // Recursively order the item in the right subtree
    } else {
        SizeNode* sizeNode = findSizeNode(root->sizes, size); // Check if the given size exists for the item
        if (sizeNode != NULL) {
            if (sizeNode->stock > 0) {
                sizeNode->stock--; // If the size exists and stock is available, reduce the stock
                printf("Order placed. New stock for item %d, size %c: %d\n", item_number, size, sizeNode->stock);
            } else {
                printf("Item %d, size %c is sold out.\n", item_number, size); // If the stock is empty, print a message
            }
        } else {
            printf("Size %c not available for item %d.\n", size, item_number); // If the size is not found, print a message
        }
    }
}

void refundItem(ItemNode* root, int item_number, char size) {
    if (root == NULL) {
        printf("Item not found.\n"); // If the item tree is empty or the item is not found, print a message
        return;
    }

    if (item_number < root->item_number) {
        refundItem(root->left, item_number, size); // Recursively refund the item in the left subtree
    } else if (item_number > root->item_number) {
        refundItem(root->right, item_number, size); // Recursively refund the item in the right subtree
    } else {
        SizeNode* sizeNode = findSizeNode(root->sizes, size); // Check if the given size exists for the item
        if (sizeNode != NULL) {
            sizeNode->stock++; // If the size exists, increase the stock
            printf("Refund processed. New stock for item %d, size %c: %d\n", item_number, size, sizeNode->stock);
        } else {
            printf("Size %c not available for item %d.\n", size, item_number); // If the size is not found, print a message
        }
    }
}

void printInventory(ItemNode* root) {
    if (root == NULL)
        return;

    printInventory(root->left); // Recursively print the inventory in the left subtree
    printf("Item Name: %s\n", root->item_name); // Print the item details
    printf("Item Number: %d\n", root->item_number);
    printf("Price: %.2f\n", root->price);

    SizeNode* sizeNode = root->sizes; // Traverse the sizes linked list of the item
    while (sizeNode != NULL) {
        printf("Size: %c, Stock: %d\n", sizeNode->size, sizeNode->stock); // Print the size and stock of the item
        sizeNode = sizeNode->next; // Move to the next size node
    }

    printInventory(root->right); // Recursively print the inventory in the right subtree
}

void freeInventory(ItemNode* root) {
    if (root == NULL)
        return;

    freeInventory(root->left); // Recursively free the memory in the left subtree
    freeInventory(root->right); // Recursively free the memory in the right subtree

    SizeNode* sizeNode = root->sizes; // Traverse the sizes linked list of the item
    while (sizeNode != NULL) {
        SizeNode* next = sizeNode->next; // Store the next size node
        free(sizeNode); // Free the current size node
        sizeNode = next; // Move to the next size node
    }

    free(root); // Free the memory allocated for the item node
}

int main() {
    ItemNode* root = NULL; // Initialize the item tree as empty
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
        scanf("%d", &choice); // Read the user's choice

        switch (choice) {
            case 1: {
                char item_name[50];
                int item_number;
                float price;
                char size;
                int stock;

                printf("Enter item name: ");
                scanf("%s", item_name);
                printf("Enter item number: ");
                scanf("%d", &item_number);
                printf("Enter price: ");
                scanf("%f", &price);

                while (1) {
                    printf("Enter size (S/M/L) or '0' to finish: ");
                    scanf(" %c", &size);
                    if (size == '0')
                        break;

                    printf("Enter stock: ");
                    scanf("%d", &stock);
                    root = insertItem(root, item_name, item_number, price, size, stock); // Insert the item into the inventory
                }
                printf("Item inserted.\n");
                break;
            }
            case 2: {
                int item_number;
                printf("Enter item number: ");
                scanf("%d", &item_number);
                searchItem(root, item_number); // Search for the item in the inventory
                break;
            }
            case 3: {
                int item_number;
                char size;
                printf("Enter item number: ");
                scanf("%d", &item_number);
                printf("Enter size (S/M/L): ");
                scanf(" %c", &size);
                orderItem(root, item_number, size); // Order the item from the inventory
                break;
            }
            case 4: {
                int item_number;
                char size;
                printf("Enter item number: ");
                scanf("%d", &item_number);
                printf("Enter size (S/M/L): ");
                scanf(" %c", &size);
                refundItem(root, item_number, size); // Refund the item to the inventory
                break;
            }
            case 5:
                printInventory(root); // Print the inventory
                break;
            case 6:
                freeInventory(root); // Free the memory allocated for the inventory
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    }

    return 0;
}
