extern char* gm_CityEntity;

#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

// SIZE 0xf8
struct msg {
	int f0;
	char b4;
	char pad[3];
	int f8;
	int fc;
	char pad2[0x18];
	struct pos14 pos;
	char b36;
	char pad3[0x21];
	char b58;
	char pad4[3];
	char b5c;
	char pad5[0x9b];
};

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"









char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl he_StartHandlungSearch(int, int, int, ...);
char* __cdecl he_fn_Handlung(void);
void __cdecl cm_SendCopyEntityData(struct msg*);

void __cdecl fcn_00547460(void)
{
	struct msg m;
	char* e;
	char* p;

	e = gm_StartFilteredEntitySearch(1, 5, 0xf);
	if (e != 0 && *(unsigned short*) (e + 0x27) != 0xffff) {
		for (p = he_StartHandlungSearch(1, 0, 0x22); p != 0; p = he_fn_Handlung()) {
			if (*(int*) (p + 0x10) == *(int*) (e + 1)) {
				return;
			}
		}
		m.b4 = 0x22;
		m.f8 = ((ENTITY_RECORD_VIEW *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[*(unsigned short*) (e + 0x27)])->entity_id;
		m.fc = *(int*) (e + 1);
		m.b36 = 2;
		m.b58 = 1;
		cm_SendCopyEntityData(&m);
	}
}
