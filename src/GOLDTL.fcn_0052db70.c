extern int g_7f4c00;
extern int g_7f4c04;
extern int g_868050;
extern int g_6b8010;

int __cdecl fcn_00500e20(int*);
void __cdecl fcn_004432d0(int, int);
char* __cdecl fcn_00445600(int, int, int, char*);
void* __cdecl fcn_00426fd0(char*);
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
	h = g_6b8010;
	if (*(unsigned char*) (g_868050 + (unsigned char) *a0 * 0x24c) == 7 ||
	    *(int*) (a0 + 0x61) == 0) {
		return;
	}
	idx = 0;
	ent = (char*) 0x7f4ca0;
	do {
		if (*(unsigned char*) (ent + 8) > 0 && *(unsigned short*) ent != 0xffff &&
		    *(unsigned char*) (ent + 2) != 10 && *(int*) (ent + 0x16c) == (int) a0 &&
		    *(unsigned char*) (ent + 0x180) == 4) {
			found = (void*) *(int*) (idx * 0x21c + 0x7f4e1c);
			if (found != 0 && *(int*) ((char*) found + 0xc8) != 0) {
				break;
			}
			if (*(int*) (a0 + 0x95) != -1) {
				break;
			}
			ft = (float) (g_7f4c04 & 0xffff);
			if (ft < *(float*) (sel * 4 + 0x696540)) {
				return;
			}
			if (ft > *(float*) (sel * 4 + 0x696550)) {
				return;
			}
			fcn_004432d0(0, 1);
			obj = fcn_00445600(*(int*) (a0 + 0x61), 0x100, 0, "6a2f08");
			if (obj == 0) {
				goto unlock;
			}
			found = fcn_00426fd0("6a2ee8");
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
	} while ((int) ent < 0x85a0a0);
	if (*(int*) (a0 + 0x95) != -1) {
		p = fcn_00426cc0(*(int*) (a0 + 0x95));
		if (p != 0) {
			fcn_00428720((char*) p);
		}
		*(int*) (a0 + 0x95) = -1;
	}
}
