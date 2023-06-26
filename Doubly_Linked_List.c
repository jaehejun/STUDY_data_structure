#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for inventory management
struct Item {
    int item_id;
    char item_name[50];
    char size[10];
    char color[20];
    int quantity;
    struct Item* previous_item;
    struct Item* next_item;
};

// Clothing brand company structure
struct ClothingBrandCompany {
    struct Item* inventory_head;
    struct Item* inventory_tail;
};

// Inventory Management: Adding an item to the linked list
void add_item(struct ClothingBrandCompany* company, int item_id, char* item_name, char* size, char* color, int quantity) {
    // Create a new item
    struct Item* new_item = (struct Item*)malloc(sizeof(struct Item));
    new_item->item_id = item_id;
    strcpy(new_item->item_name, item_name);
    strcpy(new_item->size, size);
    strcpy(new_item->color, color);
    new_item->quantity = quantity;
    new_item->previous_item = NULL;
    new_item->next_item = NULL;

    // Check if the inventory is empty
    if (company->inventory_head == NULL) {
        company->inventory_head = new_item;  // Set the new item as the head
        company->inventory_tail = new_item;  // Set the new item as the tail
    } else {
        // Add the new item to the end of the list
        new_item->previous_item = company->inventory_tail;  // Update the previous pointer of the new item
        company->inventory_tail->next_item = new_item;  // Update the next pointer of the previous tail item
        company->inventory_tail = new_item;  // Set the new item as the tail
    }
}

// Inventory Management: Removing an item from the linked list
void remove_item(struct ClothingBrandCompany* company, int item_id) {
    struct Item* current_item = company->inventory_head;
    while (current_item != NULL) {
        if (current_item->item_id == item_id) {
            // Update the previous item's next pointer
            if (current_item->previous_item != NULL)
                current_item->previous_item->next_item = current_item->next_item;

            // Update the next item's previous pointer
            if (current_item->next_item != NULL)
                current_item->next_item->previous_item = current_item->previous_item;

            // Check if the item is the head of the list
            if (current_item == company->inventory_head)
                company->inventory_head = current_item->next_item;

            // Check if the item is the tail of the list
            if (current_item == company->inventory_tail)
                company->inventory_tail = current_item->previous_item;

            free(current_item);  // Free the memory occupied by the item
            break;
        }
        current_item = current_item->next_item;  // Move to the next item
    }
}

// Main function
int main()
{
    // Create a clothing brand company
    struct ClothingBrandCompany company;
    company.inventory_head = NULL;
    company.inventory_tail = NULL;

    // Add items to the inventory
    add_item(&company, 1, "T-Shirt", "M", "Blue", 10);
    add_item(&company, 2, "Jeans", "L", "Black", 5);
    add_item(&company, 3, "Dress", "S", "Red", 3);

    // Remove an item from the inventory
    remove_item(&company, 2);
}