void* __cdecl memset(void*, int, unsigned int);
#pragma intrinsic(memset)

/* SIZE 0x2c: event record passed to fcn_004c6940 */
typedef struct {
	unsigned int ent;
	unsigned int kind;
	unsigned int p8;
	unsigned int pc;
	unsigned int target;
	unsigned int p14;
	unsigned int p18;
	unsigned char busy;
	unsigned char done;
	char p1e[2];
	int hit;
	int amount;
	unsigned int p28;
} Ev_4d89c0;

extern int g_67a370;
extern char* g_772eb4;
extern int g_772f24;
extern int g_68b79c;
extern double g_6640e8;
extern float g_664144;

int __cdecl gm_RandomMod(int);
unsigned char __cdecl fcn_0045b990(int, int, int*, int*, int*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_004c5420(int, int, int, int, int);
int __cdecl fcn_004c6680(int, int, int, int);
int __cdecl fcn_004c6940(int, int, Ev_4d89c0*);
int __cdecl gm_GetEquippedCombatGear(int);
int __cdecl gm_FindEntityActiveItem(int);
int __cdecl gm_FindOrCreateEntitySlot(int, int);
int __cdecl fcn_004cec00(int, int, int*, int*);
float __cdecl fcn_004cefb0(int, unsigned int);
int __cdecl fcn_004d1020(int, int, int, int, int);
int __cdecl cut_RandMod(int);
int __cdecl fcn_005c6270(int, int);

/* ADDRESS: GOLDTL 0x004d89c0 */
unsigned int __cdecl fcn_004d89c0(int a0, unsigned int a1, int a2)
{
	Ev_4d89c0 ev;
	unsigned int v7;
	unsigned int roll;
	int actor;
	int* p;
	int v8;
	int v9;
	int w;
	int hit;
	int i;
	char v2;

	v7 = *(unsigned int*) (g_67a370 + 0xb0);
	memset(&ev, 0, sizeof(ev));
	ev.ent = *(unsigned int*) (a1 + 4);
	v2 = *(char*) (a1 + 0x1c4);
	actor = a1;
	ev.kind = 2;
	ev.target = *(unsigned int*) (a2 + 4);
	if (v2 == 1 || v2 == 2 || v2 == 3)
		ev.busy = 1;
	p = (int*) gm_GetEquippedCombatGear(a1);
	if ((p[0x16] == 1 || p[0x16] == 2)
	    && (w = gm_FindEntityActiveItem(actor)) != 0
	    && *(int*) (w + 0x20) <= 0)
		goto fail;
	v8 = p[0];
	if (v8 == 0x154 || v8 == 0x156 || v8 == 0x158 || v8 == 0x16e
	    || v8 == 0x172 || v8 == 0 || v8 == 0x176) {
		v9 = *(int*) (a2 + 0x184);
		if (*(float*) (p + 3) < fcn_004cefb0(actor, *(unsigned int*) (v9 + 0x34))) {
			if (*(int*) (*(int*) (actor + 0x184) + 0x128) != 0)
				goto fail;
			if (ev.busy)
				goto fail;
			if (fcn_0045b990(v7, *(int*) (v9 + 0x34) + 0x4c, (int*) &a1, &a2, &a0) == 0)
				goto fail;
			if (fcn_004cec00(a1, a2, (int*) &a1, &a2) == 0)
				goto fail;
			return fcn_004c6680(*(int*) (*(int*) (actor + 0x184) + 0x34), a1, a2, 0);
		}
	}
	if (*(int*) (*(int*) (actor + 0x184) + 0x128) != 0)
		goto fail;
	roll = (unsigned short) gm_RandomMod(0xff);
	a1 = *(unsigned char*) (actor + 0x83);
	v9 = *(int*) (actor + 0x16c);
	v8 = (int) (*((unsigned char*) p + 4) * 0.01 * (int) a1);
	if ((int) roll <= 0xff - v8) {
		hit = 0;
		ev.amount = 0;
	} else {
		hit = 1;
		ev.amount = (int) ((unsigned int) (cut_RandMod(*((unsigned char*) p + 6) - *((unsigned char*) p + 5))
		    + *((unsigned char*) p + 5)) * *(float*) (a2 + 0x1c) * 0.01);
	}
	if (v9 != 0 && fcn_005c6270(v9, 0x2b9))
		ev.amount = (int) (ev.amount * g_664144);
	ev.done = 1;
	ev.hit = hit;
	if (*(int*) (g_772f24 + 4) == g_68b79c && p[0x16] == 0) {
		v9 = 0;
		for (i = 0; i < *(unsigned char*) (g_772eb4 + 0x30); i++) {
			if (*(int*) (g_772eb4 + 0x34 + i * 4) != -1 && a0 != 0x9b0e20 + i * 0x35c) {
				v9 = 0x9b0e20 + i * 0x35c;
				break;
			}
		}
		v8 = gm_FindOrCreateEntitySlot(v9, a2);
		if (*(int*) (v8 + 8) == -1 || fcn_004c4450(*(int*) (v8 + 8))) {
			*(unsigned int*) (v8 + 8) = 0xffffffff;
			if (*(int*) (v8 + 4) == 0) {
				w = gm_FindEntityActiveItem(a2);
				if (w != 0 && *(int*) (w + 0x20) > 0)
					*(unsigned int*) (v8 + 8) = fcn_004d1020(v9, a2, actor, 0, 0);
			}
		}
	}
	fcn_004c5420(*(unsigned int*) (actor + 4), 0x1c8, 4, 0x20000000, 0);
	return fcn_004c6940(actor, 2, &ev);
fail:
	return 0xffffffff;
}
