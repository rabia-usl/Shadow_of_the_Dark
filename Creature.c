#include "Creature.h"
#include <string.h>

// Initialize the creature with a name, health, and strength
void initialize_creature(Creature* creature, const char* name, int health, int strength) {
    if (!creature) return;
    strncpy(creature->name, name, 50);
    creature->health = health;
    creature->strength = strength;
}
// Destroy the creature
void destroy_creature(Creature* creature) {
    if (!creature) return;
    free(creature->name);
    free(creature);
}
