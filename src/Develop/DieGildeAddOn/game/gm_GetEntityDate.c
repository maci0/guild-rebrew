#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/client_actions.h"

extern pos14_7f4c00 gm_GameTime;

struct blk14_509050 {
	int a;
	int b;
	int c;
	short d;
};

#pragma pack(push, 1)
typedef struct {
	unsigned char day;
	unsigned char month;
	short year;
	int time;
	short rest;
} PACKED_TIME509050;
#pragma pack(pop)

void __cdecl gm_PackGameTime(int* src, char* dst);

/* ADDRESS: GOLD 0x506000 */
/* ADDRESS: GOLDTL 0x00509050 */
/* ADDRESS: GOLDDE 0x004f41d0 */
void __cdecl gm_GetEntityDate(char* entity, PACKED_TIME509050* out)
{
	struct blk14_509050 time;
	PACKED_TIME509050 packed;
	unsigned int seed;
	int year;

	time.b = gm_GameTimeHour;
	time.c = gm_GameTimeSliceDword;
	time.d = gm_GameTimeTailWord;
	year = *(int*) &gm_GameTime;
	if (entity[8] == 0) {
		year = *(short*) (entity + 0x28);
	}
	year -= *(unsigned short*) (entity + 0xa);
	time.a = year;
	gm_PackGameTime(&time.a, (char*) &packed);
	seed = *(unsigned int*) (entity + 0x30) ^ packed.year;
	packed.month = (unsigned char) (((seed >> 3) % 13 + year % 11) % 12 + 1);
	packed.day = (unsigned char) ((seed >> 5) % 28 + 1);
	*out = packed;
}
