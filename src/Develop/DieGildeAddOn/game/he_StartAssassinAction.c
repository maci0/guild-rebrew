


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

extern char g_6a7e18[];

char* __cdecl he_StartHandlungSearch(int, ...);
char* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl he_PostEntityMessage(int, int, char*, unsigned char, int, char*);
int __cdecl cm_SendSetHE(int, char*);
void __cdecl he_FreeAction(char*);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
int __cdecl cm_SendAllocCharacter(int, int, int, int, int, int, char*);

void __cdecl he_StartAssassinAction(char* u)
{
	char text[0x400];
	char* o;

	if (u[0x78] & 4) {
		return;
	}
	for (o = he_StartHandlungSearch(1, 0, 0x99); o != 0; o = he_fn_Handlung()) {
		if (o != u && *(unsigned short*) (o + 8) == *(unsigned short*) (u + 8)) {
			io_FormatTextBuffer(text, 0x3ff7, *(unsigned short*) (u + 8));
			he_PostEntityMessage(((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[*(unsigned short*) (u + 8)])->entity_id, -1, text, 0, 0x5fa, 0);
			*(int*) (u + 0x84) = cm_SendSetHE(-1, u);
			he_FreeAction(u);
			return;
		}
	}
	*(pos14_7f4c00*) (u + 0x44) = gm_GameTime;
	*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (u + 0x52), 0, 1, 0);
	*(int*) (u + 0xcc) = cm_SendAllocCharacter(0xd, *(int*) (u + 0xb0), -1, 0x2d, 0, 0, g_6a7e18);
	*(int*) (u + 0x84) = cm_SendSetHE(0, u);
}
