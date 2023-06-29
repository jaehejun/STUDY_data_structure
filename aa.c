#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Structure for AVL tree node
struct Node {
    int item_number;
    char item_name[50];
    float price;
    int stock;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get the maximum of two integers
int max(int a, int b) {
    while (a > b) {
        return a;
    }
    return b;
}

// Function to get the height of a node
int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to calculate the balance factor of a node
int getBalanceFactor(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to create a new node with given details
struct Node* createNode(int item_number, char* item_name, float price, int stock) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->item_number = item_number;
    strcpy(newNode->item_name, item_name);
    newNode->price = price;
    newNode->stock = stock;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to right rotate a subtree rooted with y
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // Return new root
    return x;
}

// Function to left rotate a subtree rooted with x
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // Return new root
    return y;
}

// Function to balance the AVL tree
struct Node* balanceTree(struct Node* node, int item_number) {
    // Update height of the current node
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

    // Calculate the balance factor
    int balanceFactor = getBalanceFactor(node);

    // Perform rotations if the node is unbalanced
    if (balanceFactor > 1 && item_number < node->left->item_number)
        return rightRotate(node);

    if (balanceFactor < -1 && item_number > node->right->item_number)
        return leftRotate(node);

    if (balanceFactor > 1 && item_number > node->left->item_number) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balanceFactor < -1 && item_number < node->right->item_number) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to insert a new item into the AVL tree
struct Node* insertItem(struct Node* node, int item_number, char* item_name, float price, int stock) {
    // Perform the normal BST insertion
    if (node == NULL)
        return createNode(item_number, item_name, price, stock);

    if (item_number < node->item_number)
        node->left = insertItem(node->left, item_number, item_name, price, stock);
    else if (item_number > node->item_number)
        node->right = insertItem(node->right, item_number, item_name, price, stock);
    else // Duplicate item_number is not allowed
        return node;

    // Update the height of the ancestor node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Balance the tree
    return balanceTree(node, item_number);
}

// Function to find the node with the minimum value in a subtree
struct Node* findMinNode(struct Node* node) {
    struct Node* current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

// Function to delete a node from the AVL tree
struct Node* deleteItem(struct Node* root, int item_number) {
    // Perform the normal BST deletion
    if (root == NULL)
        return root;

    if (item_number < root->item_number)
        root->left = deleteItem(root->left, item_number);
    else if (item_number > root->item_number)
        root->right = deleteItem(root->right, item_number);
    else {
        // Node to be deleted found

        // Node with only one child or no child
        struct Node* temp;
        if (root->left == NULL || root->right == NULL) {
            if (root->left == NULL)
                temp = root->right;
            else
                temp = root->left;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case
                *root = *temp;

            free(temp);
        } else {
            // Node with two children
            struct Node* successor = findMinNode(root->right);

            // Copy the successor's data to this node
            root->item_number = successor->item_number;
            strcpy(root->item_name, successor->item_name);
            root->price = successor->price;
            root->stock = successor->stock;

            // Delete the successor
            root->right = deleteItem(root->right, successor->item_number);
        }
    }

    // If the tree had only one node, then return
    if (root == NULL)
        return root;

    // Update the height of the current node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // Balance the tree
    return balanceTree(root, item_number);
}

// Function to search for an item in the AVL tree
void searchItem(struct Node* root, int item_number) {
    if (root == NULL) {
        printf("Item not found.\n");
        return;
    }

    if (item_number == root->item_number) {
        printf("Item: %s\n", root->item_name);
        printf("Stock: %d\n", root->stock);
        return;
    }

    if (item_number < root->item_number)
        searchItem(root->left, item_number);
    else
        searchItem(root->right, item_number);
}

// Function to order an item
void orderItem(struct Node* root, int item_number) {
    if (root == NULL) {
        printf("Item not found.\n");
        return;
    }

    if (item_number == root->item_number) {
        if (root->stock > 0) {
            root->stock--;
            printf("Ordered item: %s\n", root->item_name);
            printf("Modified Stock: %d\n", root->stock);
        } else {
            printf("Item is sold out.\n");
        }
        return;
    }

    if (item_number < root->item_number)
        orderItem(root->left, item_number);
    else
        orderItem(root->right, item_number);
}

// Function to refund an item
void refundItem(struct Node* root, int item_number) {
    if (root == NULL) {
        printf("Item not found.\n");
        return;
    }

    if (item_number == root->item_number) {
        root->stock++;
        printf("Refunded item: %s\n", root->item_name);
        printf("Modified Stock: %d\n", root->stock);
        return;
    }

    if (item_number < root->item_number)
        refundItem(root->left, item_number);
    else
        refundItem(root->right, item_number);
}

// Function to print the AVL tree in inorder traversal
void printInorder(struct Node* root) {
    if (root != NULL) {
        printInorder(root->left);
        printf("Item: %s\n", root->item_name);
        printf("Stock: %d\n", root->stock);
        printInorder(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, item_number;
    char item_name[50];
    float price;
    int stock;

    do {
        printf("\n----- Inventory Management Menu -----\n");
        printf("1. Insert Item\n");
        printf("2. Delete Item\n");
        printf("3. Search Item\n");
        printf("4. Order Item\n");
        printf("5. Refund Item\n");
        printf("6. Print Inventory\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter item number: ");
                scanf("%d", &item_number);
                printf("Enter item name: ");
                scanf("%s", item_name);
                printf("Enter price: ");
                scanf("%f", &price);
                printf("Enter stock: ");
                scanf("%d", &stock);
                root = insertItem(root, item_number, item_name, price, stock);
                break;
            case 2:
                printf("Enter item number to delete: ");
                scanf("%d", &item_number);
                root = deleteItem(root, item_number);
                break;
            case 3:
                printf("Enter item number to search: ");
                scanf("%d", &item_number);
                searchItem(root, item_number);
                break;
            case 4:
                printf("Enter item number to order: ");
                scanf("%d", &item_number);
                orderItem(root, item_number);
                break;
            case 5:
                printf("Enter item number to refund: ");
                scanf("%d", &item_number);
                refundItem(root, item_number);
                break;
            case 6:
                printf("Inventory:\n");
                printInorder(root);
                break;
            case 7:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    // TODO: Free the memory allocated for the AVL tree nodes

    return 0;
}