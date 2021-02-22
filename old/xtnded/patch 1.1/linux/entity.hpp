#ifndef ENTITY_H
#define ENTITY_H

#include "game/shared.hpp"

extern int gentities;

#define MAX_ENTITY_SIZE 1024
#define PLAYERSTATE_SIZE 0x22cc
#define GENTITY_SIZE 788

typedef enum {
	SS_PLAYING,
	SS_DEAD,
	SS_SPECTATOR,
	SS_INTERMISSION
} sessionstate_types;

typedef enum {
	EOFF_S_SVFLAGS = 244,
	EOFF_S_GROUNDENTITYNUM = 124,
	
	EOFF_ETYPE = 4,
	EOFF_PHYSICSOBJECT = 353,
    EOFF_PLAYERSTATE = 344,
    EOFF_CONTENTS = 280,
	EOFF_TAKEDAMAGE = 369,
    EOFF_NEXTTHINK = 508,
	EOFF_FLAGS = 380,
    EOFF_THINK = 512,
    EOFF_USE = 528,
    EOFF_PAIN = 532,
    EOFF_DIE = 536,
    EOFF_HEALTH = 560,
    EOFF_CLASSNAME = 374, //it's a string index of scr_
    EOFF_ORIGIN = 308,
    EOFF_ANGLES = 320,
	EOFF_CONTROLLER = 544
} ENTITY_OFFSET;

typedef enum {
	POFF_CLIENTNUM = 172,
	POFF_EFLAGS = 128,
	POFF_PM_TYPE = 4,
    POFF_VELOCITY = 0x20,
    POFF_ANGLES = 0xC0,
	POFF_SESSIONSTATE = 8400
} PLAYER_OFFSET;

struct ENTITY {
    int index;
    bool ps;
    int base;
    int ptr;
    int nextthink;
    int think;
    int pain;
    int die;
    int use;
    int touch;
    int getPlayerState();
    void set(int, void*, unsigned int);
    void get(int, void*, unsigned int);
    void switchState();
    void toPlayerState();
    void toEntityState();
    bool isPlayer();
    bool isEntity();
};

#endif // ENTITY_H
