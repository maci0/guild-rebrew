void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// SIZE 0x21c
typedef struct
{
	unsigned short id;
	unsigned char kind;
	char pad3;
	int h;
	unsigned char alive;
	char pad9;
	unsigned short age;
	char padc[4];
	float lo;
	char pad14[8];
	float hi;
	float span;
	int bonus;
	char pad28[0x21c - 0x28];
} fcn_004ff210_Ent;

extern char g_7f4ca0[];
#include "client_packet_builder.h"
#include "client_types.h"







// SIZE 0xe


#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;


int __cdecl fcn_004c4700(unsigned char type, unsigned char count, short id, char* data);
void __cdecl fcn_004c53a0(void);
void __cdecl fcn_004c5530(char* msg);
void __cdecl fcn_004c4670(int, int, int, int*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c5480(int a1, int a2, float a3);

/* ADDRESS: GOLDTL 0x004ff210 */
float __cdecl fcn_004ff210(unsigned short id, int delta)
{
	char dead;
	float res;
	char msg[0xf8];
	fcn_004ff210_Ent* e;

	e = &((fcn_004ff210_Ent*)g_7f4ca0)[id];
	if (e->id == 0xffff || e->kind == 10 || e->alive == 0)
		return -1.0f;
	if (e->kind != 0x14) {
		res = (e->age <= e->span ? (e->hi - e->lo) / e->span * e->age + e->lo : e->hi) + ((float) e->bonus + delta);
		res = (float)(res > 0.0 ? res : 0.0);
		if (res <= 0.0) {
			dead = 0;
			cm_BeginPacketFieldDelta((char*) e, e->h);
			fcn_004c4700(1, 1, (short) ((char*) e - g_aed32c + 8), &dead);
			fcn_004c53a0();
			memset(msg, 0, sizeof(msg));
			msg[4] = 0x72;
			*(int*) (msg + 8) = e->h;
			*(int*) (msg + 0xc) = -1;
			msg[0x36] = 2;
			*(pos14_7f4c00*) (msg + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
			*(int*) (msg + 0x58) = e->h;
			fcn_004c5530(msg);
			return 0.0f;
		}
		cm_BeginPacketFieldDelta((char*) e, e->h);
		fcn_004c4670(4, 1, 0x24, &delta);
		fcn_004c5360();
		return res;
	}
	{
		float d;

		d = (float) delta;
		res = e->hi;
		res += d;
		if (res <= 0.0) {
			dead = 0;
			cm_BeginPacketFieldDelta((char*) e, e->h);
			fcn_004c4700(1, 1, (short) ((char*) e - g_aed32c + 8), &dead);
			fcn_004c53a0();
			memset(msg, 0, sizeof(msg));
			msg[4] = 0x72;
			*(int*) (msg + 8) = e->h;
			*(int*) (msg + 0xc) = -1;
			msg[0x36] = 2;
			*(pos14_7f4c00*) (msg + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
			*(int*) (msg + 0x58) = e->h;
			fcn_004c5530(msg);
			return 0.0f;
		}
		fcn_004c5480(e->h, 0x1c, d);
		return res;
	}
}
