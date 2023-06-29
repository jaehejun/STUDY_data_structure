#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a store
typedef struct {
    char name[20];
    int stock;
} Store;

// Structure to represent a product
typedef struct {
    int item_number;
    int size;
    int online_stock;
    int price;
    Store offline_stores[3]; // Assuming 3 offline stores
} Product;

// Structure to represent a node in the AVL tree
typedef struct Node {
    Product data;
    int height;
    struct Node* left;
    struct Node* right;
} Node;

// Function to get the height of a node
int getHeight(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node
Node* createNode(Product data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to right rotate subtree rooted with y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

// Function to left rotate subtree rooted with x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

// Function to get the balance factor of a node
int getBalance(Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert a product into the AVL tree
Node* insert(Node* node, Product data) {
    if (node == NULL)
        return createNode(data);

    if (data.item_number < node->data.item_number)
        node->left = insert(node->left, data);
    else if (data.item_number > node->data.item_number)
        node->right = insert(node->right, data);
    else
        return node; // Duplicate item_numbers are not allowed

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    // Left Left case
    if (balance > 1 && data.item_number < node->left->data.item_number)
        return rightRotate(node);

    // Right Right case
    if (balance < -1 && data.item_number > node->right->data.item_number)
        return leftRotate(node);

    // Left Right case
    if (balance > 1 && data.item_number > node->left->data.item_number) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left case
    if (balance < -1 && data.item_number < node->right->data.item_number) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to print the AVL tree in inorder traversal
void inorderTraversal(Node* node) {
    if (node == NULL)
        return;

    inorderTraversal(node->left);

    printf("Item Number: %d\n", node->data.item_number);
    printf("Size: %d\n", node->data.size);
    printf("Online Stock: %d\n", node->data.online_stock);
    printf("Price: %d\n", node->data.price);

    for (int i = 0; i < 3; i++) {
        if (node->data.offline_stores[i].stock > 0) {
            printf("Store: %s\n", node->data.offline_stores[i].name);
            printf("Stock: %d\n", node->data.offline_stores[i].stock);
        }
    }

    printf("\n");

    inorderTraversal(node->right);
}

// Function to search for a specific item and size in the AVL tree
void search(Node* node, int item_number, int size) {
    if (node == NULL) {
        printf("Item not found.\n");
        return;
    }

    if (item_number < node->data.item_number)
        search(node->left, item_number, size);
    else if (item_number > node->data.item_number)
        search(node->right, item_number, size);
    else {
        if (size == node->data.size) {
            printf("Item Number: %d\n", node->data.item_number);
            printf("Size: %d\n", node->data.size);
            printf("Online Stock: %d\n", node->data.online_stock);
            printf("Price: %d\n", node->data.price);

            for (int i = 0; i < 3; i++) {
                if (node->data.offline_stores[i].stock > 0) {
                    printf("Store: %s\n", node->data.offline_stores[i].name);
                    printf("Stock: %d\n", node->data.offline_stores[i].stock);
                }
            }
        } else {
            printf("Item size not found.\n");
        }
    }
}

// Function to modify the stock of a specific size for a product
void modifyStock(Node* node, int item_number, int size, int new_stock) {
    if (node == NULL) {
        printf("Item not found.\n");
        return;
    }

    if (item_number < node->data.item_number)
        modifyStock(node->left, item_number, size, new_stock);
    else if (item_number > node->data.item_number)
        modifyStock(node->right, item_number, size, new_stock);
    else {
        if (size == node->data.size) {
            node->data.online_stock = new_stock;
            printf("Online stock modified successfully.\n");
        } else {
            for (int i = 0; i < 3; i++) {
                if (size == node->data.offline_stores[i].stock) {
                    node->data.offline_stores[i].stock = new_stock;
                    printf("Offline stock modified successfully.\n");
                    return;
                }
            }
            printf("Item size not found.\n");
        }
    }
}

// Function to modify the price of a product
void modifyPrice(Node* node, int item_number, int new_price) {
    if (node == NULL) {
        printf("Item not found.\n");
        return;
    }

    if (item_number < node->data.item_number)
        modifyPrice(node->left, item_number, new_price);
    else if (item_number > node->data.item_number)
        modifyPrice(node->right, item_number, new_price);
    else {
        node->data.price = new_price;
        printf("Price modified successfully.\n");
    }
}

// Function to delete a node from the AVL tree
Node* deleteNode(Node* root, int item_number) {
    if (root == NULL)
        return root;

    if (item_number < root->data.item_number)
        root->left = deleteNode(root->left, item_number);
    else if (item_number > root->data.item_number)
        root->right = deleteNode(root->right, item_number);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            Node* temp = root->right;
            while (temp->left != NULL)
                temp = temp->left;

            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data.item_number);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    // Left Left case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int main() {
    Node* root = NULL;
    int choice;
    int item_number, size, stock, price;
    char store_name[20];

    while (1) {
        printf("1. Add item\n");
        printf("2. Delete item\n");
        printf("3. Modify stock of specific size\n");
        printf("4. Modify price\n");
        printf("5. Search for specific item and size\n");
        printf("6. Print all items\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter item number: ");
                scanf("%d", &item_number);
                printf("Enter size: ");
                scanf("%d", &size);
                printf("Enter online stock: ");
                scanf("%d", &stock);
                printf("Enter price: ");
                scanf("%d", &price);

                Product newProduct;
                newProduct.item_number = item_number;
                newProduct.size = size;
                newProduct.online_stock = stock;
                newProduct.price = price;

                for (int i = 0; i < 3; i++) {
                    printf("Enter store name for offline stock %d: ", i + 1);
                    scanf("%s", store_name);
                    strcpy(newProduct.offline_stores[i].name, store_name);
                    printf("Enter stock for store %s: ", store_name);
                    scanf("%d", &stock);
                    newProduct.offline_stores[i].stock = stock;
                }

                root = insert(root, newProduct);
                printf("Item added successfully.\n");
                break;

            case 2:
                printf("Enter item number to delete: ");
                scanf("%d", &item_number);
                root = deleteNode(root, item_number);
                printf("Item deleted successfully.\n");
                break;

            case 3:
                printf("Enter item number: ");
                scanf("%d", &item_number);
                printf("Enter size: ");
                scanf("%d", &size);
                printf("Enter new stock: ");
                scanf("%d", &stock);
                modifyStock(root, item_number, size, stock);
                break;

            case 4:
                printf("Enter item number: ");
                scanf("%d", &item_number);
                printf("Enter new price: ");
                scanf("%d", &price);
                modifyPrice(root, item_number, price);
                break;

            case 5:
                printf("Enter item number: ");
                scanf("%d", &item_number);
                printf("Enter size: ");
                scanf("%d", &size);
                search(root, item_number, size);
                break;

            case 6:
                printf("Printing all items:\n");
                inorderTraversal(root);
                break;

            case 7:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
