#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);
int __cdecl cm_RequestUpdateStraftatState(int, int, int, int);
int __cdecl cm_SendSetHE(int, char*);

/* ADDRESS: GOLDTL 0x0054aa70 */
void __cdecl he_StartCourtTrial(char* action)
{
	char* accused;
	char buf[0x100];
	char* accuser;
	char* existing;
	pos14_7f4c00* stamp;

	accused = gm_LookupEntityRecordById(*(int*) (action + 0xb0));
	accuser = gm_LookupEntityRecordById(*(int*) (action + 0xac));
	stamp = (pos14_7f4c00*) (action + 0xc5);
	*stamp = gm_GameTime;
	gm_AddTime(stamp, 0x18, 0, 0);
	*(short*) (action + 0xc9) = 0xa;
	*(int*) (action + 0xcb) = 0;
	*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
	if ((action[0x78] & 2) == 0) {
		return;
	}
	for (existing = he_StartHandlungSearch(1, 0, 0x2c); existing != 0; existing = he_fn_Handlung()) {
		if (*(int*) (existing + 4) == *(int*) (action + 4)) {
			continue;
		}
		if (*(char*) (existing + 0xc4) != *(char*) (action + 0xc4)) {
			continue;
		}
		if (*(int*) (existing + 0xac) == *(int*) (action + 0xac)) {
			io_FormatTextBuffer(buf, 0x1bbe, *(unsigned short*) accuser, *(unsigned short*) accused);
			he_PostEntityMessage(*(int*) (accuser + 4), *(int*) (accuser + 4), buf, 0, 0x5f5, 0);
			*(pos14_7f4c00*) (action + 0x52) = gm_GameTime;
			*(int*) (action + 0x84) = cm_SendSetHE(-1, action);
			return;
		}
		if (*(int*) (action + 0xc5) > *(int*) (existing + 0xc5)) {
			continue;
		}
		*stamp = *(pos14_7f4c00*) (existing + 0xc5);
		gm_AddTime(stamp, 0x18, 0, 0);
		*(short*) (action + 0xc9) = 0xa;
		*(int*) (action + 0xcb) = 0;
	}
	*(int*) (action + 0xd4) = cm_RequestUpdateStraftatState(*(int*) (action + 0xac), *(int*) (action + 0xb0), *(int*) (action + 4), 1);
	*(int*) (action + 0x84) = cm_SendSetHE(0, action);
}
