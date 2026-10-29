#include <string.h>

/* Message object handed to fcn_004c5530: 0xf8 bytes, the stores pin
 * +0x04/+0x08/+0x0c/+0x36/+0x58/+0x5c/+0x60. */
typedef struct GOLDTL_Msg493 {
	int f0;                     /* 0x00 */
	unsigned char f4;           /* 0x04 */
	char pad5[3];
	int f8;                     /* 0x08 */
	int fc;                     /* 0x0c */
	char pad10[0x18];
	int f28;                    /* 0x28 */
	int f2c;                    /* 0x2c */
	int f30;                    /* 0x30 */
	unsigned short f34;         /* 0x34 */
	unsigned char f36;          /* 0x36 */
	char pad37[0x21];
	int f58;                    /* 0x58 */
	unsigned char f5c;          /* 0x5c */
	char pad5d[3];
	int f60;                    /* 0x60 */
	char pad64[0x94];
} GOLDTL_Msg493;                /* SIZE 0xf8 */

extern float g_664150;

void* __cdecl fcn_00508e40(unsigned int);
int __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl gm_MapEntityStatRange(unsigned char);
int __cdecl gm_WalkEntityChain(unsigned short);
unsigned char __cdecl fcn_00507400(int, int);
void __cdecl fcn_004c5530(GOLDTL_Msg493*);

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x00493f80 */
void __cdecl fcn_00493f80(void)
{
	int flags[0x300];
	GOLDTL_Msg493 msg;
	unsigned char* cand[5];
	int v25;
	unsigned char* e0;
	int i;
	int v28;
	int v29;
	unsigned char* rec;
	unsigned char* e1;
	unsigned char* chosen;
	unsigned char* best;
	int* slot;
	int* ap;
	int v6;
	int v7;
	int v8;
	int stat;
	int arg;

	memset(flags, 0, sizeof flags);
	rec = (unsigned char*) 0x7f4ca2;
	slot = flags;
	do {
		if (!*slot) {
			if (*(unsigned short*) (rec - 2) != 0xffff && rec[6]
			 && rec[0] < 10 && rec[0] != 6 && rec[0] != 7) {
				e0 = (unsigned char*) fcn_00508e40(*(unsigned int*) (rec + 0x5a));
				v29 = (e0[2] == 6 || e0[2] == 7);
				v25 = 0;
				ap = (int*) (rec + 0x66);
				for (i = 5; i != 0; i--) {
					e1 = (unsigned char*) fcn_00508e40(*ap);
					ap++;
					if (!e1) {
						continue;
					}
					if (v29) {
						flags[*(unsigned short*) e1] = 1;
					} else if (e1[8] == 0
					 || (float) (*(unsigned short*) (e1 + 0xa) + 3) < *(float*) (e1 + 0x20)
					 || e1[0x164]
					 || fcn_005463a0(2, 2, *(unsigned short*) e1, 0, 0x5e)) {
						v29 = 1;
						flags[*(unsigned short*) e1] = 1;
					} else {
						cand[v25] = e1;
						v25++;
					}
				}
				if (!v29 && v25) {
					rec -= 2;
					v6 = gm_MapEntityStatRange(rec[0x164]);
					v28 = gm_WalkEntityChain(*(unsigned short*) rec);
					v29 = (int) ((float) v28 * g_664150);
					v8 = gm_MapEntityStatRange(e0[0x164]);
					v28 = gm_WalkEntityChain(*(unsigned short*) e0);
					v7 = (int) ((float) v28 * g_664150);
					if (v6 && !v8) {
						chosen = rec;
						stat = v29;
						arg = v6;
					} else if (!v6 && v8) {
						chosen = e0;
						stat = v7;
						arg = v8;
					} else if (rec[2] == 5) {
						chosen = rec;
						stat = v29;
						arg = v6;
					} else if (e0[2] != 5 && !rec[9]) {
						chosen = rec;
						stat = v29;
						arg = v6;
					} else {
						chosen = e0;
						stat = v7;
						arg = v8;
					}
					if (stat <= 0x320) {
						stat = 0x320;
					}
					best = cand[0];
					flags[*(unsigned short*) best] = 1;
					i = 1;
					if (v25 > 1) {
						do {
							e1 = cand[i];
							flags[*(unsigned short*) e1] = 1;
							if (*(unsigned short*) (e1 + 0xa) > *(unsigned short*) (best + 0xa)) {
								best = e1;
							}
							i++;
						} while (i < v25);
					}
					msg.f36 = 0x11;
					msg.f4 = 0x5e;
					msg.f8 = *(int*) (best + 4);
					msg.fc = -1;
					msg.f58 = *(int*) (chosen + 4);
					msg.f5c = fcn_00507400(arg, 1);
					msg.f60 = stat;
					fcn_004c5530(&msg);
					rec += 2;
				}
				flags[*(unsigned short*) e0] = 1;
				flags[*(unsigned short*) (rec - 2)] = 1;
			} else {
				*slot = 1;
			}
		}
		rec += 0x21c;
		slot++;
	} while ((int) rec < 0x85a0a2);
}
