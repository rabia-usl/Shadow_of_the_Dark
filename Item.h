#ifndef ITEM_H
#define ITEM_H

typedef struct {
    char* name;
    char* description;
} Item;

// Function declarations for managing items
Item* create_item(const char* name, const char* description);
void destroy_item(Item* item);
void display_item(const Item* item);

#endif 