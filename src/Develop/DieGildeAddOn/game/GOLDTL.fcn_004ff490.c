#include <string.h>

#include "Develop/DieGildeAddOn/game/game_timestamp.h"








#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_664158;
extern int g_773d48;
extern float g_696444[];

char* __cdecl gm_LookupEntityRecordById(int);
float __cdecl gm_RandomFloat01(void);
void __cdecl cm_RequestChangeFloat(int, int, float);
void __cdecl gm_AddTime(void*, int, int, int);
unsigned short __cdecl gm_RandomMod(int);
int __cdecl cm_RequestAllocSpieler(int, int, int, int, int, int, int, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);
int __cdecl cm_GetCommandResult(int);
void __cdecl cm_BeginPacketFieldDelta(int, int);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl fcn_004c5980(void*);

/* ADDRESS: GOLDTL 0x004ff490 */
void __cdecl fcn_004ff490(char* entity)
{
	char* ent;
	char* other;
	char* p;
	char* e;
	int id;
	int handle;
	int count;
	int i;
	int extra;
	GAME_TIMESTAMP t;

	char pkt[0x114];
	float f;

	if ((unsigned char) entity[2] >= 10) {
		return;
	}
	if (entity[8] == 0) {
		return;
	}
	if (entity[9] != 1) {
		return;
	}
	if ((unsigned char) entity[0x1b1] > 0) {
		return;
	}
	if ((*(unsigned int*) (entity + 0x1c8)) & 0x40000) {
		return;
	}

	ent = gm_LookupEntityRecordById(*(unsigned int*) (entity + 0x5c));
	if (*(float*) (entity + 0x7c) > 1.0f) {
		cm_RequestChangeFloat(*(unsigned int*) (entity + 4), 0x7c, gm_RandomFloat01() * -0.5f - *(float*) (entity + 0x7c));
		g_773d48++;
		if (ent == 0) {
			return;
		}

		t = *(GAME_TIMESTAMP*) &gm_GameTime;
		extra = 2;
		gm_AddTime(&t, 8, 0, 0);

		other = 0;
		t.hour = gm_RandomMod(4) + 8;
		t.minute = 0;
		handle = *(int*) (entity + 0x170);
		if (handle != 0) {
			id = *(int*) (handle + 1);
		} else {
			id = -1;
		}
		if (*(char*) (ent + 2) == 6 || *(char*) (ent + 2) == 7) {
			count = 0;
			p = ent + 0x68;
			for (i = 0; i < 4; i++) {
				if (*(int*) p != -1) {
					count++;
				}
				p += 4;
			}
			if (count == 0) {
				extra = (unsigned char) ent[9];
			}
			if (*(int*) (ent + 0x170) != 0) {
				id = *(int*) (*(int*) (ent + 0x170) + 1);
			} else if (handle != 0) {
				id = *(int*) (handle + 1);
			} else {
				id = -1;
			}
			other = ent;
		} else if (*(char*) (entity + 2) == 6 || *(char*) (entity + 2) == 7) {
			count = 0;
			p = entity + 0x68;
			for (i = 0; i < 4; i++) {
				if (*(int*) p != -1) {
					count++;
				}
				p += 4;
			}
			if (count == 0) {
				extra = (unsigned char) entity[9];
			}
			if (handle != 0) {
				id = *(int*) (handle + 1);
			} else if (*(int*) (ent + 0x170) != 0) {
				id = *(int*) (*(int*) (ent + 0x170) + 1);
			} else {
				id = -1;
			}
			other = entity;
		}

		id = cm_RequestAllocSpieler(8, *(int*) (ent + 4), *(int*) (entity + 4), 0, id, 0, 0, extra);
		while (cm_GetCommandStatus(id) == 0) {
			cm_StepCommandQueue();
		}
		if (cm_GetCommandStatus(id) == 2) {
			return;
		}
		handle = cm_GetCommandResult(id);
		if (other != 0) {
			int mode;

			mode = 0x12;
			memset(pkt, 0, 0x114);
			id = *(int*) (other + 4);
			*(GAME_TIMESTAMP*) (pkt + 0x18) = t;
			*(int*) (pkt + 0xc) = id;
			*(int*) (pkt + 0x34) = id;
			id = *(int*) (handle + 4);
			pkt[8] = 7;
			pkt[0x26] = 0xa0;
			*(int*) (pkt + 0x14) = -1;
			pkt[0x30] = 2;
			*(int*) (pkt + 0x38) = id;
			cm_BeginPacketFieldDelta(handle, id);
			cm_AppendPacketFieldDelta(1, 1, 2, &mode);
			cm_RequestChangeAttribute();
			fcn_004c5980(pkt);
			g_773d48++;
			return;
		}
	}

	if (ent != 0 && ent[8] != 0 && *(unsigned short*) (entity + 0xa) <= 0x26) {
		count = 0;
		for (i = 3, p = entity + 0x68; i < 8; i++, p += 4) {
			if (*(int*) p != -1) {
				e = gm_LookupEntityRecordById(*(int*) p);
				if (*(char*) (e + 2) == 6 || *(char*) (e + 2) == 7 || *(char*) (e + 2) == 5) {
					return;
				}
				if (*(char*) (e + 2) != 0xf) {
					count++;
				}
			}
		}
		if (count == 4) {
			return;
		}
		if (*(char*) (ent + 2) == 6 || *(char*) (ent + 2) == 7) {
			extra = 0;
			for (i = 3, p = ent + 0x68; i < 8; i++, p += 4) {
				if (*(int*) p != -1) {
					e = gm_LookupEntityRecordById(*(int*) p);
					if (*(char*) (e + 2) == 6 || *(char*) (e + 2) == 7 || *(char*) (e + 2) == 5) {
						return;
					}
					if (*(char*) (e + 2) != 0xf) {
						extra++;
					}
				}
			}
			if (extra == 5) {
				return;
			}
		}
		f = (gm_RandomFloat01() + 1.0f) * g_696444[count];
		cm_RequestChangeFloat(*(unsigned int*) (entity + 4), 0x7c, f);
		g_773d48++;
		return;
	}
}
