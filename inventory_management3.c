#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for offline store stock
typedef struct {
    char name[20];
    int stock;
} OfflineStore;

// Structure for product data
typedef struct {
    int item_number;
    char item_name[20];
    int price;
    int online_stock_s;
    int online_stock_m;
    int online_stock_l;
    OfflineStore offline_stores[3];
} Product;

// Structure for AVL tree node
typedef struct Node {
    Product data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

// Function to get the height of a node
int getHeight(Node* node) {
    if (node == NULL)
        return 0;

    return node->height;
}

// Function to calculate the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node with the given data
Node* createNode(Product data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Function to right rotate a subtree rooted with node
Node* rightRotate(Node* node) {
    Node* leftChild = node->left;
    Node* rightGrandchild = leftChild->right;

    // Perform rotation
    leftChild->right = node;
    node->left = rightGrandchild;

    // Update heights
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    leftChild->height = 1 + max(getHeight(leftChild->left), getHeight(leftChild->right));

    // Return new root
    return leftChild;
}

// Function to left rotate a subtree rooted with node
Node* leftRotate(Node* node) {
    Node* rightChild = node->right;
    Node* leftGrandchild = rightChild->left;

    // Perform rotation
    rightChild->left = node;
    node->right = leftGrandchild;

    // Update heights
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    rightChild->height = 1 + max(getHeight(rightChild->left), getHeight(rightChild->right));

    // Return new root
    return rightChild;
}

// Function to get the balance factor of a node
int getBalance(Node* node) {
    if (node == NULL)
        return 0;

    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a new node into the AVL tree
Node* insert(Node* node, Product data) {
    if (node == NULL)
        return createNode(data);

    if (data.item_number < node->data.item_number)
        node->left = insert(node->left, data);
    else if (data.item_number > node->data.item_number)
        node->right = insert(node->right, data);
    else
        return node;  // Duplicate item numbers are not allowed

    // Update the height of the current node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // Check the balance factor and perform rotations if necessary

    // Left Left case
    if (getBalance(node) > 1 && data.item_number < node->left->data.item_number)
        return rightRotate(node);

    // Left Right case
    if (getBalance(node) > 1 && data.item_number > node->left->data.item_number) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Right case
    if (getBalance(node) < -1 && data.item_number > node->right->data.item_number)
        return leftRotate(node);

    // Right Left case
    if (getBalance(node) < -1 && data.item_number < node->right->data.item_number) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to search for a specific item and size in the AVL tree
void search(Node* node, int item_number, char size) {
    if (node == NULL) {
        printf("Item not found.\n");
        return;
    }

    if (item_number < node->data.item_number)
        search(node->left, item_number, size);
    else if (item_number > node->data.item_number)
        search(node->right, item_number, size);
    else {
        printf("Item Number: %d\n", node->data.item_number);
        printf("Item Name: %s\n", node->data.item_name);
        printf("Price: %d\n", node->data.price);

        if (size == 'S')
            printf("Online Stock (Size S): %d\n", node->data.online_stock_s);
        else if (size == 'M')
            printf("Online Stock (Size M): %d\n", node->data.online_stock_m);
        else if (size == 'L')
            printf("Online Stock (Size L): %d\n", node->data.online_stock_l);

        int offlineStockFound = 0;
        for (int i = 0; i < 3; i++) {
            if (node->data.offline_stores[i].stock > 0 && size == 'S') {
                printf("Offline Stock (Store: %s, Size: S): %d\n", node->data.offline_stores[i].name,
                       node->data.offline_stores[i].stock);
                offlineStockFound = 1;
            } else if (node->data.offline_stores[i].stock > 0 && size == 'M') {
                printf("Offline Stock (Store: %s, Size: M): %d\n", node->data.offline_stores[i].name,
                       node->data.offline_stores[i].stock);
                offlineStockFound = 1;
            } else if (node->data.offline_stores[i].stock > 0 && size == 'L') {
                printf("Offline Stock (Store: %s, Size: L): %d\n", node->data.offline_stores[i].name,
                       node->data.offline_stores[i].stock);
                offlineStockFound = 1;
            }
        }

        if (!offlineStockFound)
            printf("No offline stock available for size %c.\n", size);
    }
}

// Function to traverse the AVL tree in inorder
void inorderTraversal(Node* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("Item Number: %d\n", node->data.item_number);
        printf("Item Name: %s\n", node->data.item_name);
        printf("Price: %d\n", node->data.price);
        printf("Online Stock (Size S): %d\n", node->data.online_stock_s);
        printf("Online Stock (Size M): %d\n", node->data.online_stock_m);
        printf("Online Stock (Size L): %d\n", node->data.online_stock_l);
        for (int i = 0; i < 3; i++) {
            printf("Offline Stock (Store: %s, Size: S): %d\n", node->data.offline_stores[i].name,
                   node->data.offline_stores[i].stock);
            printf("Offline Stock (Store: %s, Size: M): %d\n", node->data.offline_stores[i].name,
                   node->data.offline_stores[i].stock);
            printf("Offline Stock (Store: %s, Size: L): %d\n", node->data.offline_stores[i].name,
                   node->data.offline_stores[i].stock);
        }
        printf("\n");
        inorderTraversal(node->right);
    }
}

int main(int argc, char* argv[]) {
    Node* root = NULL;

    if (argc < 2) {
        printf("Insufficient arguments.\n");
        return 1;
    }

    if (strcmp(argv[1], "add") == 0) {
        if (argc != 26) {
            printf("Invalid number of arguments.\n");
            return 1;
        }

        int item_number = atoi(argv[2]);
        char* item_name = argv[3];
        int price = atoi(argv[4]);
        int online_stock_s = atoi(argv[5]);
        int online_stock_m = atoi(argv[7]);
        int online_stock_l = atoi(argv[9]);
        char* store_name1 = argv[11];
        int offline_stock_s = atoi(argv[13]);
        char* store_name2 = argv[15];
        int offline_stock_m = atoi(argv[17]);
        char* store_name3 = argv[19];
        int offline_stock_l = atoi(argv[21]);

        Product newProduct;
        newProduct.item_number = item_number;
        strcpy(newProduct.item_name, item_name);
        newProduct.price = price;
        newProduct.online_stock_s = online_stock_s;
        newProduct.online_stock_m = online_stock_m;
        newProduct.online_stock_l = online_stock_l;

        strcpy(newProduct.offline_stores[0].name, store_name1);
        newProduct.offline_stores[0].stock = offline_stock_s;
        strcpy(newProduct.offline_stores[1].name, store_name2);
        newProduct.offline_stores[1].stock = offline_stock_m;
        strcpy(newProduct.offline_stores[2].name, store_name3);
        newProduct.offline_stores[2].stock = offline_stock_l;

        root = insert(root, newProduct);
        printf("Item added successfully.\n");
    } else if (strcmp(argv[1], "search") == 0) {
        if (argc != 4) {
            printf("Invalid number of arguments.\n");
            return 1;
        }

        int item_number = atoi(argv[2]);
        char size = argv[3][0];

        search(root, item_number, size);
    } else {
        printf("Invalid command.\n");
        return 1;
    }

    return 0;
}
