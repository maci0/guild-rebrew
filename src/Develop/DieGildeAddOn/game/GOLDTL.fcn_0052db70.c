extern int g_7f4c00;
extern int g_7f4c04;
extern int lpGebaeudePROT;
extern int g_6b8010;
extern unsigned char g_slot_table[2];

extern float g_696540[];
extern float g_696550[];

int __cdecl fcn_00500e20(int*);
void __cdecl fcn_004432d0(int, int);
char* __cdecl fcn_00445600(int, int, int, char*);
void* __cdecl evt_LoadGfxScript(char*);
void* __cdecl fcn_00426cc0(int);
char __cdecl fcn_00428720(char*);
void __cdecl fcn_00455350(char*, float*, float*);
int __cdecl fcn_00428340(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x0052db70 */
void __cdecl fcn_0052db70(char* a0)
{
	float v[4];
	char* ent;
	char* obj;
	void* found;
	int idx;
	int sel;
	int h;
	int p;
	float ft;

	sel = fcn_00500e20(&g_7f4c00);

	if (*(unsigned char*) (lpGebaeudePROT + (unsigned char) *a0 * 0x24d) == 7 ||
	    *(int*) (a0 + 0x61) == 0) {
		return;
	}
	idx = 0;
	ent = (char*) g_slot_table;
	do {
		if (*(unsigned char*) (ent + 8) > 0 && *(unsigned short*) ent != 0xffff &&
		    *(unsigned char*) (ent + 2) != 10 && *(int*) (ent + 0x16c) == (int) a0 &&
		    *(unsigned char*) (ent + 0x180) == 4) {
			found = *(void**) (g_slot_table + idx * 0x21c + 0x17c);
			if (found != 0 && *(int*) ((char*) found + 0xc8) != 0) {
				break;
			}
			if (*(int*) (a0 + 0x95) != -1) {
				return;
			}
			ft = (float) (g_7f4c04 & 0xffff);
			if (!(ft >= g_696540[sel])) {
				return;
			}
			if (!(ft < g_696550[sel])) {
				return;
			}
			h = g_6b8010; fcn_004432d0(0, 1);
			obj = fcn_00445600(*(int*) (a0 + 0x61), 0x100, 0, "dummy_RAUCH_0");
			if (obj == 0) {
				goto unlock;
			}
			found = evt_LoadGfxScript("effekte\\Schornstein_dunkel.esc");
			if (found == 0) {
				goto unlock;
			}
			fcn_00455350(obj, (float*) (obj + 0x4c), v);
			if (fcn_00428340((int) found, 3, (int) v[0], (int) v[1], (int) v[2]) != 0) {
				*(int*) (a0 + 0x95) = *(int*) ((char*) found + 0x100);
			}
			*(int*) ((char*) found + 0x104) = 0;
		unlock:
			fcn_004432d0(h, 1);
			return;
		}
		ent += 0x21c;
		idx++;
	} while ((int) ent < (int) g_slot_table + 0x65400);
	if (*(int*) (a0 + 0x95) != -1) {
		p = fcn_00426cc0(*(int*) (a0 + 0x95));
		if (p != 0) {
			fcn_00428720((char*) p);
		}
		*(int*) (a0 + 0x95) = -1;
	}
}
