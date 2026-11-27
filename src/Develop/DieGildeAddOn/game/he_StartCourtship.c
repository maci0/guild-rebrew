#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl cm_SendSetHE(int, char*);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
char* __cdecl he_fn_Handlung(void);
char* __cdecl he_StartHandlungSearch(int, int, int);
void __cdecl he_RollTripletEventScores(char*, unsigned short*, unsigned short*);
int __cdecl gm_CalcWerbungSteps(int, int);

/* ADDRESS: GOLDTL 0x0054c800 */
void __cdecl he_StartCourtship(char* e)
{
	char* a;
	char* b;
	char* f;

	*(int*) (e + 0x70) = 0;
	if ((e[0x78] & 2) == 0) {
		return;
	}
	a = gm_LookupEntityRecordById(*(int*) (e + 0xac));
	b = gm_LookupEntityRecordById(*(int*) (e + 0xb0));
	if (a == 0 || b == 0 || a[9] == b[9]) {
		*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
		gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
		*(int*) (e + 0x84) = cm_SendSetHE(-1, e);
		return;
	}
	if (*(int*) (a + 0x5c) != -1) {
		int v = -1;

		cm_BeginPacketFieldDelta(a, *(int*) (a + 4));
		cm_AppendPacketFieldDelta(4, 1, 0x5c, &v);
		cm_RequestChangeAttribute();
	}
	if (*(int*) (b + 0x5c) != -1) {
		int v = -1;

		cm_BeginPacketFieldDelta(b, *(int*) (b + 4));
		cm_AppendPacketFieldDelta(4, 1, 0x5c, &v);
		cm_RequestChangeAttribute();
	}
	f = he_StartHandlungSearch(1, 0, 0x41);
	for (; f != 0; f = he_fn_Handlung()) {
		if (*(int*) (f + 0xb0) == *(int*) (a + 4)) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			gm_AddTime((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
			*(int*) (e + 0x84) = cm_SendSetHE(-1, e);
			return;
		}
	}
	*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (e + 0x52), 0x18, 0, 0);
	*(int*) (e + 0x58) = 0;
	*(int*) (e + 0x70) = 0;
	e[0xb8] = 0;
	*(short*) (e + 0x56) = 8;
	e[0xb9] = (char) gm_CalcWerbungSteps(*(int*) (e + 0xac), *(int*) (e + 0xb0));
	e[0xba] = 0;
	he_RollTripletEventScores(e, (unsigned short*) a, (unsigned short*) b);
	e[0xbb] = 0;
	*(int*) (e + 0x84) = -1;
	cm_SendSetHE(0, e);
}
