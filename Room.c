#include "Room.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// Initialize the room with a description
void initialize_room(Room* room, const char* description) {

    if (!room) return;
    room->description = strdup(description);
    room->up = NULL;
    room->down = NULL;
    room->left = NULL;
    room->right = NULL;
    room->creature = NULL;
    for (int i = 0; i < MAX_ITEMS; i++) {
        room->items[i] = NULL;
    }
    room->item_count = 0;
}
// Connect two rooms in a specified direction
void connect_rooms(Room* room1, Room* room2, const char *direction) {
    if (!room1 || !room2 ) return;
    if(strcmp(direction, "up") == 0) {
        room1->up = room2;
        room2->down = room1;
    } else if(strcmp(direction, "down") == 0) {
        room1->down = room2;
        room2->up = room1;
    } else if(strcmp(direction, "left") == 0) {
        room1->left = room2;
        room2->right = room1;
    } else if(strcmp(direction, "right") == 0) {
        room1->right = room2;
        room2->left = room1;
    }
    
}
// Add an item to the room
void add_item_to_room(Room* room, Item* item) {
    if (!room || !item) return;
    if (room->item_count < MAX_ITEMS) {
        room->items[room->item_count++] = item;
    }
}
// Add a creature to the room
void add_creature(Room* room, Creature* creature) {
    if (!room || !creature) return;
    room->creature = creature;
}
// Describe the room and its contents
void describe_room(const Room* room) {
    if (!room) return;
    printf("Room Description: %s\n", room->description);
    if (room->creature) {
        printf("Creature present: %s\n", room->creature->name);
    }
    printf("Items in the room:\n");
    for (int i = 0; i < room->item_count; i++) {
        if (room->items[i]) {
            printf("  %s\n", room->items[i]->name);
        }
    }
}
// Create items in the room
void create_items(Room *room, Item *items[], int size) {
    room->item_count = size;
    int i;
    for (i = 0; i < size && i < 5; i++) {
        room->items[i] = items[i];
    }
    for (; i < 5; i++) {
        room->items[i] = NULL;
    }
}
// Destroy the room and free memory
void destroy_room(Room* room) {
    if (!room) return;
    for (int i = 0; i < room->item_count; i++) {
        destroy_item(room->items[i]);
    }
    free(room->description);
    destroy_creature(room->creature);
    free(room);
}
