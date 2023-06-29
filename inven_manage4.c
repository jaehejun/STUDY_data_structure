#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for inventory item
typedef struct Item {
    char item_name[100];
    int item_number;
    float price;
    char size;
    int stock;
    struct Item* left;
    struct Item* right;
    int height;
} Item;

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to get the height of a node
int height(Item* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to create a new inventory item
Item* createItem(const char* item_name, int item_number, float price, char size, int stock) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    strcpy(newItem->item_name, item_name);
    newItem->item_number = item_number;
    newItem->price = price;
    newItem->size = size;
    newItem->stock = stock;
    newItem->left = NULL;
    newItem->right = NULL;
    newItem->height = 1;
    return newItem;
}

// Function to right rotate a subtree rooted with y
Item* rotateRight(Item* y) {
    Item* x = y->left;
    Item* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Function to left rotate a subtree rooted with x
Item* rotateLeft(Item* x) {
    Item* y = x->right;
    Item* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Function to get the balance factor of a node
int getBalance(Item* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to insert a new item into the AVL tree
Item* insert(Item* node, const char* item_name, int item_number, float price, char size, int stock) {
    // Perform the normal BST insertion
    if (node == NULL)
        return createItem(item_name, item_number, price, size, stock);

    if (item_number < node->item_number)
        node->left = insert(node->left, item_name, item_number, price, size, stock);
    else if (item_number > node->item_number)
        node->right = insert(node->right, item_name, item_number, price, size, stock);
    else
        return node; // Duplicate item numbers are not allowed

    // Update the height of the current node
    node->height = 1 + max(height(node->left), height(node->right));

    // Check the balance factor and balance the tree if needed
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && item_number < node->left->item_number)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && item_number > node->right->item_number)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && item_number > node->left->item_number) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && item_number < node->right->item_number) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Return the unchanged node pointer
    return node;
}

// Function to find an item in the AVL tree by item number and size
Item* search(Item* node, int item_number, char size) {
    if (node == NULL || node->item_number == item_number && node->size == size)
        return node;
    if (item_number < node->item_number)
        return search(node->left, item_number, size);
    return search(node->right, item_number, size);
}

// Function to print the stock number of online items
void printOnlineStock(Item* root) {
    if (root == NULL)
        return;
    
    printOnlineStock(root->left);
    
    if (root->stock > 0) {
        printf("Item Number: %d, Size: %c, Stock: %d\n", root->item_number, root->size, root->stock);
    }
    
    printOnlineStock(root->right);
}

// Function to print the stock number of offline items
void printOfflineStock(Item* root) {
    if (root == NULL)
        return;
    
    printOfflineStock(root->left);
    
    if (root->stock > 0) {
        printf("Item Number: %d, Size: %c, Stock: %d (Available offline)\n", root->item_number, root->size, root->stock);
    } else {
        printf("Item Number: %d, Size: %c, Stock: Sold out\n", root->item_number, root->size);
    }
    
    printOfflineStock(root->right);
}

int main() {
    Item* root = NULL;

    // Insert some sample items into the inventory
    root = insert(root, "Shirt", 1001, 29.99, 'S', 5);
    root = insert(root, "Shirt", 1001, 29.99, 'M', 0);
    root = insert(root, "Shirt", 1001, 29.99, 'L', 10);
    root = insert(root, "Pants", 2001, 39.99, 'S', 2);
    root = insert(root, "Pants", 2001, 39.99, 'M', 3);
    root = insert(root, "Pants", 2001, 39.99, 'L', 0);
    root = insert(root, "Shoes", 3001, 79.99, 'S', 8);
    root = insert(root, "Shoes", 3001, 79.99, 'M', 6);
    root = insert(root, "Shoes", 3001, 79.99, 'L', 4);

    // Print the stock number of online items
    printf("Online Stock:\n");
    printOnlineStock(root);
    printf("\n");

    // Ask for item number and size to get the stock number
    int item_number;
    char size;

    printf("Enter item number: ");
    scanf("%d", &item_number);

    printf("Enter size (S, M, L): ");
    scanf(" %c", &size);

    // Search for the item in the inventory
    Item* item = search(root, item_number, size);

    if (item != NULL) {
        // Item found, check if it is available offline
        if (item->stock > 0) {
            printf("Online Stock: %d\n", item->stock);
        } else {
            printf("Item is not available online.\n");

            // Print the stock number of offline items
            printf("Offline Stock:\n");
            printOfflineStock(root);
        }
    } else {
        printf("Item not found.\n");
    }

    return 0;
}
