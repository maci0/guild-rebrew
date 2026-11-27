extern char* gm_CityEntity;

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	pos14_7f4c00 pos;
	char b36;
	char pad3[0x21];
	char b58;
	char pad4[3];
	char b5c;
	char pad5[0x9b];
};




#include <string.h>

char* __cdecl he_StartHandlungSearch(int, int, int, ...);
void __cdecl cm_SendCopyEntityData(struct msg*);

void __cdecl he_EnsureCityAction0x86And0xa2(void)
{
	struct msg m;

	if (he_StartHandlungSearch(1, 0, 0x86) == 0) {
		memset(&m, 0, sizeof(m));
		m.b4 = (char) 0x86;
		m.f8 = *(int*) (gm_CityEntity + 4);
		m.fc = -1;
		m.b36 = 2;
		m.pos = gm_GameTime;
		cm_SendCopyEntityData(&m);
	}
	if (he_StartHandlungSearch(1, 0, 0xa2) == 0) {
		memset(&m, 0, sizeof(m));
		m.b4 = (char) 0xa2;
		m.f8 = *(int*) (gm_CityEntity + 4);
		m.fc = -1;
		m.b36 = 2;
		m.pos = gm_GameTime;
		cm_SendCopyEntityData(&m);
	}
}
