#include <stdio.h>
#include <stdlib.h>

typedef struct Customer {
    int id;
    char name[100];
    int age;
    // Additional customer data fields
} Customer;

typedef enum Color {
    RED,
    BLACK
} Color;

typedef struct Node {
    Customer customer;
    Color color;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
} Node;

Node* createNode(Customer customer) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->customer = customer;
    newNode->color = RED; // New nodes are always red
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// Function to perform left rotation
void leftRotate(Node** root, Node* x) {
    Node* y = x->right;
    x->right = y->left;

    if (x->right != NULL)
        x->right->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Function to perform right rotation
void rightRotate(Node** root, Node* y) {
    Node* x = y->left;
    y->left = x->right;

    if (y->left != NULL)
        y->left->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

// Function to fix the Red-Black Tree after insertion
void fixInsert(Node** root, Node* z) {
    while (z->parent != NULL && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node* y = z->parent->parent->right;

            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(root, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        } else {
            Node* y = z->parent->parent->left;

            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
   }

    (*root)->color = BLACK;
}

// Function to insert a customer into the Red-Black Tree, rearranging based on age and changing IDs accordingly
void insertNode(Node** root, Customer customer) {
    Node* z = createNode(customer);
    Node* y = NULL;
    Node* x = *root;

    // Rearrange based on age
    while (x != NULL) {
        y = x;
        if (z->customer.age < x->customer.age)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NULL)
        *root = z;
    else if (z->customer.age < y->customer.age)
        y->left = z;
    else
        y->right = z;

    fixInsert(root, z);
}

// Function to find a customer in the Red-Black Tree
Node* searchNode(Node* root, int customerId) {
    while (root != NULL) {
        if (customerId < root->customer.id)
            root = root->left;
        else if (customerId > root->customer.id)
            root = root->right;
        else
            return root;
    }
    return NULL;
}

// Function to find the minimum node in a subtree rooted at a given node
Node* findMinimum(Node* node) {
    if (node == NULL)
        return NULL;
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Function to fix the Red-Black Tree after deletion
void fixDelete(Node** root, Node* x) {
    while (x != *root && (x == NULL || x->color == BLACK)) {
        if (x == x->parent->left) {
            Node* w = x->parent->right;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }

            if ((w->left == NULL || w->left->color == BLACK) && (w->right == NULL || w->right->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right == NULL || w->right->color == BLACK) {
                    if (w->left != NULL)
                        w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->right != NULL)
                    w->right->color = BLACK;
                leftRotate(root, x->parent);
                x = *root;
            }
        } else {
            Node* w = x->parent->left;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }

            if ((w->right == NULL || w->right->color == BLACK) && (w->left == NULL || w->left->color == BLACK)) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left == NULL || w->left->color == BLACK) {
                    if (w->right != NULL)
                        w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                if (w->left != NULL)
                    w->left->color = BLACK;
                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }
    if (x != NULL)
        x->color = BLACK;
}

// Function to delete a customer from the Red-Black Tree
void deleteNode(Node** root, int customerId) {
    Node* z = searchNode(*root, customerId);
    if (z == NULL) {
        printf("Customer with ID %d not found in the database.\n", customerId);
        return;
    }

    Node* x;
    Node* y = z;
    Color yOriginalColor = y->color;

    if (z->left == NULL) {
        x = z->right;
        if (z->parent == NULL)
            *root = x;
        else if (z == z->parent->left)
            z->parent->left = x;
        else
            z->parent->right = x;
        if (x != NULL)
            x->parent = z->parent;
    } else if (z->right == NULL) {
        x = z->left;
        if (z->parent == NULL)
            *root = x;
        else if (z == z->parent->left)
            z->parent->left = x;
        else
            z->parent->right = x;
        if (x != NULL)
            x->parent = z->parent;
    } else {
        y = findMinimum(z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z)
            x->parent = y;
        else {
            if (y->right != NULL)
                y->right->parent = y->parent;
            y->parent->left = x;
            y->right = z->right;
            y->right->parent = y;
        }

        if (z->parent == NULL)
            *root = y;
        else if (z == z->parent->left)
            z->parent->left = y;
        else
            z->parent->right = y;
        y->parent = z->parent;
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (yOriginalColor == BLACK)
        fixDelete(root, x);
}

// Function to update the IDs based on the new order determined by age
void updateIds(Node* root, int* newId) {
    if (root != NULL) {
        updateIds(root->left, newId);
        root->customer.id = (*newId)++;
        updateIds(root->right, newId);
    }
}

// Function to traverse the Red-Black Tree in-order
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Customer ID: %d, Name: %s, Age: %d\n", root->customer.id, root->customer.name, root->customer.age);
        inorderTraversal(root->right);
    }
}

// Function to free the memory allocated for the Red-Black Tree
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;

    // Inserting sample customer data
    Customer customer1 = { 1, "JaeHee Jung", 30 };
    insertNode(&root, customer1);

    Customer customer2 = { 2, "HyungJun Park", 20 };
    insertNode(&root, customer2);

    Customer customer3 = { 3, "Shib Kim", 40 };
    insertNode(&root, customer3);

    // Rearrange the IDs based on the new order determined by age
    int newId = 1;
    updateIds(root, &newId);

    // Traversing and printing the Red-Black Tree
    printf("Customer Database:\n");
    inorderTraversal(root);

    // Deleting a customer from the Red-Black Tree
    int customerIdToDelete = 2;
    deleteNode(&root, customerIdToDelete);
    printf("Customer with ID %d deleted.\n", customerIdToDelete);

    // Rearrange the IDs again after deletion
    newId = 1;
    updateIds(root, &newId);

    // Traversing and printing the Red-Black Tree after deletion
    printf("Customer Database after Deletion:\n");
    inorderTraversal(root);

    // Freeing the memory allocated for the Red-Black Tree
    freeTree(root);

    return 0;
}