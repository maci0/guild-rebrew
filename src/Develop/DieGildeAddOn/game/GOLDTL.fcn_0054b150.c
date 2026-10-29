#include "client_types.h"
#include "client_actions.h"

#pragma pack(push, 1)
typedef struct {
	int x00;
	unsigned short x04;
	int x06;
	int x0a;
} SIM_CLOCK;
#pragma pack(pop)

extern pos14_7f4c00 g_7f4c00;

char* __cdecl fcn_00508e40(int a1);
int __cdecl fcn_004c5620(char a1, unsigned char* e);
void __cdecl fcn_00500bb0(SIM_CLOCK* clock, int arg2, int arg3, int arg4);
void __cdecl fcn_004c54c0(int a1, int a2, int a3, int a4);
int __cdecl fcn_0051af00(char* dst, int id, ...);
int __cdecl fcn_00545d40(int id, int arg, char* text1, unsigned char flags, int value, char* text2);
void __cdecl fcn_004f4f60(int a, int b, int c, int d, int e);

/* ADDRESS: GOLDTL 0x0054b150 */
void __cdecl fcn_0054b150(char* entity)
{
	char buf[0x200];
	char* v2;
	char* v3;
	char* p;
	int v4;

	v2 = fcn_00508e40(*(int*) (entity + 0xac));
	v3 = fcn_00508e40(*(int*) (entity + 0xb0));
	*(int*) (entity + 0x84) = -1;
	if ((entity[0x78] & 2) == 0) {
		return;
	}
	if (v2 == 0 || v3 == 0) {
		*(pos14_7f4c00*) (entity + 0x52) = g_7f4c00;
		fcn_004c5620(-1, (unsigned char*) entity);
	}
	*(pos14_7f4c00*) (entity + 0x52) = g_7f4c00;
	fcn_00500bb0((SIM_CLOCK*) (entity + 0x52), 0x30, 0, 0);
	fcn_004c5620(0, (unsigned char*) entity);
	fcn_004c54c0(*(int*) (v3 + 4), *(int*) (v2 + 4), -0x14, 1);
	if (v2[2] == 6 || v2[2] == 7) {
		fcn_0051af00(buf, 0x175a, *(unsigned short*) v3, *(unsigned short*) v3);
		fcn_00545d40(*(int*) (v2 + 4), -1, buf, 0, 0x5fb, (char*) 0x6b5c60);
	}
	v4 = -1;
	p = *(char**) (v3 + 0x170);
	if (p != 0) {
		v4 = *(int*) (p + 1);
	}
	else {
		p = *(char**) (v2 + 0x170);
		if (p != 0) {
			v4 = *(int*) (p + 1);
		}
	}
	fcn_004f4f60(0x13, 1, *(int*) (entity + 0xb0), *(int*) (entity + 0xac), v4);
}
