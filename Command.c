#include "Command.h"
#include "Item.h"
#include <stdlib.h>
#include <string.h>

// Parse the user input and execute the corresponding command
void parse_command(const char* input, Player* player, Room** current_room) {
    if (!input || !player || !current_room) return;//if input, player or current_room is null return
    char command[50], arg[50];
    sscanf(input, "%s %s", command, arg);//scan the input and store the first word in command and the second word in arg

    if (strcmp(command, "attack") == 0) {
        attack(player, *current_room);
    } else if (strcmp(command, "move") == 0) {
        move(player, current_room, arg);
    } else if (strcmp(command, "pickup") == 0) {
        pickup(player, *current_room, arg);
    } else if (strcmp(command, "drop") == 0) {
        drop(player,*current_room, arg);
    } else if (strcmp(command, "use") == 0) {
        use(player, arg);
    } else if (strcmp(command, "inventory") == 0) {
        inventory(player);
    } else if (strcmp(command, "look") == 0) {
        look(*current_room);
    } else if (strcmp(command, "save") == 0) {
        save_game(player, *current_room, arg);
    } else if (strcmp(command, "load") == 0) {
        load_game(player, current_room, arg);
    } else if (strcmp(command, "list") == 0) {
        list_saved_games();
    } else if (strcmp(command, "exit") == 0) {
        exit_game();
    } else {
        printf("Unknown command: %s\n", command);
    }
}

void attack(Player* player, Room* current_room) {
    if (!player || !current_room || !current_room->creature) {//if player, current_room or current_room->creature is null return
        printf("Nothing to attack here!\n");
        return;
    }
    Creature* creature = current_room->creature;
    printf("You attack %s!\n", creature->name);
    creature->health -= player->strength;
    printf("%s's health: %d\n", creature->name, creature->health);
    if (creature->health <= 0) {
        printf("You defeated %s!\n", creature->name);
        current_room->creature = NULL;
        free(creature);
    } else {
        printf("%s attacks back!\n", creature->name);
        player->health -= creature->strength;
        printf("Your health: %d\n", player->health);
        if (player->health <= 0) {//if player health is less than or equal to 0
            printf("You have been defeated!\n");
            exit_game();
        }
    }
}

void move(Player *player, Room **currentRoom, const char *direction) {
    Room *nextRoom = NULL;

    // Determine the next room based on direction
    if (strcmp(direction, "up") == 0) {
        nextRoom = (*currentRoom)->up;
    } else if (strcmp(direction, "down") == 0) {
        nextRoom = (*currentRoom)->down;
    } else if (strcmp(direction, "left") == 0) {
        nextRoom = (*currentRoom)->left;
    } else if (strcmp(direction, "right") == 0) {
        nextRoom = (*currentRoom)->right;
    }

    if ((*currentRoom)->creature != NULL && (*currentRoom)->creature->health > 0) {
        // If there's a creature in the current room, block the move
        printf("A creature blocks your way! Defeat it before moving.\n");
    } else if (nextRoom) {
        // Move to the next room
        printf("You move %s.\n", direction);
        *currentRoom = nextRoom;  // Update the pointer to point to the new room
        printf("Current Room: ");
        describe_room(*currentRoom);
    } else {
        // No valid room in the given direction
        printf("You can't go that way.\n");
    }
}

// Pick up an item from the room
void pickup(Player* player, Room* current_room, const char* item_name) {
    if (!player || !current_room || !item_name) return;
    for (int i = 0; i < current_room->item_count; i++) {
        if (current_room->items[i] && strcmp(current_room->items[i]->name, item_name) == 0) {
            if (add_item_to_inventory(player, current_room->items[i])) {
                printf("Picked up %s.\n", item_name);
                current_room->items[i] = NULL;
                return;
            }
        }
    }
    printf("Item not found in the room!\n");
}
// Drop an item from the player's inventory
void drop(Player* player,Room *current_room, const char* item_name) {
    if (!player || !item_name) return;
    if (drop_item_from_inventory(player, item_name)) {
        printf("Dropped %s.\n", item_name);
        add_item_to_room(current_room, create_item(item_name, "An item in the room"));
    }
}
// Use an item from the player's inventory
void use(Player* player, const char* item_name) {
    if (!player || !item_name) return;
    Item* item = use_item_from_inventory(player, item_name);
    if (item) {
        printf("Used %s.\n", item->name);
        free(item);
    }
}
// Display the player's inventory
void inventory(Player* player) {
    if (!player) return;
    display_inventory(player);
}
// Describe the current room
void look(Room* current_room) {
    if (!current_room) return;
    describe_room(current_room);
}
// Save the game state to a file
void save_game(const Player* player, const Room* current_room, const char* filepath) {
    if (!player || !current_room || !filepath) return;
    FILE* file = fopen(filepath, "w");
    if (!file) {
        printf("Failed to save game!\n");
        return;
    }
    fprintf(file, "%s\n%d\n%d\n", player->name, player->health, player->strength);
    fprintf(file, "%s\n", current_room->description);
    fclose(file);
    printf("Game saved to %s.\n", filepath);
}
// Load the game state from a file
void load_game(Player* player, Room** current_room, const char* filepath) {
    if (!player || !current_room || !filepath) return;
    FILE* file = fopen(filepath, "r");
    if (!file) {
        printf("Failed to load game!\n");
        return;
    }
    if(!player->name) return;
    fscanf(file, "%s\n%d\n%d\n", player->name, &player->health, &player->strength);
    char room_description[256];
    fgets(room_description, sizeof(room_description), file);
    initialize_room(*current_room, room_description);
    fclose(file);
    printf("Game loaded from %s.\n", filepath);
    if(!player->name || !(*current_room)->description || !(*current_room)->creature) return;
    printf("Player: %s\nHealth: %d\nStrength: %d\n", player->name, player->health, player->strength);
    printf("Current Room: %s\n", (*current_room)->description);
    printf("creature:  %f \n",  (*current_room)->creature->health);
}
// List saved games in the specified directory
void list_saved_games() {
    printf("Saved games:\n");
    // List saved games in the specified directory
    system("dir /b \"C:\\Users\\CASPER\\Desktop\\ShadowOfTheDark\\SavedGames\\*.txt\"");
}
// Exit the game
void exit_game() {
    printf("Exiting game. Goodbye!\n");
    exit(0);
}
