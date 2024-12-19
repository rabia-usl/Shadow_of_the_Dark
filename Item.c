#include "Item.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Create a new item with a name and description
Item* create_item(const char* name, const char* description) {
    if (!name || !description) return NULL;

    Item* item = (Item*)malloc(sizeof(Item));
    if (!item) return NULL;

    item->name = strdup(name);
    item->description = strdup(description);

    if (!item->name || !item->description) {
        destroy_item(item);
        return NULL;
    }

    return item;
}
// Destroy an item
void destroy_item(Item* item) {
    if (!item) return;

    free(item->name);
    free(item->description);
    free(item);
}

void display_item(const Item* item) {
    if (!item) return;

    printf("Item: %s\n", item->name);
    printf("Description: %s\n", item->description);
}
