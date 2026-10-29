extern char* g_entity_type_table;
extern int g_773d70;

void __cdecl fcn_00506a70(void*);
void __cdecl fcn_005b2a00(void*, void*);
void __cdecl gm_FreeObjectListRecursive(int);
void __cdecl fcn_004030e0(int*);
int __cdecl fcn_0064d41a(char*, char*, ...);

/* ADDRESS: GOLDTL 0x00506ab0 */
void __cdecl gm_KillSpieler(int a0, int a1)
{
	char* e;
	int v4;
	int v12;
	char buf[512];
	char* ent;
	char* p;
	char* e2;
	int* v10;
	int* v8;
	unsigned int* v14;
	int v9;
	int v15;
	int v5;

	v12 = a0 * 0x21c;
	ent = (char*) 0x7f4ca0 + v12;
	v4 = *(int*) (ent + 4);
	if (ent[2] != 0x0f) {
		*(unsigned short*) (ent + 0x28) = *(unsigned short*) 0x7f4c00;
		ent[8] = 0;
		fcn_00506a70(ent);
		ent[2] = 0x0f;
		v9 = 0;
		e = 0;
		v15 = 0;
		p = (char*) 0x7f4ca2;
		do {
			if (*p == 0x06) {
				e = (char*) (v9 * 0x21c + 0x7f4ca0);
				break;
			}
			p += 0x21c;
			v9 += 1;
		} while ((int) p < 0x85a0a2);
		v9 = *(int*) (ent + 4);
		v10 = (int*) 0x9a3816;
		do {
			if (*v10 == v9) {
				v5 = *(int*) ((char*) v10 - 0x16);
				v8 = (int*) 0x99f800;
				do {
					if (v8[1] == v5) {
						if (e != 0 && *(int*) (e + 4) == *v8) {
							v15 += 1;
						}
						v8[1] = -1;
						*v8 = -1;
					}
					v8 += 2;
				} while ((int) v8 < 0x9a3800);
				v10[-1] = -1;
				*v10 = -1;
				*(int*) ((char*) v10 - 0x16) = -1;
			}
			v10 = (int*) ((char*) v10 + 0x2d);
		} while ((int) v10 < 0x9a9216);
		if (v15 != 0 && e != 0 && e != ent) {
			fcn_005b2a00(e, ent);
		}
	}
	gm_FreeObjectListRecursive((int) (ent + 0x178));
	if (*(int*) (ent + 0x184) != 0) {
		fcn_004030e0(*(int**) (ent + 0x184));
		*(int*) (ent + 0x184) = 0;
	}
	e2 = *(char**) (ent + 0x170);
	if (e2 != 0) {
		if (g_entity_type_table[*(unsigned char*) e2 * 0x24d] == 1 && *(unsigned char*) (e2 + 0x65) > 0) {
			e2[0x65] -= 1;
		}
		*(int*) (ent + 0x170) = 0;
	}
	*(int*) (ent + 0x16c) = 0;
	if (a1 != 0) {
		if (*(unsigned short*) ent != 0xffff) {
			g_773d70 -= 1;
		}
		v10 = (int*) 0x7f4cfc;
		do {
			v9 = 8;
			v8 = v10;
			do {
				if (*v8 == *(int*) (ent + 4)) {
					*v8 = -1;
				}
				v8 += 1;
				v9 -= 1;
			} while (v9 != 0);
			v10 += 0x87;
		} while ((int) v10 < 0x85a0fc);
		v10 = (int*) ent;
		for (v9 = 0; v9 < 0x87; v9++) {
			v10[v9] = 0;
		}
		v9 = 8;
		v14 = (unsigned int*) (0x7f4cfc + v12);
		*(unsigned short*) ent = 0xffff;
		*(int*) (0x7f4ca4 + v12) = -1;
		do {
			*v14 = 0xffffffff;
			v14 += 1;
			v9 -= 1;
		} while (v9 != 0);
		if (a1 != 1) {
			return;
		}
		fcn_0064d41a(buf, (char*) 0x699918, v4);
		return;
	}
	fcn_0064d41a(buf, (char*) 0x6998e0, v4);
}
