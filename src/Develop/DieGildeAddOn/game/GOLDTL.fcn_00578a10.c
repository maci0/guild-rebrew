#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern double g_6629c8;
#include "Develop/DieGildeAddOn/game/entity_record.h"







extern char g_7f4ca0[];
#include "game_data.h"
typedef struct CrimeProto { char pad0[0x247]; unsigned char field247; char tail[5]; } CrimeProto;
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_00529160(int, int, unsigned int, int);
int __cdecl he_FreeAction(char*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_004c5da0(int, unsigned int, int, int, int, int);
int __cdecl gm_AddTime(int*, int, int, int);
float __cdecl fcn_00507e70(char*, char*, int);
double __cdecl gm_RandomFloat01(void);
int __cdecl gm_RandomMod(unsigned short);
void __cdecl fcn_005782f0(char*, int, int);
void __cdecl fcn_005b2f60(char*);
void __cdecl fcn_005b2fb0(char*);
float __cdecl gm_GetEntitySkill(char*, int);
void __cdecl fcn_005b3000(char*, char*, char*, int);
void __cdecl he_ShowFriedhofMessage(char*, char*, char*);

/* ADDRESS: GOLDTL 0x00578a10 */
int __cdecl he_RunHauchDesVerfalls(char* event)
{
	char* p;
	char* q;
	char* r;
	char* o;
	char* m;
	char* n;
	char* tbl;
	unsigned char c;
	float t;
	int s;

	p = gm_LookupEntityRecordById(*(int*) (event + 0xb4));
	s = -1;
	if (*(int*) (event + 0x70) == s || *(int*) (event + 0x70) == -2) {
		goto tail1;
	}
	if (p == 0) {
		goto tail2;
	}
	switch (*(int*) (event + 0x70)) {
	case 0:
		fcn_00529160(0, 0, *(unsigned short*) p, (int) event);
		*(int*) (event + 0x84) = s;
		return *(int*) (event + 0x70) = *(int*) (event + 0x70) + 1;
	case 1:
		q = gm_StartFilteredEntitySearch(1, 1, *(int*) (event + 0xac));
		if (q == 0) {
			*(int*) (event + 0x70) = s;
			return;
		}
		fcn_004c5da0(*(int*) (event + 0xb4), *(unsigned int*) (q + 1), s, 0, 1, 0x6a7ef4);
		return *(int*) (event + 0x70) = *(int*) (event + 0x70) + 1;
	case 2:
		gm_StartFilteredEntitySearch(1, 1, *(int*) (event + 0xac));
		p = gm_LookupEntityRecordById(*(int*) (event + 0xb4));
		if (p == 0) {
			*(int*) (event + 0x70) = s;
			return;
		}
		r = *(char**) (p + 0x184);
		if (*(int*) (r + 0x128) != 0) {
			*(pos14_7f4c00*) (event + 0x52) = *(pos14_7f4c00*) &gm_GameTime;
			return gm_AddTime((int*) (event + 0x52), 0, 4, 0);
		}
		*(pos14_7f4c00*) (event + 0x52) = *(pos14_7f4c00*) &gm_GameTime;
		gm_AddTime((int*) (event + 0x52), 1, 0, 0);
		n = gm_LookupEntityRecordById(*(int*) (event + 0xb0));
		m = gm_LookupEntityRecordById(*(int*) (event + 0xb4));
		t = fcn_00507e70(m, n, 2);
		if (n != 0) {
			if (t + gm_RandomFloat01() > g_6629c8) {
				o = *(char**) (m + 0x16c);
				c = *(unsigned char*) o;
				*(int*) (event + 0xbc) = 1;
				fcn_005782f0(n, ((CrimeProto*)lpGebaeudePROT)[c].field247 * 2 + (unsigned short) gm_RandomMod(3) + *(signed char*) (o + 0x5c) / 50, 3);
				fcn_005b2f60(n);
				return *(int*) (event + 0x70) = *(int*) (event + 0x70) + 1;
			}
			fcn_005b2fb0(n);
			*(int*) (event + 0xbc) = 0;
		}
		return *(int*) (event + 0x70) = *(int*) (event + 0x70) + 1;
	case 3:
		m = gm_LookupEntityRecordById(*(int*) (event + 0xb4));
		if (m == 0 || (o = *(char**) (m + 0x16c)) == 0) {
			*(int*) (event + 0x70) = s;
			return;
		}
		fcn_004c5da0(*(int*) (event + 0xb4), *(unsigned int*) (o + 1), s, 0, 0, 0x6a7ef4);
		return *(int*) (event + 0x70) = *(int*) (event + 0x70) + 1;
	case 4:
		m = gm_LookupEntityRecordById(*(int*) (event + 0xb4));
		if (m == 0 || (o = *(char**) (m + 0x16c)) == 0) {
			*(int*) (event + 0x70) = -1;
			return;
		}
		r = *(char**) (m + 0x184);
		if (*(int*) (r + 0x128) != 0) {
			*(pos14_7f4c00*) (event + 0x52) = *(pos14_7f4c00*) &gm_GameTime;
			return gm_AddTime((int*) (event + 0x52), 0, 4, 0);
		}
		gm_StartFilteredEntitySearch(1, 1, *(int*) (event + 0xac));
		n = gm_LookupEntityRecordById(*(int*) (event + 0xb0));
		tbl = (char*)&((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*)(event + 8)];
		m = gm_LookupEntityRecordById(*(int*) (event + 0xb4));
		if (n == 0 || tbl == 0 || m == 0) {
			*(int*) (event + 0x70) = -1;
			return;
		}
		if (*(int*) (event + 0xbc) != 0) {
			t = 1.0f - gm_GetEntitySkill(m, 1);
			fcn_005b3000(tbl, m, n, t + gm_RandomFloat01() > g_6629c8 ? 0 : 1);
			*(int*) (event + 0x70) = -1;
			return;
		}
		he_ShowFriedhofMessage(tbl, m, n);
		*(int*) (event + 0x70) = -1;
		return;
	}
	return;
tail1:
	if (p != 0) {
		fcn_00529160(0, 0, *(unsigned short*) p, 0);
	}
tail2:
	return he_FreeAction(event);
}
