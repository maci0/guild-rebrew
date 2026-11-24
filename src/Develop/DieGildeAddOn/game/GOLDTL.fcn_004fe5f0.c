#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 gm_GameTime;
extern float g_662a94;
extern float g_6628a8;
extern float g_66444c;
extern float g_665370;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern char g_7f4ca2[];
extern char g_7f4ca4[];
extern int g_773d48;
extern char* g_aed32c;
extern char g_6b5c60[];
extern char g_6964f0[];

int __cdecl fcn_0050a710(char*);
int __cdecl fcn_004f3770(char*);
void __cdecl fcn_004c57e0(int, int);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4700(int, int, char*, void*);
void __cdecl fcn_004c53a0(void);
void __cdecl fcn_004c5530(char*);
void __cdecl cm_AppendPacketFieldDelta(int, int, int, void*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c5420(int, int, int, int, int);
int __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_0050c710(int, int, int);
void __cdecl fcn_004ff490(char*);

/* ADDRESS: GOLDTL 0x004fe5f0 */
double __cdecl fcn_004fe5f0(char* entity)
{
	char msg[0xf8];
	char nb[0x200];
	char c;
	char kind;
	float v10;
	float v15;
	double v11;
	int e;
	int v4;
	unsigned int v5;
	int v6;
	unsigned short w = 0;

	if (*(unsigned short*) entity == 0xffff) {
		return g_662a94;
	}
	if (*(char*) (entity + 2) == 0x0f) {
		v4 = fcn_0050a710(entity);
		if (v4 != 0) {
			fcn_004c57e0(*(int*) (entity + 4), 1);
			g_773d48 += 1;
		}
		return g_662a94;
	}
	if (*(char*) (entity + 2) == 0x14) {
		v4 = fcn_004f3770(entity);
		if (v4 == 1) {
			c = 0;
			fcn_004c4510(entity, *(int*) (entity + 4));
			fcn_004c4700(1, 1, (char*) ((int) entity + (8 - (int) g_aed32c)),
			             &c);
			fcn_004c53a0();
			memset(msg, 0, sizeof(msg));
			msg[4] = 0x72;
			*(int*) (msg + 8) = *(int*) (entity + 4);
			*(int*) (msg + 0xc) = -1;

			msg[0x36] = 2;
			*(pos14_7f4c00*) (msg + 0x28) = gm_GameTime;


			*(int*) (msg + 0x58) = *(int*) (entity + 4);
			fcn_004c5530(msg);
			e = *(int*) (entity + 0x16c);
			if (e != 0 && *(unsigned short*) (e + 0x27) != 0xffff) {
				kind = *(char*) (g_7f4ca2 +
				                 *(unsigned short*) (e + 0x27) * 0x21c);
				if (kind == 6 || kind == 7) {
					io_FormatTextBuffer(nb, 0x414a, *(unsigned short*) entity, e);
					fcn_00545d40(*(int*) (g_7f4ca4 +
					                      *(unsigned short*) (*(int*) (entity + 0x16c) +
					                                          0x27) * 0x21c), -1, nb, 0, 0x60a,
					             g_6b5c60);
				}
			}
		}
		return g_6628a8;
	}
	v5 = *(int*) (entity + 0x2c);
	if (v5 != 0) {
		if ((v5 & 0xf) != 0) {
			if ((v5 & 0xf) == 1) {
				v5 &= 0xfffffff0;
			} else {
				v5 = (v5 & 0xfffffff0) | ((v5 >> 1) & 7);
			}
		}
		v6 = (v5 >> 4) & 0xf;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xffffff0f;
			} else {
				v5 = (v5 & 0xffffff0f) | ((v5 >> 1) & 0x70);
			}
		}
		v6 = (v5 >> 8) & 0xf;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xfffff0ff;
			} else {
				v5 = (v5 & 0xfffff0ff) | ((v5 >> 1) & 0x700);
			}
		}
		v6 = (v5 >> 0xc) & 3;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xffffcfff;
			} else {
				v5 = (v5 & 0xffffcfff) | ((v5 >> 1) & 0x1000);
			}
		}
		v6 = (v5 >> 0xe) & 7;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xfffe3fff;
			} else {
				v5 = (v5 & 0xfffe3fff) | ((v5 >> 1) & 0xc000);
			}
		}
		v6 = (v5 >> 0x11) & 7;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xfff1ffff;
			} else {
				v5 = (v5 & 0xfff1ffff) | ((v5 >> 1) & 0x60000);
			}
		}
		v6 = (v5 >> 0x14) & 7;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xff8fffff;
			} else {
				v5 = (v5 & 0xff8fffff) | ((v5 >> 1) & 0x300000);
			}
		}
		v6 = (v5 >> 0x17) & 3;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xfe7fffff;
			} else {
				v5 = (v5 & 0xfe7fffff) | ((v5 >> 1) & 0x800000);
			}
		}
		v6 = (v5 >> 0x19) & 0xf;
		if (v6 != 0) {
			if (v6 == 1) {
				v5 &= 0xe1ffffff;
			} else {
				v5 = (v5 & 0xe1ffffff) | ((v5 >> 1) & 0xe000000);
			}
		}
		fcn_004c5420(*(int*) (entity + 4), 0x2c, 4, v5, -1);
		g_773d48 += 1;
	}
	if ((*(unsigned char*) (entity + 0x1cc) & 2) != 0) {
		v10 = *(float*) (entity + 0x1c) -
		      (float) (int) ((gm_RandomMod(0x10) & 0xffff) + 0x11);
		fcn_004c4510(entity, *(int*) (entity + 4));
		cm_AppendPacketFieldDelta(4, 1, 0x1c, &v10);
		fcn_004c5360();
		g_773d48 += 1;
		if (v10 <= 0.0f) {
			c = 0;
			fcn_004c4510(entity, *(int*) (entity + 4));
			fcn_004c4700(1, 1, (char*) ((int) entity + (8 - (int) g_aed32c)),
			             &c);
			fcn_004c53a0();
			g_773d48 += 1;
			memset(msg, 0, sizeof(msg));
			msg[4] = 0x72;
			*(int*) (msg + 8) = *(int*) (entity + 4);
			*(int*) (msg + 0xc) = -1;


			msg[0x36] = 2;
			*(pos14_7f4c00*) (msg + 0x28) = gm_GameTime;

			*(int*) (msg + 0x58) = *(int*) (entity + 4);
			fcn_004c5530(msg);
			g_773d48 += 1;
			e = *(int*) (entity + 0x16c);
			if (e != 0 && *(unsigned short*) (e + 0x27) != 0xffff) {
				kind = *(char*) (g_7f4ca2 +
				                 *(unsigned short*) (e + 0x27) * 0x21c);
				if (kind == 6 || kind == 7) {
					io_FormatTextBuffer(nb, 0x1c51, e, *(unsigned short*) entity);
					fcn_00545d40(*(int*) (g_7f4ca4 +
					                      *(unsigned short*) (*(int*) (entity + 0x16c) +
					                                          0x27) * 0x21c), -1, nb, 0, 0x60a,
					             g_6b5c60);
					g_773d48 += 1;
				}
			}
		}
		return v10;
	}
	v15 = (float) *(unsigned short*) (entity + 0xa);
	if (v15 <= *(float*) (entity + 0x20)) {
		v10 = ((*(float*) (entity + 0x1c) - *(float*) (entity + 0x10)) /
		       *(float*) (entity + 0x20)) *
		          v15 +
		      *(float*) (entity + 0x10);
	} else {
		float adjusted;
		adjusted = *(float*) (entity + 0x14);
		if (*(int*) (entity + 0x170) != 0) {
			v4 = fcn_0050c710(*(int*) (entity + 0x170), 8, 1);
			adjusted = v4 * g_665370 * g_66444c + adjusted;
		}
		v10 = adjusted / *(float*) (entity + 0x1c);
		v10 += *(float*) (entity + 0x1c) - adjusted;
		fcn_004c4510(entity, *(int*) (entity + 4));
		cm_AppendPacketFieldDelta(4, 1, 0x1c, &v10);
		fcn_004c5360();
		g_773d48 += 1;
	}
	v11 = (double) *(int*) (entity + 0x24) + v10;
	v15 = (float) v11;
	if (v11 <= 0.0) {
		c = 0;
		if ((*(unsigned char*) (entity + 0x1cc) & 1) != 0 &&
		    *(char*) (entity + 2) != 6 && *(char*) (entity + 2) != 7) {
			float v14 = 0.0f;
			v10 = 100.0f;
			fcn_004c4510(entity, *(int*) (entity + 4));
			cm_AppendPacketFieldDelta(4, 1, 0x1c, &v10);
			cm_AppendPacketFieldDelta(4, 1, 0x24, &v14);
			fcn_004c5360();
			g_773d48 += 1;
			fcn_004c5420(*(int*) (entity + 4), 0x1cc, 4, 2, 0);
			g_773d48 = g_773d48 + 1;
			return v10;
		}
		fcn_004c4510(entity, *(int*) (entity + 4));
		fcn_004c4700(1, 1, (char*) ((int) entity + (8 - (int) g_aed32c)), &c);
		fcn_004c53a0();
		g_773d48 += 1;
		memset(msg, 0, sizeof(msg));
		msg[4] = 0x72;
		*(int*) (msg + 8) = *(int*) (entity + 4);
		*(int*) (msg + 0xc) = -1;

		msg[0x36] = 2;
		*(pos14_7f4c00*) (msg + 0x28) = gm_GameTime;


		*(int*) (msg + 0x58) = *(int*) (entity + 4);
		fcn_004c5530(msg);
		g_773d48 += 1;
		e = *(int*) (entity + 0x16c);
		if (e != 0 && *(unsigned short*) (e + 0x27) != 0xffff) {
			kind = *(char*) (g_7f4ca2 +
			                 *(unsigned short*) (e + 0x27) * 0x21c);
			if (kind == 6 || kind == 7) {
				if ((*(unsigned char*) (entity + 0x1cc) & 4) != 0) {
					io_FormatTextBuffer(nb, 0x4080, entity + 0x30, entity + 0x40,
					             *(unsigned short*) (entity + 0xa));
					fcn_00545d40(*(int*) (g_7f4ca4 +
					                      *(unsigned short*) (*(int*) (entity + 0x16c) +
					                                          0x27) * 0x21c), -1, nb, 0, 0x60a,
					             g_6964f0);
				} else {
					io_FormatTextBuffer(nb, 0x1c51, e, *(unsigned short*) entity);
					fcn_00545d40(*(int*) (g_7f4ca4 +
					                      *(unsigned short*) (*(int*) (entity + 0x16c) +
					                                          0x27) * 0x21c), -1, nb, 0, 0x60a,
					             g_6b5c60);
				}
				g_773d48 += 1;
			}
		}
		return g_6628a8;
	}
	fcn_004ff490(entity);
	if (v15 > 0.0) {
		v11 = v15;
	} else {
		v11 = 0.0;
	}
	w = *(unsigned short*) (entity + 0xa) + 1;
	fcn_004c4510(entity, *(int*) (entity + 4));
	cm_AppendPacketFieldDelta(2, 1, 10, &w);
	fcn_004c5360();
	g_773d48 = g_773d48 + 1;
	return v11;
}
