#ifndef COMMAND_H
#define COMMAND_H

#include "Player.h"
#include "Room.h"
#include <stdio.h>

void parse_command(const char* input, Player* player, Room** current_room);
void attack(Player* player, Room* current_room);
void move(Player *player, Room **current_room, const char* direction);
void pickup(Player* player, Room* current_room, const char* item_name);
void drop(Player* player,Room* current_room, const char* item_name);
void use(Player* player,Room* current_room, const char* item_name);
void inventory(Player* player);
void look(Room* current_room);
void stats(Player *player);
void save_game(const Player* player, const Room* current_room, const char* filepath);
void load_game(Player* player, Room** current_room, const char* filepath);
void list_saved_games();
void exit_game();

#endif