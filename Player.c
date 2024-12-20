#include "Player.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Set the player's name, health, strength, and inventory size
void initialize_player(Player* player, const char* name) {
    if (!player) return; //if player is null return
    strncpy(player->name, name, 50);
    player->health = 150;
    player->strength = 90;
    player->inventory_size = 0;
    for (int i = 0; i < MAX_INVENTORY; i++) {
        player->inventory[i] = NULL;
    }
}
//Display the player's inventory
void display_inventory(const Player* player) {
    if (!player) return;
    printf("Inventory:\n");
    if (player->inventory_size == 0) {
        printf("  (empty)\n");
        return;
    }
    for (int i = 0; i < player->inventory_size; i++) {
        if (player->inventory[i]) {
            printf("  %s\n", player->inventory[i]->name);
        }
    }
}
//Add an item to the player's inventory
int add_item_to_inventory(Player* player, Item* item) {
    if (!player || !item) return 0;
    if (player->inventory_size >= MAX_INVENTORY) {
        printf("Inventory is full!\n");
        return 0;
    }
    player->inventory[player->inventory_size++] = item;
    return 1;
}
//Drop an item from the player's inventory
int drop_item_from_inventory(Player* player, const char* item_name) {
    if (!player || !item_name) return 0;
    for (int i = 0; i < player->inventory_size; i++) {
        if (player->inventory[i] && strcmp(player->inventory[i]->name, item_name) == 0) {
            printf("Dropped %s\n", player->inventory[i]->name);
            free(player->inventory[i]);
            player->inventory[i] = NULL;
            player->inventory_size--;
            return 1;
        }
    }
    printf("Item not found in inventory!\n");
    return 0;
}
//Use an item from the player's inventory
Item* use_item_from_inventory(Player* player,Room* current_room, const char* item_name) {
    if (!player || !item_name) return NULL;
    for (int i = 0; i < player->inventory_size; i++) {
        if (player->inventory[i] && strcmp(player->inventory[i]->name, item_name) == 0) {
            Item* item = player->inventory[i];
            printf("Using %s\n", item->name);
            if(strcmp(item_name, "LIFEELIXIR") == 0){
                player->health = 100.0;
                printf("The health is increased.\n");

            } else if(strcmp(item_name, "CHARM") == 0){
                if (current_room->creature) {
                    current_room->creature->health = current_room->creature->health / 2;
                }
            } else if(strcmp(item_name, "KNIFE") == 0){
                player->strength += 20;
            } else if(strcmp(item_name, "BLOODSPEAR") == 0){
                player->health -= player->health * 0.1;
                if (current_room->creature) {
                    current_room->creature->health -= current_room->creature->health * 0.5;
                }
            } else if(strcmp(item_name, "SHIELD") == 0) {
                if (current_room->creature) {
                    current_room->creature->strength -= 20;
                }
            } else if(strcmp(item_name, "LIFESTEALER") == 0){
                player->health += 20.0;
                if (current_room->creature) {
                    current_room->creature->health -= 20.0;
                }
            }
            player->inventory[i] = NULL;
            player->inventory_size--;
            return item;
        }
    }
    printf("Item not found in inventory!\n");
    return NULL;
}
//Destroy the player and free memory
void destroy_player(Player* player) {
    if (!player) return;
    for (int i = 0; i < player->inventory_size; i++) {
        destroy_item(player->inventory[i]);
    }
    free(player->name);
    free(player);
}
