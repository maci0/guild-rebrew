#ifndef GAME_TIMESTAMP_H
#define GAME_TIMESTAMP_H

#include "Develop/client_types.h"

#pragma pack(push, 2)
typedef struct {
	int unit_0;
	unsigned short hour;
	int minute;
	int second;
} GAME_TIMESTAMP;
#pragma pack(pop)
/* SIZE 0x0e */

extern pos14_7f4c00 gm_GameTime;

#endif
