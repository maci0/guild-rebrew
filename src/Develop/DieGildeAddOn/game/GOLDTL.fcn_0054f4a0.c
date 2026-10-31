#include "client_types.h"

typedef struct {
	int v[6];
} Row_54f4a0;

extern pos14_7f4c00 g_7f4c00;
extern float g_662924;

void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);
void __cdecl fcn_004c5420(int, int, int, int, int);
int __cdecl srv_GetEntityOfficeSlot(unsigned char*, void*, void*);
float __cdecl gm_GetEntitySkill(char*, int);
int __cdecl gm_RandomMod(int);
void __cdecl fcn_004ec2d0(unsigned char*, int, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_004c5620(int, char*);

/* ADDRESS: GOLDTL 0x0054f4a0 */
void __cdecl fcn_0054f4a0(char* a0, char* a1, unsigned char* a2)
{
	Row_54f4a0 role;
	Row_54f4a0 slot;
	char buf[0x400];
	int ret;
	int delay;
	float d;

	ret = 0;
	if (a1[2] == 6 || a1[2] == 7) {
		io_FormatTextBuffer(buf, 0x1d81, *(unsigned short*) a2, *(unsigned short*) a2, (a2[9] != 0) + 0x1d68);
		fcn_00545d40(*(int*) (a1 + 4), *(int*) (a1 + 4), buf, 0, 0x5fb, 0);
		fcn_004c5420(*(int*) (a1 + 4), 0x1c8, 4, 0, 0x400);
		fcn_004c5420(*(int*) (a2 + 4), 0x1c8, 4, 0, 0x400);
	}
	if (a2[0x166] != 0) {
		if (srv_GetEntityOfficeSlot(a2, &role, &slot) != 0) {
			ret = role.v[1];
		}
		else {
			ret = (unsigned short) gm_RandomMod(3) + 1;
		}
	}
	d = gm_GetEntitySkill(a1, 4) * g_662924;
	delay = -9 - (int) d;
	delay -= gm_RandomMod(8) & 0xffff;
	fcn_004ec2d0(a2, ret, delay);
	fcn_004c54c0(*(int*) (a1 + 4), *(int*) (a2 + 4), -0x14, 1);
	*(pos14_7f4c00*) (a0 + 0x52) = g_7f4c00;
	fcn_004c5620(-1, a0);
}
