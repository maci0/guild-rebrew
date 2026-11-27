#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char* g_7e2aa0;
#include "Develop/DieGildeAddOn/game/game_player.h"

typedef struct {
	unsigned char kind;
	char pad1[3];
	int a;
	int b;
	int c;
	int d;
	float f;
} Blk24;
// SIZE 0x18

char* __cdecl gm_LookupEntityRecordById(int);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short, int);
int __cdecl ai_StartGraveyardOwner(int, char*, int, Blk24*, Blk24*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl gm_ComputeCannonShot(char*, char*, int);
int __cdecl ai_FireCannonVolley(char*, char*);
void __cdecl d2_OpenBlutracheDialog(char*);
void __cdecl d2_RunBlutracheDialog(int);
void __cdecl d2_ShowBlutracheDialog(int);
void __cdecl d2_RunEhrerbietungDialog(int);
void __cdecl d2_RunKanoneUI(int);
int __cdecl d2_RunCardGameDialog(void);

/* ADDRESS: GOLDTL 0x005359c0 */
int __cdecl gm_DispatchDebugActionKeys(void)
{
	char* o;
	char* e;
	Blk24 b1;
	Blk24 b2;

	switch (*(unsigned char*) 0x14cf950) {
	case 0x1e:
		return d2_RunCardGameDialog();
	case 0x30:
		o = g_7e2aa0;
		if (o != 0) {
			d2_RunBlutracheDialog((int) o);
		}
		return;
	case 0x2e:
		o = g_7e2aa0;
		if (o != 0) {
			d2_ShowBlutracheDialog((int) o);
		}
		return;
	case 0x20:
		o = g_7e2aa0;
		if (o != 0) {
			d2_RunEhrerbietungDialog((int) o);
		}
		return;
	case 0x12:
		o = g_7e2aa0;
		if (o != 0) {
			d2_OpenBlutracheDialog(o);
		}
		return;
	case 0x25:
		e = gm_LookupEntityRecordById(*(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970] + 0x60));
		if (e != 0) {
			gm_ApplyEntityHealthDelta(*(unsigned short*) e, -1000);
		} else {
			e = gm_LookupEntityRecordById(*(int*) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970] + 0x60));
			if (e != 0) {
				gm_ApplyEntityHealthDelta(*(unsigned short*) e, -1000);
			}
		}
		return;
	case 0x14:
		if (g_7e2aa0 == 0) {
			return;
		}
		ai_StartGraveyardOwner(0, (char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970], 0, &b2, &b1);
		return;
	case 0x16:
		o = g_7e2aa0;
		if (o == 0) {
			return;
		}
		e = gm_StartFilteredEntitySearch(1, 5, 0xf);
		if (e == 0) {
			return;
		}
		if (gm_ComputeCannonShot((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970], o, (int) e) == 0) {
			return;
		}
		ai_FireCannonVolley((char*)&((ENTITY_RECORD*)g_7f4ca0)[g_774970], o);
		return;
	case 0x2f:
		o = g_7e2aa0;
		if (o != 0) {
			d2_RunKanoneUI((int) o);
		}
		break;
	}
	return;
}
