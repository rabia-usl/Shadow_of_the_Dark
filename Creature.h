#ifndef CREATURE_H
#define CREATURE_H

#include <stdlib.h>

typedef struct {
    char name[50];
    int health;
    int strength;
} Creature;

void initialize_creature(Creature* creature, const char* name, int health, int strength);
void destroy_creature(Creature* creature);
#endif