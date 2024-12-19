#ifndef ROOM_H
#define ROOM_H

#include "Creature.h"
#include "Item.h"

#define MAX_ITEMS 10 // Maximum number of items in a room
#define MAX_CONNECTIONS 4 // Maximum number of connections a room can have

typedef struct Room {
    char *description; 
    Creature* creature;
    struct Room *up, *down, *left, *right;
    Item* items[MAX_ITEMS];
    int item_count;
} Room;

void initialize_room(Room* room, const char* description);
void connect_rooms(Room* room1, Room* room2,const char *direction);
void describe_room(const Room* room);
void add_item_to_room(Room* room, Item* item);
void add_creature(Room* room, Creature* creature);
void create_items(Room *room, Item *items[], int size);
void destroy_room(Room* room);

#endif