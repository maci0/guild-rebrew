


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







// SIZE 0x2f4
struct rec {
	unsigned short v;
	char pad2[0x2f2];
};

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl fcn_00502cd0(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, int);
void __cdecl gm_TryRecordCrime(int, int, int, int, int);

void __cdecl he_AllocKredit(char* e)
{
	char* o;
	char buf[0x200];
	char* q;
	ENTITY_RECORD* h;
	char* r;
	int v;

	*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
	*(pos14_7f4c00*) (e + 0xc4) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (e + 0xc4), *(int*) (e + 0xb8) * 24, 0, 0);
	*(short*) (e + 0xc8) = 8;
	*(int*) (e + 0xca) = 0;
	*(int*) (e + 0xce) = 0;
	*(int*) (e + 0xbc) = *(int*) (e + 0xb8);
	q = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0xac));
	if (q == 0 || (e[0x78] & 2) == 0) {
		return;
	}
	h = ((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[*(unsigned short*) (q + 0x27)]);
	o = gm_LookupEntityRecordById(*(int*) (e + 0xb0));
	if (h->entity_state != 6 && h->entity_state != 7) {
		return;
	}
	v = 0;
	r = fcn_00502cd0(*(int*) (q + 0x5d), 1, 0, ((struct rec*)g_8680b4)[g_773d75].v);
	if (r != 0) {
		v = *(int*) (r + 0xe);
	}
	io_FormatTextBuffer(buf, 0x18d7, *(unsigned short*) o, q, *(int*) (e + 0xb4), *(int*) (e + 0xc0), *(int*) (e + 0xb8), 0x5d, v);
	he_MessageBoxQuickjump(h->entity_id, -1, buf, 0, 0x5ec, *(int*) (q + 1), -1, 0, 0);
	gm_TryRecordCrime(0xe, *(int*) (e + 0xc0), h->entity_id, *(int*) (e + 0xb0), *(int*) (q + 1));
}
