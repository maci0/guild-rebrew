#include "Develop/game_structs.h"

extern char g_7f4ca4[];
extern char g_6b5c60[];
extern float g_66414c;

float __cdecl gm_RandomFloat01(void);
char* __cdecl fcn_00508e40(int id);
void __cdecl fcn_005100f0(int id, int amount);
void __cdecl fcn_004c5420(int handle, int a, int b, int c, int d);
int __cdecl fcn_004c54c0(int a, int b, int value, int flag);
float __cdecl fcn_00507f10(char* entity, int idx);
void __cdecl fcn_0051af00(char* buf, int id, ...);
void __cdecl fcn_00545d40(int id, int arg, char* text1, int flags, int value, char* text2);
int __cdecl fcn_00526120(char* text, int arg);
int __cdecl srv_GetEntityOfficeSlot(char* entity, void* role_out, void* slot_out);
int __cdecl fcn_004e8240(int id, char* ea, char* eb, int x1, int x2);
int __cdecl fcn_004e8b80(int kind, int max, OFFICE_SLOT* out);

/* ADDRESS: GOLDTL 0x004eba60 */
unsigned int __cdecl fcn_004eba60(char* e, unsigned int* a1)
{
	float f;
	float g;
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
	sign = (f > g_66414c) ? 1 : -1;

	if (e[0x169] == 0x1e) {
		if (a1[0] != 1)
			return 0;
		h = fcn_00508e40(a1[1]);
		if (h == 0)
			return 0;
		if (h[0x166] == 0)
			return 0;
		if (h == e)
			return 0;
		if (srv_GetEntityOfficeSlot(h, role, slot) == 0)
			return 0;
		if (f > g_66414c)
			fcn_004e8240(slot[0], 0, 0, 4, 0xff);
		fcn_005100f0(*(int*) (e + 4), -8);
		fcn_004c5420(*(int*) (e + 4), 0x1c8, 4, 0x10000000, 0);
		if (f > g_66414c) {
			if (7 == h[2] || 6 == h[2]) {
				fcn_0051af00(buf, 0x1684);
				fcn_00545d40(*(int*) (h + 4), -1, buf, 0, 0x5fb, g_6b5c60);
			}
			fcn_0051af00(buf, 0x1682, *(unsigned short*) h, *(unsigned short*) h);
			p = g_7f4ca4;
			do {
				if ((p[-2] == 6 || p[-2] == 7) && *(int*) p != *(int*) (h + 4) && *(int*) p != *(int*) (e + 4))
					fcn_00545d40(*(int*) p, -1, buf, 0, 0x5fe, g_6b5c60);
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				fcn_0051af00(buf, 0x1680, *(unsigned short*) h, *(unsigned short*) h);
				fcn_00526120(buf, 0);
			}
		} else {
			if (7 == h[2] || 6 == h[2]) {
				fcn_0051af00(buf, 0x1685);
				fcn_00545d40(*(int*) (h + 4), -1, buf, 0, 0x5fb, g_6b5c60);
			}
			fcn_0051af00(buf, 0x1683, *(unsigned short*) h, *(unsigned short*) h);
			p = g_7f4ca4;
			do {
				if ((p[-2] == 6 || p[-2] == 7) && *(int*) p != *(int*) (h + 4) && *(int*) p != *(int*) (e + 4))
					fcn_00545d40(*(int*) p, -1, buf, 0, 0x5fe, g_6b5c60);
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				fcn_0051af00(buf, 0x1681, *(unsigned short*) h, *(unsigned short*) h);
				fcn_00526120(buf, 0);
			}
		}
		return sign;
	}

	if (e[0x169] == 0x1f || e[0x169] == 0x21) {
		if (a1[0] != 4)
			return 0;
		if (a1[1] < 1 || a1[1] > 6)
			return 0;
		if (f > g_66414c) {
			n = fcn_004e8b80(a1[1], 6, arr);
			g = fcn_00507f10(e, 4);
			value = (int) (((gm_RandomFloat01() + 1.0f) * g * 15.0f + 5.0) * 2.55f);
			for (i = 1; i < n; i++) {
				id1 = arr[i - 1].mplayerid;
				if (id1 == *(int*) (e + 4) || id1 == -1)
					continue;
				for (k = i; k < n; k++) {
					id2 = arr[k].mplayerid;
					if (id2 == *(int*) (e + 4) || id2 == -1)
						continue;
					fcn_004c54c0(id2, id1, -value, 1);
					fcn_004c54c0(id1, id2, -value, 1);
				}
			}
		} else {
			n = fcn_004e8b80(a1[1], 6, arr);
		}
		fcn_005100f0(*(int*) (e + 4), -8);
		fcn_004c5420(*(int*) (e + 4), 0x1c8, 4, 0x10000000, 0);
		if (f > g_66414c) {
			fcn_0051af00(buf, 0x1672, a1[1] + 0x1663);
			fcn_0051af00(buf2, 0x1670, a1[1] + 0x1663);
			p = g_7f4ca4;
			do {
				if ((p[-2] == 6 || p[-2] == 7) && *(int*) p != *(int*) (e + 4)) {
					fmt = 0x5fe;
					out = buf2;
					for (k = 0; k < n; k++) {
						if (arr[k].mplayerid == *(int*) p) {
							fmt = 0x5fb;
							out = buf;
							break;
						}
					}
					fcn_00545d40(*(int*) p, -1, out, 0, fmt, g_6b5c60);
				}
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				fcn_0051af00(buf, 0x166e, a1[1] + 0x1663);
				fcn_00526120(buf, 0);
				return sign;
			}
		} else {
			fcn_0051af00(buf, 0x1673, a1[1] + 0x1663);
			fcn_0051af00(buf2, 0x1671, a1[1] + 0x1663);
			p = g_7f4ca4;
			do {
				if ((p[-2] == 6 || p[-2] == 7) && *(int*) p != *(int*) (e + 4)) {
					fmt = 0x5fe;
					out = buf2;
					for (k = 0; k < n; k++) {
						if (arr[k].mplayerid == *(int*) p) {
							fmt = 0x5fb;
							out = buf;
							break;
						}
					}
					fcn_00545d40(*(int*) p, -1, out, 0, fmt, g_6b5c60);
				}
				p += 0x21c;
			} while ((int) p < (int) (g_7f4ca4 + 0x65400));
			if (e[2] == 6) {
				fcn_0051af00(buf, 0x166f, a1[1] + 0x1663);
				fcn_00526120(buf, 0);
			}
		}
		return sign;
	}

	if (e[0x169] != 0x20)
		return 0;
	if (a1[0] != 4)
		return 0;
	if (a1[1] < 1 || a1[1] > 6)
		return 0;
	if (f > g_66414c) {
		n = fcn_004e8b80(a1[1], 6, arr);
		g = fcn_00507f10(e, 4);
		value = (int) (((gm_RandomFloat01() + 1.0f) * g * 15.0f + 5.0) * 2.55f);
		for (k = 0; k < n; k++) {
			id1 = arr[k].mplayerid;
			if (id1 != *(int*) (e + 4) && id1 != -1)
				fcn_004c54c0(*(int*) (e + 4), id1, value, 1);
		}
	}
	fcn_005100f0(*(int*) (e + 4), -8);
	fcn_004c5420(*(int*) (e + 4), 0x1c8, 4, 0x10000000, 0);
	if (f > g_66414c) {
		fcn_0051af00(buf, 0x167a, a1[1] + 0x1663);
		p = g_7f4ca4;
		do {
			if ((p[-2] == 6 || p[-2] == 7) && *(int*) p != *(int*) (e + 4))
				fcn_00545d40(*(int*) p, -1, buf, 0, 0x5fd, g_6b5c60);
			p += 0x21c;
		} while ((int) p < (int) (g_7f4ca4 + 0x65400));
		if (e[2] != 6)
			return sign;
		fcn_0051af00(buf, 0x1678, a1[1] + 0x1663);
	} else {
		fcn_0051af00(buf, 0x167b, a1[1] + 0x1663);
		p = g_7f4ca4;
		do {
			if ((p[-2] == 6 || p[-2] == 7) && *(int*) p != *(int*) (e + 4))
				fcn_00545d40(*(int*) p, -1, buf, 0, 0x5fe, g_6b5c60);
			p += 0x21c;
		} while ((int) p < (int) (g_7f4ca4 + 0x65400));
		if (e[2] != 6)
			return sign;
		fcn_0051af00(buf, 0x1679, a1[1] + 0x1663);
	}
	fcn_00526120(buf, 0);
	return sign;
}
