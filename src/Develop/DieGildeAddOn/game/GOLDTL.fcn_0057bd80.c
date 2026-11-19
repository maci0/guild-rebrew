


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"




#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;


int __cdecl fcn_004c4450(int);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_0057c630(ENTITY_RECORD*, int);
void __cdecl fcn_0057bed0(ENTITY_RECORD*, char*, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
unsigned short __cdecl gm_RandomMod(int);

void __cdecl fcn_0057bd80(char* u)
{
	char* h2;
	ENTITY_RECORD* h;

	if (*(int*) (u + 0x70) != -1 && *(int*) (u + 0x70) != -2) {
		if (u[0x78] & 4) {
			return;
		}
		if (*(int*) (u + 0x84) != -1 && fcn_004c4450(*(int*) (u + 0x84)) == 0) {
			return;
		}
		*(int*) (u + 0x84) = -1;
		*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
		h2 = gm_LookupEntityRecordById(*(int*) (u + 0xb0));
		if (h2 == 0 || ((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (u + 8)].entity_index == 0xffff) {
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
			return;
		}
		h = &((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (u + 8)];
		switch (*(int*) (u + 0x70)) {
		case 0:
			fcn_0057bed0(h, h2, *(int*) (u + 0xac));
			fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 0x18, 0, 0);
			*(short*) (u + 0x56) = 6;
			*(int*) (u + 0x58) = gm_RandomMod(4) * 15 + 5;
			*(int*) (u + 0x84) = fcn_004c5620(1, u);
			break;
		case 1:
			fcn_0057c630(h, *(int*) (u + 0xac));
			*(int*) (u + 0x84) = fcn_004c5620(-1, u);
			break;
		}
	} else {
		fcn_00546190(u);
	}
}
