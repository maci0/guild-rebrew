#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"











extern unsigned char g_773d75;


float __cdecl gm_RandomFloat01(void);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl fcn_005100f0(int, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);
void __cdecl fcn_00526120(char*, int);

/* ADDRESS: GOLDTL 0x004eb780 */
int __cdecl fcn_004eb780(char* e, int* msg)
{
	char* h;
	int cnt;
	char buf[0x400];
	float f;
	int amount;
	int i;

	if (msg[0] != 2) {
		return 0;
	}
	gm_ResolveEntityById((void**) (&h), 0, 0, msg[1]);
	if (h == 0) {
		return 0;
	}
	if (*(unsigned short*) (h + 0x27) == *(unsigned short*) e || *(unsigned short*) (h + 0x27) == 0xffff) {
		return 0;
	}
	f = gm_GetEntitySkill(e, 4);
	amount = (int) (((gm_RandomFloat01() + 1.0f) * f * 15.0f + 5.0) * 2.55f);
	cm_RequestTransferCurrencyNoKill(-1, *(int*) (e + 4), (*(char*)&g_773d75), msg[2]);
	for (i = 0, cnt = 0; i < 0x300; i++) {
		if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_index != 0xffff && (*(char**)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].ptr_16c) == h && *(unsigned short*) (h + 0x27) != i) {
			cm_RequestCopyEntityData(((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].entity_id, ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id, -amount, 1);
			cnt++;
		}
	}
	if (cnt != 0) {
		amount = (int) ((float) msg[2] / cnt) + 0x20;
		for (i = 0; i < 0x300; i++) {
			if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_index != 0xffff && (*(char**)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].ptr_16c) == h && *(unsigned short*) (h + 0x27) != i) {
				cm_RequestTransferCurrencyNoKill(((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id, -1, (*(char*)&g_773d75), amount);
			}
		}
	}
	fcn_005100f0(*(int*) (e + 4), -5);
	cm_RequestChangeBits(*(int*) (e + 4), 0x1c8, 4, 0x8000000, 0);
	if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].entity_type == 7 || ((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].entity_type == 6) {
		io_FormatTextBuffer(buf, 0x1663, h);
		he_MessageBoxQuickjump(((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].entity_id, -1, buf, 0, 0x5fb, *(int*) (h + 1), -1, 0, "");
	}
	io_FormatTextBuffer(buf, 0x1662, *(unsigned short*) (h + 0x27), h);
	for (i = 0; i < 0x300; i++) {
		if ((((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 7 || ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 6) && *(int*) (e + 4) != ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id
		    && ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id != ((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (h + 0x27)].entity_id) {
			fcn_00545d40(((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id, -1, buf, 0, 0x5fd, "");
		}
	}
	if (e[2] == 6) {
		io_FormatTextBuffer(buf, 0x1661, *(unsigned short*) (h + 0x27), h);
		fcn_00526120(buf, 0);
	}
	return 1;
}
