#include <string.h>

#include "Develop/client_types.h"


// SIZE 0xe


extern pos14_7f4c00 gm_GameTime;

unsigned char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_PackGameTime(pos14_7f4c00*, void*);
int __cdecl gm_GetSeasonFromDate(void*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);

struct PACKED_DATE_MSG {
	int a;
	int b;
	int c;
};
// SIZE 0xc


/* ADDRESS: GOLDTL 0x004bb640 */
int __cdecl gm_HandlePostSpouseSeasonMsg(int* a1)
{
	pos14_7f4c00 st;
	struct PACKED_DATE_MSG d;
	char buf[0x100];
	unsigned char* entity;

	entity = gm_LookupEntityRecordById(a1[0]);
	if (entity == 0)
		return 1;
	if (*(int*) (entity + 0x2c) == 0)
		return 0x400;
	st = (*(pos14_7f4c00*)&gm_GameTime);
	gm_PackGameTime(&st, &d);
	io_FormatTextBuffer(buf, *(unsigned short*) (a1 + 1) + 0x12e7, gm_GetSeasonFromDate(&d) + 0x4c);
	he_PostEntityMessage(*(int*) (entity + 4), *(int*) (entity + 4), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
