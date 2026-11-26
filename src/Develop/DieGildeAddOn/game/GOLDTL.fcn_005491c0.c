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




char* __cdecl he_StartHandlungSearch(int, int, int, ...);
void __cdecl he_FreeAction(char*);
void __cdecl fcn_004c5530(struct msg*);

void __cdecl he_ClearActivePlayerActions(void)
{
	struct msg m;
	char* p;

	p = he_StartHandlungSearch(1, 0, 0x73);
	if (p != 0) {
		he_FreeAction(p);
	}
	m.b4 = 0x73;
	m.f8 = *(int*) (gm_CityEntity + 4);
	m.fc = -1;
	m.b36 = 1;
	m.pos = gm_GameTime;
	fcn_004c5530(&m);
}
