#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include "Room.h"

#define MAX_INVENTORY 10 // Maximum number of items a player can carry

// Player structure
typedef struct {
    char name[50];
    int health;
    int strength;
    Item* inventory[MAX_INVENTORY];
    int inventory_size;
} Player;

void initialize_player(Player* player, const char* name);
void display_inventory(const Player* player);
int add_item_to_inventory(Player* player, Item* item);
int drop_item_from_inventory(Player* player, const char* item_name);
Item* use_item_from_inventory(Player* player,Room* current_room, const char* item_name);
void destroy_player(Player* player);

#endif