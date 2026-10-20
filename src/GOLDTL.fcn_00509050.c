#include "client_types.h"
#include "client_actions.h"

extern pos14_7f4c00 g_7f4c00;

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

void __cdecl fcn_00500d60(int* src, char* dst);

/* ADDRESS: GOLDTL 0x00509050 */
void __cdecl fcn_00509050(char* entity, PACKED_TIME509050* out)
{
	struct blk14_509050 time;
	PACKED_TIME509050 packed;
	unsigned int seed;
	int year;

	time.b = g_7f4c04;
	time.c = g_7f4c08;
	time.d = g_7f4c0c;
	year = *(int*) &g_7f4c00;
	if (entity[8] == 0) {
		year = *(short*) (entity + 0x28);
	}
	year -= *(unsigned short*) (entity + 0xa);
	time.a = year;
	fcn_00500d60(&time.a, (char*) &packed);
	seed = *(unsigned int*) (entity + 0x30) ^ packed.year;
	packed.month = (unsigned char) (((seed >> 3) % 13 + year % 11) % 12 + 1);
	packed.day = (unsigned char) ((seed >> 5) % 28 + 1);
	*out = packed;
}
