extern char g_7f4ca0[];
extern char* g_entity_type_table;

extern int __cdecl gm_LookupEntityRecordById(int);
extern int __cdecl gm_StartFilteredEntitySearch(int, int, int);
extern int __cdecl gm_ResolveEntityById(int*, int, int, int);
extern int __cdecl gm_FindRecordById(int);
extern int __cdecl fcn_005463a0(int, int, int);
extern int __cdecl gm_SearchTable67(int);
extern int __cdecl fcn_004e6a30(int);
extern void __cdecl fcn_004432d0(int, int);
extern void __cdecl fcn_005290d0(char*);
extern void __cdecl fcn_00573e10(char*);
extern void __cdecl fcn_00510100(void);


/* Reload the whole world state after a new game starts.  Every master record
 * of the type table is released and reallocated, the entity list is relinked
 * from the owner chains of the loaded objects, every live game object runs its
 * per-kind reset handler, and the remaining reference tables are rebuilt. */
/* ADDRESS: GOLDTL 0x00525670 */
unsigned int __cdecl fcn_00525670(void)
{
	char* p;
	char* obj;
	char* rec;
	int* q;
	int v3;
	int v4;
	int v5;
	int v6;
	int v7;
	int v8;
	int v9;
	unsigned char kind;

	*(int*) 0x773da8 = gm_LookupEntityRecordById(*(int*) 0x773da8);
	if (!*(int*) 0x773da8)
		return 0;
	*(int*) 0x773d78 = gm_StartFilteredEntitySearch(1, 5, 10);
	if (*(unsigned int*) 0x6a23ac > 0x10016) {
		for (p = (char*) 0x773db4; (int) p < 0x773dd4; p += 4)
			*(int*) p = gm_LookupEntityRecordById(*(int*) p);
	}
	for (p = g_7f4ca0; (int) p < 0x85a0a0; p += 0x21c) {
		if (*(short*) p != -1) {
			if (*(int*) (p + 0x16c) != -1)
				gm_ResolveEntityById((int*) (p + 0x16c), 0, 0, *(int*) (p + 0x16c));
			else
				*(int*) (p + 0x16c) = 0;
			if (*(int*) (p + 0x170) != -1)
				gm_ResolveEntityById((int*) (p + 0x170), 0, 0, *(int*) (p + 0x170));
			else
				*(int*) (p + 0x170) = 0;
			v9 = *(int*) (p + 0x17c);
			if (v9 != -1)
				*(int*) (p + 0x17c) = fcn_005463a0(1, 1, v9);
			else
				*(int*) (p + 0x17c) = 0;
			*(int*) (p + 0x184) = 0;
		}
	}
	for (v9 = 0; v9 < *(int*) 0x773d8c; v9++) {
		obj = (char*) (0x868054 + v9 * 0x43);
		if (*(char*) (*(int*) 0x99ec10 +
		               (unsigned int) *(unsigned short*) (v9 * 0x43 + 0x868054) * 0x41) == 0x1d)
			*(unsigned int*) (obj + 0x24) = 0;
		v5 = *(int*) (obj + 6);
		if (v5 != -1 && gm_ResolveEntityById(&v8, &v7, &v6, v5)) {
			if (v8) {
				v5 = *(int*) (v8 + 0x5d);
				if (v5) {
					for (v4 = *(int*) (v5 + 0x3f); v4; v4 = *(int*) (v4 + 0x3f))
						v5 = v4;
					goto chain;
				}
				*(int*) (v8 + 0x5d) = (int) obj;
			} else if (v7) {
				v5 = *(int*) (v7 + 0x14);
				if (v5) {
					for (v4 = *(int*) (v5 + 0x3f); v4; v4 = *(int*) (v4 + 0x3f))
						v5 = v4;
				chain:
					*(int*) (v5 + 0x3f) = (int) obj;
				} else {
					*(int*) (v7 + 0x14) = (int) obj;
				}
			} else {
				v5 = *(int*) (v6 + 0x178);
				if (v5) {
					for (v4 = *(int*) (v5 + 0x3f); v4; v4 = *(int*) (v4 + 0x3f))
						v5 = v4;
					goto chain;
				}
				*(int*) (v6 + 0x178) = (int) obj;
			}
		}
	}
	v3 = *(int*) 0x6b8010;
	fcn_004432d0(0, 0);
	for (p = (char*) 0x77e980; (int) p <= 0x7d197f; p += 0x14c) {
		kind = *(unsigned char*) p;
		if (!kind)
			continue;
		if (kind == 0x29 || kind == 0x2d || kind == 0x2f || kind == 0x11 || kind == 0x25 ||
		    kind == 5 || kind == 10 || kind == 0x26 || (*(unsigned char*) (p + 0x78) & 8)) {
			v9 = *(int*) (p + 0x70);
			if (v9) {
				*(int*) (p + 0x70) = 0;
				*(int*) 0x774964 = 2;
				if (kind == 0x11)
					*(unsigned char*) (p + 0xf0) &= 0xef;
				(*(void(__cdecl**)(char*)) (kind * 4 + 0x7dc440))(p);
				*(int*) 0x774964 = 0;
				*(int*) (p + 0x70) = v9;
			}
		}
		kind = *(unsigned char*) p;
		if (kind == 0xc)
			continue;
		if (kind == 0xd) {
			gm_ResolveEntityById(&v6, 0, 0, *(int*) (p + 0xb8));
			if (v6)
				fcn_00573e10(p);
			continue;
		}
		if (kind == 0xf) {
			v9 = gm_FindRecordById(*(int*) (p + 0x10));
			if (v9)
				*(char**) (v9 + 0x24) = p;
			continue;
		}
		if (kind == 0x78) {
			*(unsigned char*) (p + 0xc8) = 0;
			*(unsigned char*) (p + 0xc9) = 0;
			*(unsigned char*) (p + 0xca) = 0;
			*(unsigned char*) (p + 0xcb) = 0;
			*(unsigned char*) (p + 0xcc) = 0;
			*(unsigned char*) (p + 0xcd) = 0;
			*(unsigned char*) (p + 0xce) = 0;
			*(unsigned char*) (p + 0xcf) = 0;
			continue;
		}
		if (kind == 0x76) {
			*(unsigned char*) (p + 0xb0) = 0;
			*(unsigned char*) (p + 0xb1) = 0;
			*(unsigned char*) (p + 0xb2) = 0;
			*(unsigned char*) (p + 0xb3) = 0;
			continue;
		}
		if (kind == 0x14) {
			fcn_005290d0(p);
			*(unsigned char*) (p + 0xac) =
			    *(unsigned char*) (p + 0x14) + *(unsigned char*) (p + 0x18);
		}
	}
	fcn_004432d0(v3, 0);
	for (q = (int*) 0x7d2020; (int) q < 0x7dc420; q += 0x29) {
		v9 = *q;
		if (v9)
			*q = fcn_005463a0(1, 1, v9);
	}
	for (rec = (char*) 0xfb5766; (int) rec < 0x1005766; rec += 10) {
		v9 = *(int*) rec;
		if (v9) {
			if (*(char*) (rec - 5) == 1)
				*(int*) rec = gm_LookupEntityRecordById(v9);
			if (*(char*) (rec - 5) == 3)
				*(int*) rec = gm_FindRecordById(v9);
			if (*(char*) (rec - 5) == 2)
				*(int*) rec = gm_SearchTable67(v9);
			if (*(char*) (rec - 5) == 9)
				*(int*) rec = fcn_004e6a30(v9);
		}
	}
	fcn_00510100();
	return 1;
}
