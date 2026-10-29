typedef struct Slot {
	char* obj;
	int kind;
	char pad8[4];
	unsigned char done;
	char padd[0x13];
	unsigned int t;
	char pad24[0x100];
} Slot;
/* SIZE 0x124 */

extern int g_6b8010;
extern char g_7f4c00[];
extern unsigned char g_776664;
extern unsigned int g_6b7fac;
extern unsigned int g_7728f0;
extern int g_7728e4;
extern Slot* g_7728e8;
extern int g_7728ec;

int __cdecl fcn_00500e20(char*);
void __cdecl fcn_004432d0(int, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
double __cdecl gm_RandomFloat01(void);
Slot* __cdecl fcn_004bc010(void);
void __cdecl fcn_004bc060(Slot*);
void __cdecl fcn_004bc090(Slot*);
void __cdecl fcn_004bc1e0(Slot*);
void __cdecl fcn_004bc270(Slot*);
void __cdecl fcn_004bc2f0(Slot*);
void __cdecl fcn_004bc380(Slot*);
void __cdecl fcn_004bc410(Slot*, int);
void __cdecl fcn_004bc540(Slot*);
void __cdecl fcn_004bc6b0(Slot*);


/* Per-tick driver for the 32 ambient slots: may spawn one, then updates and
   retires the slot at the rotating cursor g_7728ec. */
/* ADDRESS: GOLDTL 0x004bbd70 */
void __cdecl fcn_004bbd70(void)
{
	int saved;
	int r;
	int lim;
	Slot* s;

	saved = g_6b8010;
	r = fcn_00500e20(g_7f4c00);
	fcn_004432d0(0, 1);
	if (g_776664 == 0) {
		lim = 0;
	} else {
		lim = g_776664 == 1 ? 0x10 : 0x20;
	}
	if (g_6b7fac > g_7728f0 + 0x15e) {
		if ((int) gm_RandomMod(lim * 2) - lim > g_7728e4 && r != 3) {
			s = fcn_004bc010();
			if (s != 0) {
				switch (gm_RandomMod(100) > 30 ? gm_RandomMod(5) + 3 : gm_RandomMod(2)) {
				case 1:
					fcn_004bc1e0(s);
					break;
				case 0:
					fcn_004bc270(s);
					break;
				case 4:
					fcn_004bc2f0(s);
					break;
				case 3:
					fcn_004bc380(s);
					break;
				case 6:
					fcn_004bc410(s, 6);
					break;
				case 7:
					fcn_004bc410(s, 7);
					break;
				}
			}
		}
		g_7728f0 = g_6b7fac;
	}
	s = &g_7728e8[g_7728ec];
	if (s->obj != 0) {
		switch (s->kind) {
		case 0:
		case 1:
			fcn_004bc540(s);
			break;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			fcn_004bc6b0(s);
			break;
		case 2:
			fcn_004bc090(s);
			break;
		}
		if (r == 3) {
			g_7728e8[g_7728ec].done = 1;
		}
		if (g_6b7fac > g_7728e8[g_7728ec].t + 0x834 &&
		    gm_RandomFloat01() > (g_7728e8[g_7728ec].t + 0x834) / (g_6b7fac - (g_7728e8[g_7728ec].t + 0x834))) {
			g_7728e8[g_7728ec].done = 1;
		}
		s = &g_7728e8[g_7728ec];
		if (s->done != 0 &&
		    ((*(unsigned char*) (*(char**) (*(char**) (s->obj + 0x34) + 0x1ec) + 0x163d) & 0x40) || r == 3 ||
		     g_7728e4 > lim)) {
			fcn_004bc060(s);
		}
	}
	fcn_004432d0(saved, 1);
	g_7728ec = (g_7728ec + 1) % 32;
}
unsigned char _dpad_775318[4940];
