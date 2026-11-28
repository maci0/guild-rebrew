#include <string.h>

#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_7f4ca4[];

char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
char* __cdecl plt_FindRecordById(char*, int);
char* __cdecl gm_FindBuildingPrimarySlot(unsigned char*);
char* __cdecl fcn_00502cd0(int, int, int, ...);
void __cdecl he_AssignActionSlot(int, int, unsigned int, int);
void __cdecl cm_SendCopyEntityData(char*);

/* Message layout (0xf8 bytes).  The type byte at +4 selects the payload:
   +8/+0xc entity ids, +0x10 selection counter, +0x28..+0x36 stamp, +0x38
   entity id list, +0x58 count/length, +0x5a..+0x6c per-type fields. */
/* ADDRESS: GOLDTL 0x00487f90 */
void __cdecl ai_DispatchMeisterAction(int* actionCtx)
{
	char m[0xf8];
	char* e;
	char* rec;
	char* r;
	char* free_rec;
	int n;
	int base;
	int k;
	int v;
	unsigned short id;

	if (actionCtx[0] == 0x28) {
		base = *(int*) (*(int*) (actionCtx[1] + 0x16c) + 0x71);
		if (actionCtx[5] > 1 && actionCtx[7] == 0) {
			n = actionCtx[8] + actionCtx[6] % actionCtx[5] + actionCtx[6] / actionCtx[5];
		} else {
			n = actionCtx[6] / actionCtx[5] + actionCtx[8];
		}
		for (rec = he_StartHandlungSearch(2, 0, 0x28, 3,
		                        *(int*) (*(int*) (actionCtx[1] + 0x16c) + 1));
		     rec != 0; rec = he_fn_Handlung()) {
			v = (int) plt_FindRecordById((char*) base, *(int*) (rec + 0xb8));
			if (v != 0 &&
			    *(unsigned short*) (v + 0xa) == *(int*) actionCtx[2]) {
				n = n - 1;
			}
		}
		for (e = (char*) 0x7f4e05;
		     actionCtx[8] < n && (int) e < 0x85a205; e += 0x21c) {
			r = e - 0x165;
			if (*(short*) (e - 0x165) == -1 ||
			    *(int*) (e + 7) != *(int*) (actionCtx[1] + 0x16c) ||
			    *e == 0 || *(int*) (e + 0x17) != 0 ||
			    *(int*) (e + 0x1f) == 0 ||
			    *(int*) (*(int*) (e + 0x1f) + 0x2c) !=
			        *(int*) (*(int*) (e + 7) + 1)) {
				continue;
			}
			free_rec = 0;
			for (k = 0; free_rec == 0 && k < 0x40; k++) {
				if (*(char*) ((char*) base + k * 0x18 + 0xd) > 1 &&
				    *(int*) ((char*) base + k * 0x18 + 0x10) == -1) {
					free_rec = (char*) base + k * 0x18;
				}
			}
			if (free_rec == 0) {
				return;
			}
			memset(m, 0, sizeof(m));
			m[4] = (char) actionCtx[0];
			*(int*) (m + 8) = *(int*) (g_7f4ca4 +
			                           *(unsigned short*) (*(int*) (actionCtx[1] + 0x16c) + 0x27) * 0x21c);
			*(int*) (m + 0xc) = *(int*) (*(int*) (actionCtx[1] + 0x16c) + 1);
			*(int*) (m + 0x28) = *(int*) &gm_GameTime;
			*(int*) (m + 0x2c) = g_7f4c04;
			*(int*) (m + 0x30) = g_7f4c08;
			*(short*) (m + 0x34) = g_7f4c0c;
			*(int*) (m + 0x10) = 1;
			*(int*) (m + 0x14) = 0;
			m[0x36] = 1;
			*(int*) (m + 0x64) = *(int*) free_rec;
			*(int*) (m + 0x58) = *(int*) (*(int*) (actionCtx[1] + 0x16c) + 1);
			*(int*) (m + 0x5c) = *(int*) (r + 0x169);
			cm_SendCopyEntityData(m);
			actionCtx[8] = actionCtx[8] + 1;
		}
		actionCtx[7] = actionCtx[7] + 1;
		return;
	}
	if (actionCtx[0] == 0x14) {
		if (actionCtx[5] > 1 && actionCtx[7] == 0) {
			n = actionCtx[8] + actionCtx[6] / actionCtx[5] + actionCtx[6] % actionCtx[5];
		} else {
			n = actionCtx[6] / actionCtx[5] + actionCtx[8];
		}
		memset(m, 0, sizeof(m));
		m[4] = (char) actionCtx[0];
		*(int*) (m + 8) = *(int*) (g_7f4ca4 +
		                           *(unsigned short*) (*(int*) (actionCtx[1] + 0x16c) + 0x27) * 0x21c);
		*(int*) (m + 0xc) = *(int*) (*(int*) (actionCtx[1] + 0x16c) + 1);
		*(int*) (m + 0x10) = 0;
		*(int*) (m + 0x14) = 0;
		*(int*) (m + 0x28) = *(int*) &gm_GameTime;
		*(int*) (m + 0x2c) = g_7f4c04;
		*(int*) (m + 0x30) = g_7f4c08;
		*(short*) (m + 0x34) = g_7f4c0c;
		m[0x36] = 1;
		*(short*) (m + 0x5a) = *(short*) actionCtx[2];
		*(int*) (m + 0x5c) =
		    *(int*) (gm_FindBuildingPrimarySlot((unsigned char*) *(int*) (actionCtx[1] + 0x16c)) + 2);
		for (e = (char*) 0x7f4e05;
		     actionCtx[8] < n && (int) e < 0x85a205; e += 0x21c) {
			if (*(short*) (e - 0x165) != -1 &&
			    *(int*) (e + 7) == *(int*) (actionCtx[1] + 0x16c) &&
			    *e != 0 && *(int*) (e + 0x17) == 0 &&
			    *(int*) (e + 0x1f) != 0 &&
			    *(int*) (*(int*) (e + 0x1f) + 0x2c) ==
			        *(int*) (*(int*) (e + 7) + 1)) {
				*(int*) (m + 0x38 + *(int*) (m + 0x10) * 4) =
				    *(int*) (e + 4);
				*(int*) (m + 0x10) = *(int*) (m + 0x10) + 1;
				actionCtx[8] = actionCtx[8] + 1;
			}
		}
		m[0x58] = (char) *(int*) (m + 0x10);
		if (*(int*) (m + 0x10) == 0) {
			actionCtx[7] = actionCtx[7] + 1;
			return;
		}
		if (*(short*) (m + 0x5a) == 0) {
			actionCtx[7] = actionCtx[7] + 1;
			return;
		}
		cm_SendCopyEntityData(m);
		actionCtx[7] = actionCtx[7] + 1;
		return;
	}
	if (actionCtx[0] == 0x15) {
		if (actionCtx[5] > 1 && actionCtx[7] == 0) {
			n = actionCtx[8] + actionCtx[6] % actionCtx[5] + actionCtx[6] / actionCtx[5];
		} else {
			n = actionCtx[6] / actionCtx[5] + actionCtx[8];
		}
		rec = fcn_00502cd0(*(int*) (*(int*) (actionCtx[1] + 0x16c) + 0x5d), 2, 6, 0,
		                   0xdd);
		memset(m, 0, sizeof(m));
		m[4] = (char) actionCtx[0];
		*(int*) (m + 8) = *(int*) (g_7f4ca4 +
		                           *(unsigned short*) (*(int*) (actionCtx[1] + 0x16c) + 0x27) * 0x21c);
		*(int*) (m + 0xc) = *(int*) (*(int*) (actionCtx[1] + 0x16c) + 1);
		*(int*) (m + 0x10) = 0;
		*(int*) (m + 0x14) = 0;
		*(int*) (m + 0x28) = *(int*) &gm_GameTime;
		*(int*) (m + 0x2c) = g_7f4c04;
		*(int*) (m + 0x30) = g_7f4c08;
		*(short*) (m + 0x34) = g_7f4c0c;
		m[0x36] = 1;
		*(short*) (m + 0x5a) = *(short*) actionCtx[2];
		if (rec != 0) {
			*(int*) (m + 0x60) = *(int*) (rec + 2);
		} else {
			rec = gm_FindBuildingPrimarySlot((unsigned char*) *(int*) (actionCtx[1] + 0x16c));
			if (rec != 0) {
				*(int*) (m + 0x60) = *(int*) (rec + 2);
			} else {
				*(int*) (m + 0x60) = -1;
			}
		}
		for (e = (char*) 0x7f4e05;
		     actionCtx[8] < n && (int) e < 0x85a205; e += 0x21c) {
			if (*(unsigned short*) (e - 0x165) != 0xffff &&
			    *(int*) (e + 7) == *(int*) (actionCtx[1] + 0x16c) &&
			    *e != 0 && *(int*) (e + 0x17) == 0 &&
			    *(int*) (e + 0x1f) != 0 &&
			    *(int*) (*(int*) (e + 0x1f) + 0x2c) ==
			        *(int*) (*(int*) (e + 7) + 1)) {
				*(int*) (m + 0x38 + *(int*) (m + 0x10) * 4) =
				    *(int*) (e + 4);
				*(int*) (m + 0x10) = *(int*) (m + 0x10) + 1;
				actionCtx[8] = actionCtx[8] + 1;
			}
		}
		m[0x58] = (char) *(int*) (m + 0x10);
		if (*(int*) (m + 0x10) == 0) {
			actionCtx[7] = actionCtx[7] + 1;
			return;
		}
		if (*(short*) (m + 0x5a) == 0) {
			actionCtx[7] = actionCtx[7] + 1;
			return;
		}
		cm_SendCopyEntityData(m);
		actionCtx[7] = actionCtx[7] + 1;
		return;
	}
	if (actionCtx[0] == 0x8c) {
		fcn_00502cd0(*(int*) (*(int*) (actionCtx[1] + 0x16c) + 0x5d), 1, 0, 0xfd);
		if (actionCtx[5] > 1 && actionCtx[7] == 0) {
			n = actionCtx[8] + actionCtx[6] % actionCtx[5] + actionCtx[6] / actionCtx[5];
		} else {
			n = actionCtx[6] / actionCtx[5] + actionCtx[8];
		}
		memset(m, 0, sizeof(m));
		m[4] = (char) actionCtx[0];
		*(int*) (m + 8) = *(int*) (g_7f4ca4 +
		                           *(unsigned short*) (*(int*) (actionCtx[1] + 0x16c) + 0x27) * 0x21c);
		*(int*) (m + 0xc) = *(int*) (*(int*) (actionCtx[1] + 0x16c) + 1);
		*(int*) (m + 0x10) = 0;
		*(int*) (m + 0x14) = 0;
		*(int*) (m + 0x28) = *(int*) &gm_GameTime;
		*(int*) (m + 0x2c) = g_7f4c04;
		*(int*) (m + 0x30) = g_7f4c08;
		*(short*) (m + 0x34) = g_7f4c0c;
		m[0x36] = 1;
		*(short*) (m + 0x58) = *(short*) actionCtx[2];
		for (e = (char*) 0x7f4e05;
		     actionCtx[8] < n && (int) e < 0x85a205; e += 0x21c) {
			if (*(short*) (e - 0x165) != -1 &&
			    *(int*) (e + 7) == *(int*) (actionCtx[1] + 0x16c) &&
			    *e != 0 && *(int*) (e + 0x17) == 0 &&
			    *(int*) (e + 0x1f) != 0 &&
			    *(int*) (*(int*) (e + 0x1f) + 0x2c) ==
			        *(int*) (*(int*) (e + 7) + 1)) {
				*(int*) (m + 0x38 + *(int*) (m + 0x10) * 4) =
				    *(int*) (e + 4);
				*(int*) (m + 0x10) = *(int*) (m + 0x10) + 1;
				actionCtx[8] = actionCtx[8] + 1;
			}
		}
		if (*(int*) (m + 0x10) == 0) {
			actionCtx[7] = actionCtx[7] + 1;
			return;
		}
		if (*(short*) (m + 0x58) == 0) {
			actionCtx[7] = actionCtx[7] + 1;
			return;
		}
		cm_SendCopyEntityData(m);
		actionCtx[7] = actionCtx[7] + 1;
		return;
	}
	rec = he_StartHandlungSearch(2, 0, actionCtx[0], 3,
	                   *(int*) (*(int*) (actionCtx[1] + 0x16c) + 1));
	while (rec != 0) {
		if (actionCtx[0] == 4 &&
		    *(unsigned short*) (rec + 0xac) == *(int*) actionCtx[2]) {
			break;
		}
		if (actionCtx[0] == 8 &&
		    *(unsigned short*) (rec + 0xac) == *(int*) actionCtx[2]) {
			break;
		}
		if (actionCtx[0] == 3 &&
		    *(unsigned short*) (rec + 0xac) == *(int*) actionCtx[2]) {
			break;
		}
		rec = he_fn_Handlung();
	}
	if (rec == 0) {
		memset(m, 0, sizeof(m));
		m[4] = (char) actionCtx[0];
		*(int*) (m + 8) = *(int*) (g_7f4ca4 +
		                           *(unsigned short*) (*(int*) (actionCtx[1] + 0x16c) + 0x27) * 0x21c);
		*(int*) (m + 0xc) = *(int*) (*(int*) (actionCtx[1] + 0x16c) + 1);
		*(int*) (m + 0x28) = *(int*) &gm_GameTime;
		*(int*) (m + 0x2c) = g_7f4c04;
		*(int*) (m + 0x30) = g_7f4c08;
		*(int*) (m + 0x10) = 0;
		*(int*) (m + 0x14) = 0;
		*(short*) (m + 0x34) = g_7f4c0c;
		m[0x36] = 1;
		if (actionCtx[0] == 4) {
			*(short*) (m + 0x58) = *(short*) actionCtx[2];
			*(int*) (m + 0x5c) = -1;
			*(int*) (m + 0x68) = *(int*) (*(int*) (actionCtx[1] + 0x16c) + 1);
			*(int*) (m + 0x6c) = *(int*) (actionCtx[3] + 2);
		}
		if (actionCtx[0] == 8) {
			*(short*) (m + 0x58) = *(short*) actionCtx[2];
			*(int*) (m + 0x5c) = *(int*) (*(int*) (actionCtx[1] + 0x16c) + 1);
			*(int*) (m + 0x60) = *(int*) (actionCtx[4] + 2);
		}
		if (actionCtx[0] == 3) {
			*(short*) (m + 0x58) = *(short*) actionCtx[2];
			*(int*) (m + 0x64) = *(int*) (*(int*) (actionCtx[1] + 0x16c) + 1);
			*(int*) (m + 0x6c) = *(int*) (actionCtx[3] + 2);
			*(int*) (m + 0x68) = *(int*) (actionCtx[4] + 2);
		}
		cm_SendCopyEntityData(m);
		actionCtx[7] = actionCtx[7] + 1;
		return;
	}
	if (actionCtx[5] > 1 && actionCtx[7] == 0) {
		n = actionCtx[8] + actionCtx[6] % actionCtx[5] + actionCtx[6] / actionCtx[5];
	} else {
		n = actionCtx[6] / actionCtx[5] + actionCtx[8];
	}
	v = 0;
	if (actionCtx[0] == 8 || actionCtx[0] == 3) {
		v = (int) fcn_00502cd0(*(int*) (*(int*) (actionCtx[1] + 0x16c) + 0x5d), 1,
		                       0, 0x37);
	} else if (actionCtx[0] == 4) {
		v = (int) gm_FindBuildingPrimarySlot((unsigned char*) *(int*) (actionCtx[1] + 0x16c));
	}
	for (e = (char*) 0x7f4e05;
	     actionCtx[8] < n && (int) e < 0x85a205; e += 0x21c) {
		id = *(unsigned short*) (e - 0x165);
		if (id != 0xffff &&
		    *(int*) (e + 7) == *(int*) (actionCtx[1] + 0x16c) &&
		    *e != 0 && *(int*) (e + 0x17) == 0) {
			he_AssignActionSlot(*(int*) (actionCtx[1] + 0x16c), v,
			             id, (int) rec);
			actionCtx[8] = actionCtx[8] + 1;
		}
	}
	actionCtx[7] = actionCtx[7] + 1;
	return;
}
