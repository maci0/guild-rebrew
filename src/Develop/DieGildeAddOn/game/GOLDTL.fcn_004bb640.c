#include <string.h>

#include "client_types.h"


// SIZE 0xe


extern pos14_7f4c00 gm_GameTime;

unsigned char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_00500d60(pos14_7f4c00*, void*);
int __cdecl fcn_004fe330(void*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

struct date_4bb640 {
	int a;
	int b;
	int c;
};
// SIZE 0xc


/* ADDRESS: GOLDTL 0x004bb640 */
int __cdecl fcn_004bb640(int* a1)
{
	pos14_7f4c00 st;
	struct date_4bb640 d;
	char buf[0x100];
	unsigned char* entity;

	entity = gm_LookupEntityRecordById(a1[0]);
	if (entity == 0)
		return 1;
	if (*(int*) (entity + 0x2c) == 0)
		return 0x400;
	st = (*(pos14_7f4c00*)&gm_GameTime);
	fcn_00500d60(&st, &d);
	io_FormatTextBuffer(buf, *(unsigned short*) (a1 + 1) + 0x12e7, fcn_004fe330(&d) + 0x4c);
	fcn_00545d40(*(int*) (entity + 4), *(int*) (entity + 4), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
