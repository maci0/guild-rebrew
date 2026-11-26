


#include <string.h>

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;
extern float g_66414c;
extern char g_67eb38[];
extern char g_67eb2c[];
extern char* gm_CityEntity;
extern float g_100a0a0;
extern float g_100a0c0[];

char* __cdecl gm_FindPublicTreasury(int k);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
int __cdecl fcn_0050d170(int k);
void __cdecl fcn_004c5150(int a, int b, char c, int n);
void __cdecl fcn_004c5530(char* msg);
int __cdecl amt_ExecGebaeudeBauen(char* a1, char* a2, char* a3);

int __cdecl ai_RunBaumeister(char* entity, char* a2, char* a3)
{
	char msg[0xf8];
	char* b;

	b = gm_FindPublicTreasury(1);
	if (b == 0 || (unsigned char) entity[0x166] != 0xa) {
		goto out0;
	}
	if (*a3 == 4) {
		memset(msg, 0, sizeof(msg));
		msg[4] = 0x1e;
		*(int*) (msg + 8) = *(int*) (entity + 4);
		*(int*) (msg + 0xc) = *(int*) (a3 + 4);
		msg[0x36] = 1;
		*(int*) (msg + 0x28) = (*(int*)&gm_GameTime);
		*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
		*(int*) (msg + 0x30) = g_7f4c08;
		*(short*) (msg + 0x34) = g_7f4c0c;
		*(int*) (msg + 0x58) = *(int*) (a3 + 4);
		fcn_004c4eb0(g_67eb38);
		fcn_004c5150(-1, *(int*) (b + 2), (*(char*)&g_773d75), (int) (fcn_0050d170(*(int*) (a2 + 4)) * 0.3f));
		fcn_004c5530(msg);
		fcn_004c4ef0(g_67eb38);
		if (*(int*) (a2 + 0x10) > 0 && *(int*) (a2 + 0x10) < 4) {
			g_100a0c0[*(int*) (a2 + 0x10) * 2] = g_100a0a0 + g_100a0a0;
		}
		return 0x2f;
	} else {
		fcn_004c4eb0(g_67eb2c);
		if (amt_ExecGebaeudeBauen(gm_CityEntity, a2, a3)) {
			fcn_004c5150(-1, *(int*) (b + 2), (*(char*)&g_773d75), fcn_0050d170(*(int*) (a2 + 4)));
			fcn_004c4ef0(g_67eb2c);
			if (*(int*) (a2 + 0x10) > 0 && *(int*) (a2 + 0x10) < 4) {
				g_100a0c0[*(int*) (a2 + 0x10) * 2] = g_100a0a0 + g_100a0a0;
			}
			return 0x2f;
		} else {
			fcn_004c4ef0(g_67eb2c);
			return 0;
		}
	}
out0:
	return 0;
}
