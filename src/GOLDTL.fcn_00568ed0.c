#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern float g_662910;
extern float g_6628a0;
extern float g_6628cc;
extern float g_662a3c;
extern double g_662908;
extern double g_6629c8;
extern double g_6653f8;
extern char* g_aed32c;

int __cdecl gm_RandomMod(int);
float __cdecl gm_RandomFloat01(void);
int __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(unsigned char, unsigned char, unsigned short, char*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c5530(int);
void __cdecl fcn_004c5c00(int, int, int, char*);
void __cdecl fcn_004c5c80(int);
int __cdecl fcn_004c5da0(int, int, int, char*, int, char*);
void __cdecl fcn_004c6b20(int, int, int);
float __cdecl fcn_004ff210(unsigned short, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
int __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl fcn_00503fe0(int, int, int);
char* __cdecl gm_SetupEntityQuery(char*);
char* __cdecl fcn_00504e70(int);
unsigned short* __cdecl fcn_00508e40(int);
int __cdecl fcn_0050c710(unsigned char*, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00529160(unsigned char*, char*, unsigned int, unsigned char*);
int __cdecl fcn_00529670(char*, char*);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl fcn_00546190(int);
int __cdecl fcn_005c6270(char*, int);

/* queued scene action handed to the packet builder */
/* SIZE 0xf8 */
typedef struct {
	char pad04[4];
	unsigned char kind;	/* +0x04 */
	char pad05[3];
	int who;		/* +0x08 */
	int target;		/* +0x0c */
	char pad10[0x18];
	pos14_7f4c00 when;	/* +0x28 */
	unsigned char flag;	/* +0x36 */
	char pad37[0x21];
	int ent;		/* +0x58 */
	int house;		/* +0x5c */
	char pad60[0x98];
} Msg_568ed0;

/* ADDRESS: GOLDTL 0x00568ed0 */

/* Runs the three-step trade window: open it, wait until a scene slot reports
 * the matching partner, then queue the packet for the selected house. */
void __cdecl fcn_00568ed0(char* a1)
{
	char buf[0x200];
	char* obj;
	char* ent;
	char* slot;
	char* hs;
	char* ent2;
	char* p;
	char* r;
	int i;
	int sel;
	int cnt;
	int n;
	int upto;
	int t;
	float total;

	i = sel = cnt = 0;
	switch (*(int*) (a1 + 0x70)) {
	case 0:
		obj = (char*) fcn_00503fe0(1, 1, *(int*) (a1 + 0xb0));
		if (obj == 0) {
			*(int*) (a1 + 0x70) = -1;
			return;
		}
		ent = (char*) gm_SetupEntityQuery(obj);
		if (ent == 0) {
			*(int*) (a1 + 0x70) = -1;
			return;
		}
		i = 8;
		p = a1 + 0x8c;
		do {
			if (*(int*) p != -1) {
				hs = (char*) fcn_00508e40(*(int*) p);
				fcn_00529160(0, 0, *(unsigned short*) hs, (unsigned char*) a1);
				fcn_004c5c80(*(int*) p);
				fcn_004c5da0(*(int*) p, *(int*) (obj + 1), *(int*) (ent + 2), 0, 1,
				             (char*) 0x6a69bc);
			}
			p += 4;
		} while (--i != 0);
		*(pos14_7f4c00*) (a1 + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (a1 + 0x52), 0, 0x1e, 0);
		*(int*) (a1 + 0x70) = 1;
		return;
	case 1:
		ent2 = (char*) fcn_00504e70(*(int*) (a1 + 0xb0));
		if (ent2 == 0) {
			*(int*) (a1 + 0x70) = -1;
			return;
		}
		for (i = 0; i < 8; i++) {
			if (*(int*) (a1 + 0x8c + i * 4) == -1) {
				continue;
			}
			hs = (char*) fcn_00508e40(*(int*) (a1 + 0x8c + i * 4));
			if (*(int*) (hs + 0x184) == 0) {
				continue;
			}
			if (fcn_00529670(hs, ent2) == 0) {
				goto used;
			}
		}
		*(pos14_7f4c00*) (a1 + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (a1 + 0x52), 0, 0, 1);
		*(int*) (a1 + 0x70) = 2;
		return;
	used:
		*(pos14_7f4c00*) (a1 + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (a1 + 0x52), 0, 0xa, 0);
		return;
	case 2:
		obj = (char*) fcn_00508e40(*(int*) (a1 + 0xac));
		slot = g_7f4ca0 + (unsigned short) *(unsigned short*) (a1 + 8) * 0x21c;
		hs = (char*) fcn_00508e40(*(int*) (slot + 4));
		ent = (char*) fcn_00503fe0(1, 1, *(int*) (a1 + 0xb4));
		if (ent == 0 || obj == 0 || hs == 0 || *(unsigned char*) (obj + 0x1b1) != 0) {
			*(int*) (a1 + 0x70) = -1;
			return;
		}
		ent2 = (char*) gm_SetupEntityQuery(ent);
		cnt = 0;
		total = 0;
		i = 8;
		p = a1 + 0x8c;
		do {
			if (*(int*) p != -1) {
				fcn_004c5c80(*(int*) p);
				fcn_004c5da0(*(int*) p, *(int*) (ent + 1), *(int*) (ent2 + 2), 0, 0,
				             (char*) 0x6a69bc);
				cnt++;
				r = (char*) fcn_00508e40(*(int*) p);
				total = total + (float) *(unsigned char*) (r + 0x83);
			}
			p += 4;
		} while (--i != 0);
		t = fcn_0050c710((unsigned char*) ent, 0xf, 1);
		sel = ((gm_RandomFloat01() + g_6628cc) <
		       (float) *(unsigned char*) (obj + 0x83) /
		       (((float) t * g_662910 + g_6629c8) *
		        ((float) cnt * g_662a3c + g_6628a0) * (total / (float) cnt)))
		      ? 1 : 0;
		if (fcn_005c6270(obj, 0x17c) != 0) {
			if (*(unsigned char*) (hs + 2) == 6 || *(unsigned char*) (hs + 2) == 7) {
				fcn_0051af00(buf, 0xff4);
				fcn_00545d40(*(int*) (hs + 4), -1, buf, 0, 0x5fa, 0);
			}
			*(int*) (a1 + 0x70) = -1;
			return;
		}
		if (sel != 0) {
			if (*(int*) (ent + 0x65) == -1) {
				r = (char*) fcn_00502cd0(*(int*) (ent + 0x5d), 1, 0, 0x65);
				if (*(int*) (obj + 0x184) != 0) {
					fcn_004c5c80(*(int*) (obj + 4));
					fcn_004c5c00(*(int*) (obj + 4), *(int*) (ent + 1), *(int*) (r + 2),
					             (char*) 0x6a69a8);
				}
			} else {
				*(int*) (a1 + 0x70) = -1;
				return;
			}
			if (*(unsigned char*) (hs + 2) == 6 || *(unsigned char*) (hs + 2) == 7) {
				fcn_0051af00(buf, 0x19bc, 0x19c1, *(unsigned short*) obj,
				             *(unsigned short*) obj, ent);
				he_MessageBoxQuickjump(*(int*) (hs + 4), *(int*) (hs + 4), buf, 0, 0x5fa,
				             *(int*) (ent + 1), *(int*) (r + 2), 0, (char*) 0x6a6994);
			}
			if (*(unsigned char*) (obj + 2) == 6 || *(unsigned char*) (obj + 2) == 7) {
				fcn_0051af00(buf, 0x19be);
				fcn_00545d40(*(int*) (obj + 4), *(int*) (obj + 4), buf, 0, 0x5fb,
				             (char*) 0x6a6980);
			}
			if (*(unsigned char*) (obj + 2) == 6 || *(unsigned char*) (obj + 2) == 5) {
				for (n = (int) (g_7f4ca0 + 4); n < 0x85a0a4; n += 0x21c) {
					if (*(unsigned char*) (n - 2) != 6 &&
					    *(unsigned char*) (n - 2) != 7) {
						continue;
					}
					if (*(int*) n == *(int*) (obj + 4) ||
					    *(int*) n == *(int*) (hs + 4)) {
						continue;
					}
					fcn_0051af00(buf, 0x19c0, *(unsigned short*) obj);
					fcn_00545d40(*(int*) n, -1, buf, 0, 0x5ec, (char*) 0x6a696c);
				}
			}
			fcn_004c4510(ent, *(int*) (ent + 1));
			fcn_004c4570(4, 1, (unsigned short) (ent - g_aed32c + 0x65), obj + 4);
			fcn_004c5360();
			fcn_004c6b20(*(int*) (obj + 4), 5, 0);
			{
				Msg_568ed0 msg = {0};

				msg.kind = 0x3d;
				msg.who = *(int*) (hs + 4);
				msg.target = *(int*) (hs + 4);
				msg.when = g_7f4c00;
				msg.flag = 0x12;
				msg.ent = *(int*) (obj + 4);
				msg.house = *(int*) (hs + 4);
				fcn_004c5530((int) &msg);
			}
		} else {
			if (*(unsigned char*) (hs + 2) == 6 || *(unsigned char*) (hs + 2) == 7) {
				fcn_0051af00(buf, 0x19bd, 0x19c1, *(unsigned short*) obj);
				fcn_00545d40(*(int*) (hs + 4), *(int*) (hs + 4), buf, 1, 0x5f0,
				             (char*) 0x6a6958);
			}
			if (*(unsigned char*) (obj + 2) == 6 || *(unsigned char*) (obj + 2) == 7) {
				fcn_0051af00(buf, 0x19bf, *(unsigned short*) hs);
				fcn_00545d40(*(int*) (obj + 4), *(int*) (obj + 4), buf, 1, 0x5fa, 0);
			}
		}
		p = a1 + 0x8c;
		for (i = 8; i != 0; i--) {
			if (*(int*) p != -1) {
				r = (char*) fcn_00508e40(*(int*) p);
				t = (int) *(float*) (r + 0x1c);
				upto = gm_RandomMod(t) & 0xffff;
				fcn_004ff210(*(unsigned short*) r,
				             (int) -((double) upto * g_6653f8 +
				                     (double) *(float*) (r + 0x1c) * g_662908));
			}
			p += 4;
		}
		p = a1 + 0x8c;
		for (i = 8; i != 0; i--) {
			if (*(int*) p != -1) {
				r = (char*) fcn_00508e40(*(int*) p);
				if (r != 0) {
					fcn_00529160((unsigned char*) ent, 0, *(unsigned short*) r, 0);
				}
			}
			p += 4;
		}
		fcn_00546190((int) a1);
		return;
	case -2:
	case -1:
		obj = (char*) fcn_00503fe0(1, 1, *(int*) (a1 + 0xb0));
		if (obj != 0) {
			i = (int) gm_SetupEntityQuery(obj);
		}
		p = a1 + 0x8c;
		n = 8;
		do {
			if (*(int*) p != -1) {
				hs = (char*) fcn_00508e40(*(int*) p);
				if (hs != 0) {
					fcn_004c5c80(*(int*) p);
					if (obj != 0) {
						if (i != 0) {
							fcn_004c5da0(*(int*) p, *(int*) (obj + 1),
							             *(int*) (i + 2), 0, 0, (char*) 0x6a69bc);
						}
						fcn_00529160((unsigned char*) obj, 0, *(unsigned short*) hs, 0);
					}
				}
			}
			p += 4;
		} while (--n != 0);
		fcn_00546190((int) a1);
		return;
	}
}
