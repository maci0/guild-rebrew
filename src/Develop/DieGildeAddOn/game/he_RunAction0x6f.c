#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl he_FreeAction(char*);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl gm_AddTime(void*, int, int, int);
int __cdecl cm_SendSetHE(int, char*);
int __cdecl cm_GetCommandStatus(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_RegisterApEvent(int, char*, int, int);

/* ADDRESS: GOLDTL 0x00556b40 */
void __cdecl he_RunAction0x6f(char* e)
{
	char buf[0x200];
	char* a;
	char* b;
	int r;

	a = gm_LookupEntityRecordById(*(int*) (e + 0xb0));
	b = gm_LookupEntityRecordById(*(int*) (e + 0xac));
	if (*(int*) (e + 0x70) == -1) {
		he_FreeAction(e);
		return;
	}
	if (*(int*) (e + 0x70) == -2) {
		if ((e[0x78] & 4) != 0) {
			he_FreeAction(e);
			return;
		}
		if (a != 0) {
			cm_RequestChangeBits(*(int*) (a + 4), 0x1c8, 4, 0, 0x800000);
			if (b != 0) {
				cm_RequestCopyEntityData(*(int*) (b + 4), *(int*) (a + 4), (-8 - *(int*) (e + 0xb4)) * 5, 1);
			}
		}
		he_FreeAction(e);
		return;
	}
	if ((e[0x78] & 4) != 0) {
		return;
	}
	if (a == 0) {
		gm_AddTime(e + 0x52, 0, 2, 0);
		*(int*) (e + 0x84) = cm_SendSetHE(-1, e);
		return;
	}
	if (*(int*) (e + 0x70) == 2) {
		r = cm_GetCommandStatus(*(int*) (e + 0x84));
		if (r == 0) {
			return;
		}
		if (r == 1) {
			gm_AddTime(e + 0x52, 0, 2, 0);
			cm_SendSetHE(0, e);
			return;
		}
		if (r == 2) {
			gm_AddTime(e + 0x52, 0, 2, 0);
			cm_SendSetHE(-1, e);
		}
		return;
	}
	if (b != 0 && b[8] != 0) {
		if (*(int*) (e + 0x70) == 1) {
			cm_RequestChangeBits(*(int*) (a + 4), 0x1c8, 4, 0, 0x800000);
			cm_RequestCopyEntityData(*(int*) (b + 4), *(int*) (a + 4), (-2 - *(int*) (e + 0xb4)) * 5, 1);
			gm_AddTime(e + 0x52, 0, 2, 0);
			*(int*) (e + 0x84) = cm_SendSetHE(-1, e);
			return;
		}
		if (*(int*) (e + 0x70) == 3) {
			*(pos14_7f4c00*) (e + 0x52) = gm_GameTime;
			cm_SendSetHE(0, e);
			return;
		}
		if (a[9] == 1) {
			io_FormatTextBuffer(buf, 0xb4, *(unsigned short*) a);
		} else {
			io_FormatTextBuffer(buf, 0xb5, *(unsigned short*) a);
		}
		he_RegisterApEvent(*(unsigned short*) (e + 8), buf, -*(int*) (e + 0xb8), 0);
		(*(int*) (e + 0xb4))++;
		gm_AddTime(e + 0x52, 0x18, 0, 0);
		*(int*) (e + 0x84) = cm_SendSetHE(0, e);
		return;
	}
	cm_RequestChangeBits(*(int*) (a + 4), 0x1c8, 4, 0, 0x800000);
	gm_AddTime(e + 0x52, 0, 2, 0);
	*(int*) (e + 0x84) = cm_SendSetHE(-1, e);
}
