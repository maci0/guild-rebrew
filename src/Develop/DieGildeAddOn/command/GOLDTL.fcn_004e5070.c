

typedef struct {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	char f14;
	char pad15[0x347];
} rec35c;
// SIZE 0x35c

#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl cm_StageRawPacketPayload(int, void*);
int __cdecl cm_RequestSendCutInfo(int, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl fcn_00535960(void);

void __cdecl fcn_004e5070(unsigned char* s, int id)
{
	int i;
	rec35c copy;
	int h;

	for (i = 0; i < s[0x30]; i++) {
		if (((rec35c*)g_9b0e20)[i].f10 == id) {
			copy = ((rec35c*)g_9b0e20)[i];
			copy.f8 = 0;
			copy.f4 = 1;
			copy.f0 = 1;
			copy.fc = 1;
			copy.f14 = 0;
			cm_StageRawPacketPayload(0x35c, &copy);
			h = cm_RequestSendCutInfo(id, *(int*) s);
			while (cm_GetCommandStatus(h) == 0)
				fcn_00535960();
		}
	}
}
