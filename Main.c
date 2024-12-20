#include "Item.h"
#include "Player.h"
#include "Room.h"
#include "Creature.h"
#include "Command.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main() {
    srand(time(NULL));
    Player *player = malloc(sizeof(Player));
    initialize_player(player, "Player");

    // Create rooms
    Room *room1 = malloc(sizeof(Room)), *room2 = malloc(sizeof(Room)), *room3 = malloc(sizeof(Room)), *room4 = malloc(sizeof(Room)), *room5 = malloc(sizeof(Room));
    initialize_room(room1, "Mystic Entrance : dark and dusty room, the door is broken u can easily come in!");
    initialize_room(room2, "Dark Basement : Dark , frowsty room.You should hurry to exit the room!");
    initialize_room(room3, "Collapsing Hall : cracked mirrors line the walls,reflecting a world devoid of light.");
    initialize_room(room4, "Ruined Library : a ruined library with ruined shelves and old books on the floor");
    initialize_room(room5, "Garden Exit : there is a huge locked door, if you succeed you win the game!");

    // Set current room
    
    Room *current_room = room1;
    Room *start_room = room1;
    Room *end_room = room5;
    

    //Add creatures to rooms
    Creature *c1 = malloc(sizeof(Creature)), *c2 = malloc(sizeof(Creature)), *c3 = malloc(sizeof(Creature)), *c4 = malloc(sizeof(Creature)), *c5 = malloc(sizeof(Creature));
    initialize_creature(c1, "Goblin", 100, 5);
    initialize_creature(c2, "Shadow Snake", 100, 5);
    initialize_creature(c3,"Fanglord", 100, 15);
    initialize_creature(c4, "Lost Soul", 170, 15);
    initialize_creature(c5, "Warwick", 200, 10);

    add_creature(room1, c1);
    add_creature(room2, c2);
    add_creature(room3, c3);
    add_creature(room4, c4);
    add_creature(room5, c5);
    
    // Create items
    Item *item1 , *item2, *item3, *item4, *item5, *item6, *item7, *item8;
    item1 = create_item( "LIFEELIXIR","This item fulls your health rate");
    item2 = create_item ( "CHARM", "Special charm!The beast's health is halved.");
    item3 = create_item ( "KNIFE", "Increases damage rate by 10 percent.");
    item4 = create_item ( "BLOODSPEAR", "It consumes some health with each use, but deals high damage.");
    item5 = create_item ( "SHIELD", "Reduces damage taken by 10 percent");
    item6 = create_item ( "LIFESTEALER", "It is used for steal creature's health.Increases your health by 20 point while decreases creature's health by same rate.");
    item7 = create_item ( "STRENGTHGLOVES", "Increases damage rate by 20 percent.");
    item8 = create_item ( "SHURIKEN", "Increases damage by 10 percent.");

    // Add items to rooms
    Item *items1[1] = {item3};
    Item *items2[1] = {item5};
    Item *items3[2] = {item8, item2};
    Item *items4[3] = {item1, item4, item7};
    Item *items5[1] = {item6};

    create_items(room1, items1, 1);
    create_items(room2, items2, 1);
    create_items(room3, items3, 2);
    create_items(room4, items4, 3);
    create_items(room5, items5, 1);

    // Connect rooms
    connect_rooms(room1, room2 , "down");
    connect_rooms(room2, room3, "right");
    connect_rooms(room3, room4, "down");
    connect_rooms(room4, room5, "left");

    // Display starting text
    FILE *file;  
    char line[256]; 
    file = fopen("C:\\Users\\CASPER\\Desktop\\ShadowOfTheDark\\Starting\\Starting.txt", "r");
    if (file == NULL) {
        printf("The file cannot open.\n");
        return 1;  
    }
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);  
    }
    fclose(file);

    printf("\nNEW GAME(N) \nLOAD GAME(L)\n");
    char choose;
    scanf(" %c", &choose);
    while (getchar() != '\n');
    if(choose == 'N' || choose == 'n'){

    // Display room information
    char input[100];

    printf("Welcome to the Shadow of the Dark!\n");
    printf("Navigate through the rooms, defeat creatures, and reach the end room to win.\n");
    printf("\nCurrent Room: %s\n",(current_room)->description);

    printf("Items in the room:\n");
    for(int i = 0; i < (current_room)->item_count; i++) {
        display_item((current_room)->items[i]);
    }

    printf("Creature in the room:\n");
    printf("%s\n Health: %d Damage: %d \n", (current_room)->creature->name, (current_room)->creature->health,(current_room)->creature->strength);
        

    // Game loop
    while (player->health > 0) {
        

        printf("Enter command: ");
        fgets(input, sizeof(input), stdin);

        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        parse_command(input, player, &current_room);

        // Check for win condition
        if (current_room == end_room && (current_room->creature == NULL || current_room->creature->health <= 0)) {
            printf("\nCongratulations! You have reached the end room and won the game!\n");
            break;
        }

        // Check for player death
        if (player->health <= 0) {
            printf("\nYou have been defeated. Game Over.\n");
            break;
        }
    }

    }
    else if(choose == 'L' || choose == 'l'){
        printf("Choose a saved game to load:\n");
        list_saved_games();
        char filepath[100];
        printf("Enter the file path: ");
        fgets(filepath, sizeof(filepath), stdin);
        filepath[strcspn(filepath, "\n")] = 0;
        load_game(player, &current_room, filepath);
        while (player->health > 0) {
        
        char input[100];
        printf("Enter command: ");
        fgets(input, sizeof(input), stdin);

        // Remove newline character
        input[strcspn(input, "\n")] = 0;

        parse_command(input, player, &current_room);

        // Check for win condition
        if (current_room == end_room && current_room->creature != NULL && current_room->creature->health <= 0) {
            printf("\nCongratulations! You have reached the end room and won the game!\n");
            break;
        }

        // Check for player death
        if (player->health <= 0) {
            printf("\nYou have been defeated. Game Over.\n");
            break;
        }
    }
    }
    // Free memory
    destroy_player(player);
    destroy_room(room1);
    destroy_room(room2);
    destroy_room(room3);
    destroy_room(room4);
    destroy_room(room5);
    destroy_room(current_room);
    destroy_room(start_room);
    destroy_room(end_room);
    destroy_creature(c1);
    destroy_creature(c2);
    destroy_creature(c3);
    destroy_creature(c4);
    destroy_creature(c5);
    destroy_item(item1);
    destroy_item(item2);
    destroy_item(item3);
    destroy_item(item4);
    destroy_item(item5);
    destroy_item(item6);
    destroy_item(item7);
    destroy_item(item8);
    return 0;
}
