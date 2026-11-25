#include "game_data.h"
typedef struct {
	short id;
	char pad2[0x16a];
	int f16c;
	int f170;
	char pad174[8];
	int f17c;
	char pad180[4];
	int f184;
	char pad188[0x21c - 0x188];
} Ent525670;
extern char g_7f4ca0[];
extern char* g_entity_type_table;
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern int __cdecl gm_LookupEntityRecordById(int);
extern int __cdecl gm_StartFilteredEntitySearch(int, int, int);
extern int __cdecl gm_ResolveEntityById(int*, int, int, int);
extern int __cdecl gm_FindRecordById(int);
extern int __cdecl he_StartHandlungSearch(int, int, int);
extern int __cdecl gm_SearchTable67(int);
extern int __cdecl cut_FindCutsceneById(int);
extern void __cdecl fcn_004432d0(int, int);
extern void __cdecl fcn_005290d0(char*);
extern void __cdecl fcn_00573e10(char*);
extern void __cdecl fcn_00510100(void);
extern char *gm_CityEntity, *g_773d78;
extern int ls_SaveVersion, g_773d8c;
/* Reload the whole world state after a new game starts.  Every master record
 * of the type table is released and reallocated, the entity list is relinked
 * from the owner chains of the loaded objects, every live game object runs its
 * per-kind reset handler, and the remaining reference tables are rebuilt. */
/* ADDRESS: GOLDTL 0x00525670 */
unsigned int __cdecl gm_RebuildLoadedReferences(void)
{
	char* p;
	char* r;
	Ent525670* e;
	char* obj;
	char* rec;
	int* q;
	int savedContext;
	int v5;
	int v8;
	int v7;
	int v6;
	int v9;

	gm_CityEntity = (char*) gm_LookupEntityRecordById((int) gm_CityEntity);
	if (!gm_CityEntity)
		return 0;
	g_773d78 = (char*) gm_StartFilteredEntitySearch(1, 5, 10);
	if (ls_SaveVersion >= 0x10017) {
		for (p = (char*) 0x773db4; (int) p < 0x773dd4; p += 4)
			*(int*) p = gm_LookupEntityRecordById(*(int*) p);
	}
	p = (char*) g_7f4ca0 + 0x170;
	do {
		e = (Ent525670*) (p - 0x170);
		if ((unsigned short) e->id != 0xffff) {
			if (e->f16c == -1)
				e->f16c = 0;
			else
				gm_ResolveEntityById(&e->f16c, 0, 0, e->f16c);
			if (e->f170 == -1)
				e->f170 = 0;
			else
				gm_ResolveEntityById(&e->f170, 0, 0, e->f170);
			v9 = e->f17c;
			if (v9 == -1)
				e->f17c = 0;
			else
				e->f17c = he_StartHandlungSearch(1, 1, v9);
			e->f184 = 0;
		}
	} while ((int) (p += 0x21c) < 0x85a210);
	v9 = 0;
		while (v9 < g_773d8c) {
		obj = (char*) (int) lpObjekteINST + v9 * 0x43;
		if (*(char*) ((int) &((OBJECT_PROTOTYPE *)lpObjektePROT)[
		               (unsigned int) *(unsigned short*) obj]) == 0x1d)
			*(unsigned int*) (obj + 0x24) = 0;
		v5 = *(int*) (obj + 6);
		if (v5 != -1 && gm_ResolveEntityById(&v8, &v7, &v6, v5)) {
			if (v8) {
				v5 = *(int*) (v8 + 0x5d);
				if (!v5) {
					*(int*) (v8 + 0x5d) = (int) obj;
				} else {
					while (*(int*) (v5 + 0x3f))
						v5 = *(int*) (v5 + 0x3f);
					*(int*) (v5 + 0x3f) = (int) obj;
				}
			} else if (v7) {
				v5 = *(int*) (v7 + 0x14);
				if (!v5) {
					*(int*) (v7 + 0x14) = (int) obj;
				} else {
					while (*(int*) (v5 + 0x3f))
						v5 = *(int*) (v5 + 0x3f);
					*(int*) (v5 + 0x3f) = (int) obj;
				}
			} else {
				v5 = *(int*) (v6 + 0x178);
				if (!v5) {
					*(int*) (v6 + 0x178) = (int) obj;
				} else {
					while (*(int*) (v5 + 0x3f))
						v5 = *(int*) (v5 + 0x3f);
					*(int*) (v5 + 0x3f) = (int) obj;
				}
			}
		}
		v9++;
	}
	savedContext = d3_CurrentContextIndex;
	fcn_004432d0(0, 0);
	for (r = (char*) 0x77e980; (int) r < 0x7d1980; r += 0x14c) {
		if (!*(unsigned char*) r)
			continue;
		if (*(unsigned char*) r == 0x29 || *(unsigned char*) r == 0x2d || *(unsigned char*) r == 0x2f ||
		    *(unsigned char*) r == 0x11 || *(unsigned char*) r == 0x25 || *(unsigned char*) r == 5 ||
		    *(unsigned char*) r == 10 || *(unsigned char*) r == 0x26 || (*(unsigned char*) (r + 0x78) & 8)) {
			v9 = *(int*) (r + 0x70);
			if (v9) {
				*(int*) (r + 0x70) = 0;
				g_774964 = 2;
				if (*(unsigned char*) r == 0x11)
					*(unsigned char*) (r + 0xf0) &= 0xef;
				(*(void(__cdecl**)(char*)) (*(unsigned char*) r * 4 + 0x7dc440))(r);
				g_774964 = 0;
				*(int*) (r + 0x70) = v9;
			}
		}
		if (*(unsigned char*) r == 0xc)
			continue;
		if (*(unsigned char*) r == 0xd) {
			gm_ResolveEntityById(&v6, 0, 0, *(int*) (r + 0xb8));
			if (v6)
				fcn_00573e10(r);
			continue;
		}
		if (*(unsigned char*) r == 0xf) {
			v9 = gm_FindRecordById(*(int*) (r + 0x10));
			if (v9)
				*(char**) (v9 + 0x24) = r;
			continue;
		}
		if (*(unsigned char*) r == 0x78) {
			*(int*) (r + 0xc8) = 0;
			*(int*) (r + 0xcc) = 0;
			continue;
		}
		if (*(unsigned char*) r == 0x76) {
			*(int*) (r + 0xb0) = 0;
			continue;
		}
		if (*(unsigned char*) r == 0x14) {
			fcn_005290d0(r);
			*(unsigned char*) (r + 0xac) =
			    *(unsigned char*) (r + 0x14) + *(unsigned char*) (r + 0x18);
		}
	}
	fcn_004432d0(savedContext, 0);
	for (q = (int*) 0x7d2020; (int) q < 0x7dc420; q += 0x29) {
		v9 = *q;
		if (v9)
			*q = he_StartHandlungSearch(1, 1, v9);
	}
	for (rec = (char*) 0xfb5766; (int) rec < 0x1005766; rec += 10) {
		v9 = *(int*) rec;
		if (v9) {
			if (*(char*) (rec - 5) == 1)
				*(int*) rec = gm_LookupEntityRecordById(v9);
			if (*(char*) (rec - 5) == 3)
				*(int*) rec = gm_FindRecordById(*(int*)rec);
			if (*(char*) (rec - 5) == 2)
				*(int*) rec = gm_SearchTable67(*(int*)rec);
			if (*(char*) (rec - 5) == 9)
				*(int*) rec = cut_FindCutsceneById(*(int*)rec);
		}
	}
	fcn_00510100();
	return 1;
}
