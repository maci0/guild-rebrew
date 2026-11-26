#include "Develop/game_structs.h"

extern char g_7f4ca4[];
extern char g_6b5c60[];
#include "Develop/DieGildeAddOn/game/game_data.h"

float __cdecl gm_RandomFloat01(void);
char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl fcn_005100f0(int id, int amount);
void __cdecl cm_RequestChangeBits(int handle, int a, int b, int c, int d);
int __cdecl cm_RequestCopyEntityData(int a, int b, int value, int flag);
float __cdecl gm_GetEntitySkill(char* entity, int idx);
void __cdecl io_FormatTextBuffer(char* buf, int id, ...);
void __cdecl fcn_00545d40(int id, int arg, char* text1, int flags, int value, char* text2);
int __cdecl fcn_00526120(char* text, int arg);
int __cdecl srv_GetEntityOfficeSlot(char* entity, void* role_out, void* slot_out);
int __cdecl amt_SendOfficeCommand(int id, char* ea, char* eb, int x1, int x2);
int __cdecl amt_FindOfficeSlotsByKind(int kind, int max, OFFICE_SLOT* out);

/* ADDRESS: GOLDTL 0x004eba60 */
unsigned int __cdecl fcn_004eba60(char* e, unsigned int* target)
{
	float f;
	int sign;
	int value;
	int n;
	int i;
	int k;
	int fmt;
	char* p;
	char* out;
	char* h;
	int id1;
	int id2;
	int slot[6];
	OFFICE_SLOT arr[6];
	int role[6];
	char buf[0x400];
	char buf2[0x400];

	f = gm_RandomFloat01();
	sign = (f > 0.3f) ? 1 : -1;

	if (e[0x169] == 0x1e) {
		if (target[0] != 1)
			return 0;
		h = gm_LookupEntityRecordById(target[1]);
		if (h == 0)
			return 0;
		if (h[0x166] == 0)
			return 0;
		if (h == e)
			return 0;
		if (srv_GetEntityOfficeSlot(h, role, slot) == 0)
			return 0;
		if (f > 0.3f)
			amt_SendOfficeCommand(slot[0], 0, 0, 4, 0xff);
		fcn_005100f0(*(int*) (e + 4), -8);
		cm_RequestChangeBits(*(int*) (e + 4), 0x1c8, 4, 0x10000000, 0);
		if (f > 0.3f) {
			if (7 == h[2] || 6 == h[2]) {
				io_FormatTextBuffer(buf, 0x1684);
				fcn_00545d40(*(int*) (h + 4), -1, buf, 0, 0x5fb, g_6b5c60);
			}
			io_FormatTextBuffer(buf, 0x1682, *(unsigned short*) h, *(unsigned short*) h);
			p = g_7f4ca4;
			do {
				if ((7 == p[-2] || 6 == p[-2]) && *(int*) p != *(int*) (h + 4) && *(int*) p != *(int*) (e + 4))
					fcn_00545d40(*(int*) p, -1, buf, 0, 0x5fe, g_6b5c60);
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				io_FormatTextBuffer(buf, 0x1680, *(unsigned short*) h, *(unsigned short*) h);
				fcn_00526120(buf, 0);
			}
		} else {
			if (7 == h[2] || 6 == h[2]) {
				io_FormatTextBuffer(buf, 0x1685);
				fcn_00545d40(*(int*) (h + 4), -1, buf, 0, 0x5fb, g_6b5c60);
			}
			io_FormatTextBuffer(buf, 0x1683, *(unsigned short*) h, *(unsigned short*) h);
			p = g_7f4ca4;
			do {
				if ((7 == p[-2] || 6 == p[-2]) && *(int*) p != *(int*) (h + 4) && *(int*) p != *(int*) (e + 4))
					fcn_00545d40(*(int*) p, -1, buf, 0, 0x5fe, g_6b5c60);
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				io_FormatTextBuffer(buf, 0x1681, *(unsigned short*) h, *(unsigned short*) h);
				fcn_00526120(buf, 0);
			}
		}
		return sign;
	}

	if (e[0x169] != 0x1f && e[0x169] != 0x21) {
		if (e[0x169] != 0x20)
			return 0;
		if (target[0] != 4)
			return 0;
		if (target[1] < 1 || target[1] > 6)
			return 0;
		if (f > 0.3f) {
			float g;
			n = amt_FindOfficeSlotsByKind(target[1], 6, arr);
			g = gm_GetEntitySkill(e, 4);
			value = (int) (((gm_RandomFloat01() + 1.0f) * g * 15.0f + 5.0) * 2.55f);
			for (k = 0; k < n; k++) {
				id1 = arr[k].mplayerid;
				if (id1 != *(int*) (e + 4) && id1 != -1)
					cm_RequestCopyEntityData(*(int*) (e + 4), id1, value, 1);
			}
		}
		fcn_005100f0(*(int*) (e + 4), -8);
		cm_RequestChangeBits(*(int*) (e + 4), 0x1c8, 4, 0x10000000, 0);
		if (f > 0.3f) {
			io_FormatTextBuffer(buf, 0x167a, target[1] + 0x1663);
			p = g_7f4ca4;
			do {
				if ((7 == p[-2] || 6 == p[-2]) && *(int*) p != *(int*) (e + 4))
					fcn_00545d40(*(int*) p, -1, buf, 0, 0x5fd, g_6b5c60);
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				io_FormatTextBuffer(buf, 0x1678, target[1] + 0x1663);
				fcn_00526120(buf, 0);
			}
		} else {
			io_FormatTextBuffer(buf, 0x167b, target[1] + 0x1663);
			p = g_7f4ca4;
			do {
				if ((7 == p[-2] || 6 == p[-2]) && *(int*) p != *(int*) (e + 4))
					fcn_00545d40(*(int*) p, -1, buf, 0, 0x5fe, g_6b5c60);
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				io_FormatTextBuffer(buf, 0x1679, target[1] + 0x1663);
				fcn_00526120(buf, 0);
			}
		}
	} else {
		if (target[0] != 4)
			return 0;
		if (target[1] < 1 || target[1] > 6)
			return 0;
		if (f > 0.3f) {
			float g;
			n = amt_FindOfficeSlotsByKind(target[1], 6, arr);
			g = gm_GetEntitySkill(e, 4);
			value = (int) (((gm_RandomFloat01() + 1.0f) * g * 15.0f + 5.0) * 2.55f);
			for (i = 0; i < n - 1; i++) {
				id1 = arr[i].mplayerid;
				if (id1 == *(int*) (e + 4) || id1 == -1)
					continue;
				for (k = i + 1; k < n; k++) {
					id2 = arr[k].mplayerid;
					if (id2 == *(int*) (e + 4) || id2 == -1)
						continue;
					cm_RequestCopyEntityData(id2, id1, -value, 1);
					cm_RequestCopyEntityData(id1, id2, -value, 1);
				}
			}
		} else {
			n = amt_FindOfficeSlotsByKind(target[1], 6, arr);
		}
		fcn_005100f0(*(int*) (e + 4), -8);
		cm_RequestChangeBits(*(int*) (e + 4), 0x1c8, 4, 0x10000000, 0);
		if (f > 0.3f) {
			io_FormatTextBuffer(buf, 0x1672, target[1] + 0x1663);
			io_FormatTextBuffer(buf2, 0x1670, target[1] + 0x1663);
			p = g_7f4ca4;
			do {
				if ((7 == p[-2] || 6 == p[-2]) && *(int*) p != *(int*) (e + 4)) {
					for (k = 0; k < n; k++) {
						if (arr[k].mplayerid == *(int*) p) {
							fcn_00545d40(*(int*) p, -1, buf, 0, 0x5fb, g_6b5c60);
							goto next_p1;
						}
					}
					fcn_00545d40(*(int*) p, -1, buf2, 0, 0x5fe, g_6b5c60);
				}
			next_p1:
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				io_FormatTextBuffer(buf, 0x166e, target[1] + 0x1663);
				fcn_00526120(buf, 0);
				return sign;
			}
		} else {
			io_FormatTextBuffer(buf, 0x1673, target[1] + 0x1663);
			io_FormatTextBuffer(buf2, 0x1671, target[1] + 0x1663);
			p = g_7f4ca4;
			do {
				if ((7 == p[-2] || 6 == p[-2]) && *(int*) p != *(int*) (e + 4)) {
					for (k = 0; k < n; k++) {
						if (arr[k].mplayerid == *(int*) p) {
							fcn_00545d40(*(int*) p, -1, buf, 0, 0x5fb, g_6b5c60);
							goto next_p2;
						}
					}
					fcn_00545d40(*(int*) p, -1, buf2, 0, 0x5fe, g_6b5c60);
				}
			next_p2:
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				io_FormatTextBuffer(buf, 0x166f, target[1] + 0x1663);
				fcn_00526120(buf, 0);
			}
		}
	}
	return sign;
}
