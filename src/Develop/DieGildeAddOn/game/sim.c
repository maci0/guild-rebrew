extern char* g_773d44;
#include "../../Units/Error/error.h"
#include "rebrew_types.h"
#include "rebrew_globals.h"
#if !defined(REBREW_SERVER)
#include <io.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "Develop/Units/d2.v1/rgb.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#endif

extern unsigned char g_entity_type_bytes[1];
extern int __cdecl gm_RandomMod(unsigned short range);
unsigned int __cdecl gm_AllocSpieler(int p1, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
void __cdecl plt_TableLookup(unsigned int a, unsigned short* b);
unsigned short __cdecl sim_FindAndMatchParents(unsigned int param);
extern unsigned char g_slot_table[2];
/* 0x10035a05: the byte at +0x165 of each 0x21c-byte g_slot_table record. */
#define g_stat_b_array ((unsigned char*) g_slot_table + 0x165)
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);

#if !defined(REBREW_SERVER)
#if defined(REBREW_GOLD)
extern unsigned char* lpGebaeudeINST;
#endif
extern char gm_EntityAgeField[];
extern char gm_EntityAgeLimitField[];
extern int g_773d64;
extern int g_773d3c;
extern char g_67bd30[];
extern char g_67a930[];
extern RGB_COLOR g_100f1a0;
extern char g_1015da0[];
extern char g_696528[];
extern char g_67d940[];
extern char g_99f620[];
extern int g_99f624[9];
extern float g_99f644;
extern float g_99f648[8];
extern float g_99f668[8];
extern float flt_100_0;

typedef struct { int word[2]; } QUERY_LIMIT;

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3[6];
	unsigned char cls;
	unsigned short age;
	char padc[0x20 - 0xc];
	float years;
	char pad24[0x164 - 0x24];
	unsigned char group;
	unsigned char kind;
	char pad166[0x16c - 0x166];
	int home;
	char pad170[0x1c8 - 0x170];
	int flags;
	char pad1cc[0x21c - 0x1cc];
} Obj;

#pragma pack(push, 2)
typedef struct {
	int day;
	unsigned short hour;
	int min;
	int sec;
} Time;
// SIZE 0xe
#pragma pack(pop)

#pragma pack(push, 2)
typedef struct TIME_4FE140 {
	int day;
	unsigned short hour;
	int minute;
	int second;
} TIME_4FE140;
#pragma pack(pop)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int __cdecl gm_CheckEntityAgeLimit(int index);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_FindNextFilteredEntity(void);
int __cdecl gm_GetBuildingSlotLimits(int, int*);
void __cdecl d3_TransformPoint(int, int, float*);
int __cdecl gm_EntityClassCheck(int kind);
int __cdecl gm_IsInRange(int cls);
int __cdecl gm_GetEntityRelation(int a, int i);
int __cdecl gm_AllocClientSpieler(int a, int b, int c, int d, int e, int f, int g, int h);
int __cdecl init_SpawnBuildingCharacter(int, int, int, int, int);
int __cdecl d2_ReadBmp24Dimensions(char* path);
int __cdecl d2_LoadBmp24Surface(char* path);
int __cdecl shp_CreateSpriteFromSurface(int a, int b, int c, int d, int h, int e, int f);
void __cdecl d2_AppendShapeToBank(int o, int x);
void __cdecl m_FreeTracked(void*);
void __cdecl d2_ReleaseSurface(int h);
char* __cdecl m_alloc(int size, char* tag);
float __cdecl gm_GetEntityAge(int);
float __cdecl gm_GetEntityHealth(void*);
float __cdecl gm_GetEntityMaxHealth(void*);
#endif

/* Simulation entity records are 0x21c bytes, based at g_slot_table
 * (0x100358a0).  Fields used here: +0x00 slot id (0xffff = free),
 * +0x02 state byte, +0x04 entity id, +0x08 usable flag, +0x0a weight,
 * +0x20 float threshold, +0x68 five linked children.
 *
 * Records are addressed by byte offset into g_slot_table rather than
 * through a struct pointer.  Subscripting the array keeps the pure record
 * offset in a register and leaves the symbol as each access's displacement
 * (`lea ecx,[eax+eax*8]` / `shl ecx,2` / `cmp word[ecx+g_slot_table+0x0]`),
 * which is what the target does.  A struct pointer built from the address
 * of a scalar folds the final *4 into the SIB scale and adds the symbol
 * into the pointer instead, which cost every access in both scan loops. */
#define SIM_ENT_OFF(i) (((i) & 0xffff) * 0x21c)

/* Client-only family check (the Gold T&L client's sim order).  No server
 * function calls it, so /OPT:REF discards it; its absolute fixups still count
 * toward LINK's .reloc reservation. */
int __cdecl sim_IsUnrelated(unsigned char* entity)
{
	int id;
	int i;
	int j;
	int found;
	int count;
	unsigned char* e;

	if (entity[2] == 6 || entity[2] == 7) {
		return 0;
	}
	id = *(int*) (entity + 4);
	for (i = 0; i < 0x300; i++) {
		e = g_slot_table + i * 0x21c;
		found = 0;
		count = 0;
		if (*(int*) (e + 4) != id && (e[2] == 6 || e[2] == 7)) {
			if (*(int*) (e + 0x5c) == id || *(int*) (e + 0x60) == id || *(int*) (e + 0x64) == id) {
				return 0;
			}
			for (j = 0; j < 5; j++) {
				if (*(int*) (e + 0x68 + j * 4) == id) {
					found |= 1;
					count++;
				}
				else if (*(int*) (e + 0x68 + j * 4) != -1) {
					count++;
				}
			}
			if (found && count < 5) {
				return 0;
			}
		}
	}
	return 1;
}

/* Searches for matching parent entities by type and creates
 * family tree linkages. Used in citizen creation to find
 * compatible parents for stat inheritance. */


#if defined(REBREW_SERVER)
unsigned short __cdecl sim_FindAndMatchParents(unsigned int param)
{
	int weights[6];
	unsigned int off;
	unsigned int rnd;
	unsigned int count;
	unsigned short parentA;
	unsigned short parentB;
	int i;
	int j = 0;
	int k;
	float f1;
	float f2;

	weights[0] = 0x60;
	weights[1] = 0x4b;
	weights[2] = 0x28;
	weights[3] = 0x17;
	weights[4] = 9;
	weights[5] = 0;
	i = 0x300;
	for (; j < 0x10; j++) {
		rnd = gm_RandomMod(i);
		parentA = rnd;
		off = SIM_ENT_OFF(rnd);
		if (*(unsigned short*) &g_slot_table[off] == 0xffff) {
			i = i * 3 / 4;
			continue;
		}
		f1 = (float) *(unsigned short*) &g_slot_table[off + 0xa];
		if (g_slot_table[off + 0x2] < 6 && f1 >= *(float*) &g_slot_table[off + 0x20] &&
		    g_slot_table[off + 0x8] != 0) {
			count = 0;
			for (k = 0; k < 5; k++) {
				if (((int*) &g_slot_table[off + 0x68])[k] != -1) {
					count++;
				}
			}
			if ((int) ((gm_RandomMod(0x100) & 0xffff) + 1) < weights[count]) {
				goto done1;
			}
		} else {
			parentA = 0xffff;
		}
	}
done1:
	if (parentA == 0xffff) {
		return 0;
	}

	for (j = 0; j < 0x10; j++) {
		rnd = gm_RandomMod(i);
		parentB = rnd;
		off = SIM_ENT_OFF(rnd);
		if (*(unsigned short*) &g_slot_table[off] == 0xffff) {
			i = i * 3 / 4;
			continue;
		}
		f2 = (float) *(unsigned short*) &g_slot_table[off + 0xa];
		if (g_slot_table[off + 0x2] < 6 && f2 >= *(float*) &g_slot_table[off + 0x20] &&
		    g_slot_table[off + 0x8] != 0) {
			count = 0;
			for (k = 0; k < 5; k++) {
				if (((int*) &g_slot_table[off + 0x68])[k] != -1) {
					count++;
				}
			}
			if ((int) ((gm_RandomMod(0x100) & 0xffff) + 1) < weights[count]) {
				goto done2;
			}
		} else {
			parentB = 0xffff;
		}
	}
done2:
	if (parentB == 0xffff) {
		return 0;
	}

	return (unsigned short) gm_AllocSpieler(
		0,
		*(int*) &g_slot_table[SIM_ENT_OFF(parentA) + 0x4],
		*(int*) &g_slot_table[SIM_ENT_OFF(parentB) + 0x4],
		(int) param,
		0, 0, 0, 2);
}
#endif
#if !defined(REBREW_SERVER)
/* The T&L build of fcn_004ffd90 (SERVER 0x100151e0). The
 * Processor Pack code generator needs the weight test spelled as
 * !(f < w) to emit the reference's test ah,5 / jnp. */

/* ADDRESS: GOLDTL 0x004ffd90 */
/* ADDRESS: GOLD 0x004fd5c0 */
/* ADDRESS: GOLDDE 0x004eb7a0 */
unsigned short __cdecl sim_FindAndMatchParents(unsigned int param)
{
	int weights[6];
	unsigned int off;
	unsigned int rnd;
	unsigned int count;
	unsigned short parentA;
	unsigned short parentB;
	int i;
	int j = 0;
	int k;
	float f1;
	float f2;

	weights[0] = 0x60;
	weights[1] = 0x4b;
	weights[2] = 0x28;
	weights[3] = 0x17;
	weights[4] = 9;
	weights[5] = 0;
	i = 0x300;
	for (; j < 0x10; j++) {
		rnd = gm_RandomMod(i);
		parentA = rnd;
		off = SIM_ENT_OFF(rnd);
		if (*(unsigned short*) &((unsigned char*)gm_EntitySlotTable)[off] == 0xffff) {
			i = i * 3 / 4;
			continue;
		}
		f1 = (float) *(unsigned short*) &((unsigned char*)gm_EntitySlotTable)[off + 0xa];
		if (((unsigned char*)gm_EntitySlotTable)[off + 0x2] < 6 && !(f1 < *(float*) &((unsigned char*)gm_EntitySlotTable)[off + 0x20]) &&
		    ((unsigned char*)gm_EntitySlotTable)[off + 0x8] != 0) {
			count = 0;
			for (k = 0; k < 5; k++) {
				if (((int*) &((unsigned char*)gm_EntitySlotTable)[off + 0x68])[k] != -1) {
					count++;
				}
			}
			if ((int) ((gm_RandomMod(0x100) & 0xffff) + 1) < weights[count]) {
				goto done1;
			}
		} else {
			parentA = 0xffff;
		}
	}
done1:
	if (parentA == 0xffff) {
		return 0;
	}

	for (j = 0; j < 0x10; j++) {
		rnd = gm_RandomMod(i);
		parentB = rnd;
		off = SIM_ENT_OFF(rnd);
		if (*(unsigned short*) &((unsigned char*)gm_EntitySlotTable)[off] == 0xffff) {
			i = i * 3 / 4;
			continue;
		}
		f2 = (float) *(unsigned short*) &((unsigned char*)gm_EntitySlotTable)[off + 0xa];
		if (((unsigned char*)gm_EntitySlotTable)[off + 0x2] < 6 && !(f2 < *(float*) &((unsigned char*)gm_EntitySlotTable)[off + 0x20]) &&
		    ((unsigned char*)gm_EntitySlotTable)[off + 0x8] != 0) {
			count = 0;
			for (k = 0; k < 5; k++) {
				if (((int*) &((unsigned char*)gm_EntitySlotTable)[off + 0x68])[k] != -1) {
					count++;
				}
			}
			if ((int) ((gm_RandomMod(0x100) & 0xffff) + 1) < weights[count]) {
				goto done2;
			}
		} else {
			parentB = 0xffff;
		}
	}
done2:
	if (parentB == 0xffff) {
		return 0;
	}

	return (unsigned short) gm_AllocClientSpieler(
		0,
		*(int*) &((unsigned char*)gm_EntitySlotTable)[SIM_ENT_OFF(parentA) + 0x4],
		*(int*) &((unsigned char*)gm_EntitySlotTable)[SIM_ENT_OFF(parentB) + 0x4],
		(int) param,
		0, 0, 0, 2);
}
#endif

/* Client-only: whether an entity is younger than its adult age (discarded). */
int __cdecl sim_IsUnderage(int slot)
{
	unsigned int i;

	i = (unsigned int) slot & 0xffff;
	return *(unsigned short*) (g_slot_table + 0xa + i * 0x21c) < *(float*) (g_slot_table + 0x20 + i * 0x21c);
}

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLD 0x004fd7e0 */
/* ADDRESS: GOLDTL 0x004fffb0 */
/* ADDRESS: GOLDDE 0x004eb9c0 */
int __cdecl gm_CheckEntityAgeLimit(int index)
{
	unsigned short w;
	unsigned int slot;
	int v;

	slot = (unsigned int) index & 0xffff;
	w = *(unsigned short*) (gm_EntityAgeField + slot * 540);
	v = w;
	return v < *(float*) (gm_EntityAgeLimitField + slot * 540);
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x004ffff0 */
char* __cdecl gm_FindAvailableResidence(int unused, int nearEntity)
{
	char* e;
	char* best;
	char* list[0x10];
	float p1[4];
	float p2[4];
	float bestd;
	float d;
	int n;
	QUERY_LIMIT selected, current;
	int best_n;

	best = 0;
	bestd = 1e8f;
	gm_GetBuildingSlotLimits(1, selected.word);
	e = gm_StartFilteredEntitySearch(1, 5, 1);
	if (e != 0) {
		best_n = selected.word[0];
		do {
			gm_GetBuildingSlotLimits(*(unsigned char*) e, current.word);
			n = current.word[0];
			if ((unsigned short) *(unsigned char*) (e + 0x65) < (unsigned short) current.word[0]
			    && (*(unsigned char*) (e + 0x5a) & 1) == 0) {
				if (nearEntity != 0 && *(int*) (nearEntity + 0x61) != 0 && *(int*) (e + 0x61) != 0) {
					d3_TransformPoint(*(int*) (e + 0x61), *(int*) (e + 0x61) + 0x4c, p1);
					d3_TransformPoint(*(int*) (nearEntity + 0x61), *(int*) (nearEntity + 0x61) + 0x4c, p2);
					p1[0] = p1[0] - p2[0];
					p1[1] = p1[1] - p2[1];
					p1[2] = p1[2] - p2[2];
					d = sqrt(p1[0] * p1[0] + p1[1] * p1[1] + p1[2] * p1[2]);
					if (d < bestd) {
						selected.word[1] = current.word[1];
						best_n = n;
						best = e;
						bestd = d;
					}
				} else if (best != 0) {
					if ((float) *(unsigned char*) (e + 0x65) / (float) (n & 0xffff)
					    < (float) *(unsigned char*) (best + 0x65) / (float) (best_n & 0xffff)) {
						best = e;
					}
				} else {
					selected.word[1] = current.word[1];
					best_n = n;
					best = e;
				}
			}
			e = gm_FindNextFilteredEntity();
		} while (e != 0);
		if (best != 0) {
			return best;
		}
	}
	e = gm_StartFilteredEntitySearch(1, 5, 0x16);
	memset(list, 0, sizeof(list));
	n = 0;
	while (e != 0 && (*(unsigned char*) (e + 0x5a) & 1) == 0 && n < 0x10) {
		list[n] = e;
		n++;
		e = gm_FindNextFilteredEntity();
	}
	return list[gm_RandomMod((unsigned short) n) & 0xffff];
}
#endif

/* Updates entity priority/scheduling. Called during simulation
 * tick to adjust entity processing order based on game state. */


/* ADDRESS: GOLDDE 0x004ebbf0 */
/* ADDRESS: SERVERDE 0x10013e80 */
void __cdecl sim_PriorityUpdate(char* ctx, char* entity)
{
	unsigned short tmp[4];
	char* old;

	plt_TableLookup((unsigned char) entity[0], tmp);
	if ((unsigned short) (unsigned char) entity[0x65] < tmp[0]) {
		old = *(char**) (ctx + 0x170);
		if (old != 0) {
			if ((unsigned char) old[0x65] > 0)
				old[0x65]--;
		}
		*(char**) (ctx + 0x170) = entity;
		entity[0x65]++;
	}
}

/* Client-only: claims a free, adult resident of `kind` (or of `group`) that
 * gets on with `who`'s household (discarded). */
unsigned char* __cdecl sim_ClaimResident(char* who, int kind, int group)
{
	int __cdecl gm_EntityClassCheck(int kind);
	int __cdecl gm_IsInRange(int group);
	int __cdecl gm_GetRelationship(int a, int b);
	unsigned char* e;
	int i;
	int c;

	if (kind != 0) {
		for (i = 0; i < 0x300; i++) {
			e = g_slot_table + i * 0x21c;
			if (*(unsigned short*) e != 0xffff && !(*(int*) (e + 0x1c8) & 0x2000) && e[2] <= 1 &&
			    (e[0x165] == kind || e[0x165] == 0) && *(int*) (e + 0x16c) == 0 &&
			    (float) *(unsigned short*) (e + 0xa) >= *(float*) (e + 0x20) && e[0x164] == group) {
				c = gm_EntityClassCheck(kind);
				if ((c == 2 || e[9] == c) &&
				    (*(unsigned short*) (who + 0x27) == 0xffff ||
				     gm_GetRelationship(*(unsigned short*) (who + 0x27), i) > -30)) {
					*(int*) (e + 0x1c8) |= 0x2000;
					return e;
				}
			}
		}
		return 0;
	}
	if (group == 0) {
		return 0;
	}
	c = gm_IsInRange((unsigned char) group);
	for (i = 0; i < 0x300; i++) {
		e = g_slot_table + i * 0x21c;
		if (*(unsigned short*) e != 0xffff && !(*(int*) (e + 0x1c8) & 0x2000) && e[2] <= 1 && e[0x164] == group &&
		    *(int*) (e + 0x16c) == 0 && (c == 2 || e[9] == c) &&
		    (*(unsigned short*) (who + 0x27) == 0xffff || gm_GetRelationship(*(unsigned short*) (who + 0x27), i) > -30)) {
			*(int*) (e + 0x1c8) |= 0x2000;
			return e;
		}
	}
	/* placeholder: inferred server log call, see msvc6-link-layout 5f */
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\sim.c", __LINE__, "sim_ClaimResident(): no free resident found", 1);
	return 0;
}

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLDTL 0x00500240 */
/* ADDRESS: GOLD 0x004fda70 */
/* ADDRESS: GOLDDE 0x004ebc50 */
Obj* __cdecl gm_FindAndReserveEntity(char* who, int kind, int group)
{
	int i;
	int c;

	if (kind != 0) {
		for (i = 0; i < 768; i++) {
			if (((Obj*)gm_EntitySlotTable)[i].id != 0xffff && !(((Obj*)gm_EntitySlotTable)[i].flags & 0x2000) && ((Obj*)gm_EntitySlotTable)[i].type <= 1 &&
			    (((Obj*)gm_EntitySlotTable)[i].kind == kind || ((Obj*)gm_EntitySlotTable)[i].kind == 0) && ((Obj*)gm_EntitySlotTable)[i].home == 0 &&
			    (float) ((Obj*)gm_EntitySlotTable)[i].age >= ((Obj*)gm_EntitySlotTable)[i].years && ((Obj*)gm_EntitySlotTable)[i].group == group) {
				c = gm_EntityClassCheck(kind);
				if ((c == 2 || ((Obj*)gm_EntitySlotTable)[i].cls == c) &&
				    (*(unsigned short*) (who + 0x27) == 0xffff ||
				     gm_GetEntityRelation(*(unsigned short*) (who + 0x27), i) > -30)) {
					goto found;
				}
			}
		}
		return 0;
	}
	if (group == 0) {
		return 0;
	}
	c = gm_IsInRange((unsigned char) group);
	for (i = 0; i < 768; i++) {
		if (((Obj*)gm_EntitySlotTable)[i].id != 0xffff && !(((Obj*)gm_EntitySlotTable)[i].flags & 0x2000) && ((Obj*)gm_EntitySlotTable)[i].type <= 1 &&
		    ((Obj*)gm_EntitySlotTable)[i].group == group && ((Obj*)gm_EntitySlotTable)[i].home == 0 && (c == 2 || ((Obj*)gm_EntitySlotTable)[i].cls == c) &&
		    (*(unsigned short*) (who + 0x27) == 0xffff || gm_GetEntityRelation(*(unsigned short*) (who + 0x27), i) > -30)) {
			goto found;
		}
	}
	return 0;
found:
	((Obj*)gm_EntitySlotTable)[i].flags |= 0x2000;
	return &((Obj*)gm_EntitySlotTable)[i];
}
#endif

/* Starts an entity query filtered by type byte from arg1.
 * Dispatches entity iteration across buildings, citizens, or
 * other entity categories based on the type selector. */


/* ADDRESS: GOLDDE 0x004ebdf0 */
/* ADDRESS: SERVERDE 0x10013ee0 */
unsigned short* __cdecl sim_StartEntityQueryByType(unsigned char* arg1)
{
	unsigned short* result = 0;
	unsigned char cls;
	unsigned char* base;
	unsigned char* slot;
	unsigned int idx;
	unsigned int off;

	/* The function returns the query handle, and that is what produced the
	 * `xor eax,eax` that ten earlier probing rounds chased as a constant-0
	 * argument.  eax holds the fall-through return value 0, materialised
	 * before the dispatch; the cls==1 arm reuses that still-live register for
	 * its third argument (`push eax`) while the three later arms, whose eax
	 * was clobbered by the preceding call, push the literal.  The extra live
	 * value across all four calls is also what forces the second callee-saved
	 * register (edi) the target saves.  Nothing about the argument spelling
	 * was ever reachable; the signature was wrong.
	 *
	 * Prior rounds measured a ceiling of 18/145 on the void signature and
	 * logged the zero argument as unreachable; that conclusion was an artefact
	 * of the missing return value.  Also confirmed while closing this: the
	 * volatile record read gives the target's `lea` + `mov cl,[ecx]` pair where
	 * a plain read folds into a scaled `mov cl,[edi+ecx*4]`, and the table must
	 * be read as a plain pointer, not through a volatile alias, or
	 * `mov ecx,[esp+4]` sinks below `push edi`. */
	idx = arg1[0];
	base = (unsigned char*) g_entity_type_table + idx;
	off = idx * 588;
	slot = base + off;
	cls = *(volatile unsigned char*) slot;
	if (cls == 1) {
		result = gm_ff_Objekt(*(int*) (arg1 + 0x5d), 1, 0, 0x12);
	} else if (cls == 2) {
		result = gm_ff_Objekt(*(int*) (arg1 + 0x5d), 1, 0, 0x13);
	} else if (cls == 0x1d) {
		result = gm_ff_Objekt(*(int*) (arg1 + 0x5d), 1, 0, 0xfd);
	} else if (cls == 0x16) {
		result = gm_ff_Objekt(*(int*) (arg1 + 0x5d), 1, 0, 0x120);
	}
	return result;
}

/* Client-only: the entity's service building, else the next market, mill or
 * tavern after the last one handed out (cursor kept at TL 0x773d64, the last
 * dword of the server's unnamed 0x10035410 block).  Discarded. */
char* __cdecl sim_NextServiceBuilding(char* entity, int* id, int* sub)
{
	extern char g_gap_10035410[28];
	unsigned short* query;
	unsigned char* type;
	int k;
	int n;

	n = 0xff;
	if (*(char**) (entity + 0x170) != 0) {
		query = sim_StartEntityQueryByType(*(unsigned char**) (entity + 0x170));
		*sub = query != 0 ? *(int*) ((char*) query + 2) : -1;
		*id = *(int*) (*(char**) (entity + 0x170) + 1);
		return *(char**) (entity + 0x170);
	}
	k = *(int*) (g_gap_10035410 + 0x18);
	do {
		if (g_entity_ptr[k * 0xa9] != 0) {
			type = (unsigned char*) g_entity_type_table + g_entity_ptr[k * 0xa9] * 0x24d;
			if (*type == 3 || *type == 0x16 || *type == 0xf) {
				*(int*) (g_gap_10035410 + 0x18) = k + 1;
				*sub = -1;
				*id = *(int*) (g_entity_ptr + k * 0xa9 + 1);
				return (char*) g_entity_ptr + k * 0xa9;
			}
		}
		k = (k + 1) % 0x100;
	} while (--n != 0);
	return 0;
}

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLDTL 0x00500480 */
/* ADDRESS: GOLD 0x004fdcb0 */
/* ADDRESS: GOLDDE 0x004ebe90 */
char* __cdecl gm_FindFallbackPublicBuilding(char* entity, int* id, int* sub)
{
	char* found_ent;
	int idx;
	int rem;
	char* proto;

	rem = 255;
	if (*(char**) (entity + 0x170) != 0) {
		found_ent = (char*) sim_StartEntityQueryByType(*(unsigned char**) (entity + 0x170));
		if (found_ent != 0) {
			*sub = *(int*) (found_ent + 2);
		} else {
			*sub = -1;
		}
		*id = *(int*) (*(char**) (entity + 0x170) + 1);
		return *(char**) (entity + 0x170);
	}
	idx = g_773d64;
	do {
		if (((char*)lpGebaeudeINST)[idx * 169] != 0) {
			proto = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned char)((char*)lpGebaeudeINST)[idx * 169]];
			if (*proto == 3 || *proto == 0x16 || *proto == 0xf) {
				g_773d64 = idx + 1;
				*sub = -1;
				*id = *(int*) (((char*)lpGebaeudeINST) + idx * 169 + 1);
				return ((char*)lpGebaeudeINST) + idx * 169;
			}
		}
		idx = (idx + 1) % 256;
	} while (--rem != 0);
	return 0;
}
#endif

/* Creates a new citizen entity with initial stats generated
 * from parent entities. Allocates entity memory, assigns random
 * stats via gm_AllocSpieler, and links to home. */


void* __cdecl sim_CreateCitizen(unsigned char flags, int citizen_type, int parent_id, unsigned char stat_a, unsigned char stat_b)
{
	unsigned int new_entity_slot;

	if ((flags & 1) != 0) {
		new_entity_slot = sim_FindAndMatchParents(parent_id) & 0xffff;
		if (new_entity_slot == 0xffff) {
			goto error;
		}
		if ((flags & 2) != 0) {
			g_stat_b_array[new_entity_slot * 0x21c] = stat_b;
			g_entity_type_bytes[new_entity_slot * 0x21c] = stat_a;
		}
	}
	else {
		new_entity_slot =
			gm_AllocSpieler(citizen_type, -1, -1, parent_id, 0, (unsigned int) stat_a, (unsigned int) stat_b, 2) &
			0xffff;
	}
	if (new_entity_slot == 0xffff) {
		goto error;
	}
	return g_slot_table + new_entity_slot * 0x21c;
error:
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\sim.c",
		0x127d,
		"sim_CreateCitizen(): could not alloc spieler",
		1
	);
	return (void*) 0;
}

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x00500580 */
/* ADDRESS: GOLDDE 0x004ebf90 */
char* __cdecl sim_CreateCitizenClient(unsigned char flags, int a2, int a3, int a4, int a5,
	char* queryEntity)
{
	int i;
	char* rec;
	char* s;

	if (flags & 1) {
		i = sim_FindAndMatchParents(a3) & 0xffff;
		if (i != 0xffff && (flags & 2)) {
			*(char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].active = (char) a5;
			*(char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].stat_category = (char) a4;
		}
	} else {
		i = gm_AllocClientSpieler(a2, -1, -1, a3, 0, a4 & 0xff, a5 & 0xff, 2)
			& 0xffff;
	}
	if (i == 0xffff) {
		return 0;
	}
	rec = ((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i]);
	if (!(flags & 4)) {
		return rec;
	}
	{
		if (queryEntity != 0) {
			s = (char*) sim_StartEntityQueryByType((unsigned char*) queryEntity);
			if (s != 0) {
				init_SpawnBuildingCharacter(*(int*) (rec + 4), *(int*) (queryEntity + 1),
					*(int*) (s + 2), 0, 0);
			}
		}
	}
	return rec;
}
#endif

#if defined(REBREW_SERVER)
/* Client-only: calls `visit` for every file below `dir` (discarded). */
void __cdecl sim_WalkDirectory(char* dir, int arg, void (__cdecl* visit)(char* path))
{
	struct SIM_FINDDATA {
		unsigned attrib;
		long time_create;
		long time_access;
		long time_write;
		unsigned long size;
		char name[260];
	};
	long __cdecl _findfirst(const char* spec, struct SIM_FINDDATA* data);
	int __cdecl _findnext(long handle, struct SIM_FINDDATA* data);
	int __cdecl _findclose(long handle);
	char* __cdecl strcpy(char* dst, const char* src);
	char* __cdecl strcat(char* dst, const char* src);
	int __cdecl strcmp(const char* a, const char* b);
	char path[0x100];
	struct SIM_FINDDATA fd;
	long h;

	strcpy(path, dir);
	strcat(path, "*");
	h = _findfirst(path, &fd);
	if (h == -1) {
		/* placeholder: inferred server log call, see msvc6-link-layout 5f */
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\sim.c", __LINE__, "sim_WalkDirectory(): Can't open directory", 1);
		return;
	}
	do {
		if (strcmp(fd.name, ".") != 0 && strcmp(fd.name, "..") != 0) {
			if (fd.attrib & 0x10) {
				strcpy(path, dir);
				strcat(path, fd.name);
				strcat(path, "\\");
				sim_WalkDirectory(path, arg, visit);
			}
			else {
				strcpy(path, dir);
				strcat(path, fd.name);
				if (visit != 0) {
					visit(path);
				}
			}
		}
	} while (_findnext(h, &fd) == 0);
	_findclose(h);
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x00500660 */
void __cdecl sim_WalkDirectoryClient(char* dir, int arg, void (__cdecl* visit)(char*))
{
	char path[0x100];
	struct _finddata_t fd;
	long h;

	strcpy(path, dir);
	strcat(path, "*");
	h = _findfirst(path, &fd);
	if (h == -1) {
		return;
	}
	do {
		if (strcmp(fd.name, ".") != 0 && strcmp(fd.name, "..") != 0) {
			if (fd.attrib & _A_SUBDIR) {
				strcpy(path, dir);
				strcat(path, fd.name);
				strcat(path, "\\");
				sim_WalkDirectoryClient(path, arg, visit);
			} else {
				strcpy(path, dir);
				strcat(path, fd.name);
				if (visit != 0) {
					visit(path);
				}
			}
		}
	} while (_findnext(h, &fd) == 0);
	_findclose(h);
}

/* ADDRESS: GOLDTL 0x005007f0 */
void __cdecl sim_CountBmpFiles(char* path)
{
	if (strstr(path, g_67bd30) != 0 || strstr(path, g_67a930) != 0) {
		g_773d40++;
	}
}

/* ADDRESS: GOLDTL 0x00500830 */
void __cdecl sim_LoadBmpShape(char* path)
{
	int k;
	int h;
	int o;
	char* d;

	k = d2_ReadBmp24Dimensions(path);
	if (k == -1) {
		return;
	}
	h = d2_LoadBmp24Surface(path);
	if (h == 0) {
		return;
	}
	o = shp_CreateSpriteFromSurface(0, 0, k & 0xffff, k >> 16, h, 0, 1);
	if (o != 0) {
		d2_AppendShapeToBank(o, g_773d3c);
		m_FreeTracked((void*) o);
		strcpy(g_773d44 + g_773d40 * 0x30, strrchr(path, '\\') + 1);
		d = strrchr(g_773d44 + g_773d40 * 0x30, '.');
		if (d != 0) {
			*d = 0;
		}
		g_773d40++;
	}
	d2_ReleaseSurface(h);
}
#endif

#if !defined(REBREW_SERVER)
/* ADDRESS: GOLDTL 0x00500900 */
/* ADDRESS: GOLD 0x004fde90 */
/* ADDRESS: GOLDDE 0x004ec070 */
void __cdecl init_LoadCharacterNames(void)
{
	char path[260];
	char line[260];
	FILE* f;

	g_100f1a0.g = 0xff;
	g_100f1a0.r = 0;
	g_100f1a0.b = 0;
	g_773d40 = 0;
	sprintf(path, g_696528, g_1015da0);
	f = fopen(path, g_6750e8);
	if (f != 0) {
		do {
			fread(line, 0x80, 1, f);
			g_773d40++;
		} while (!feof(f));
		fclose(f);
	}
	g_773d44 = m_alloc(g_773d40 * 48, g_67d940);
	g_773d40 = 0;
	f = fopen(path, g_6750e8);
	if (f != 0) {
		do {
			fread(line, 0x80, 1, f);
			strcpy(g_773d44 + g_773d40++ * 48, line);
		} while (!feof(f));
		fclose(f);
	}
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x00500a20 */
/* ADDRESS: GOLDDE 0x004ec190 */
void __cdecl gm_FreeBuffer773d44(void)
{
	if (*(int*) &g_773d44 != 0) {
		m_FreeTracked((void*) *(int*) &g_773d44);
		*(int*) &g_773d44 = 0;
	}
}
#endif

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004fdfb0 */
void __cdecl gm_FreeBuffer773d44(void)
{
	int h;
	h = *(int*) 0x6f1b94;
	if (h != 0) {
		m_FreeTracked((void*) h);
		*(int*) 0x6f1b94 = 0;
	}
}
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
/* ADDRESS: GOLDTL 0x00500a40 */
/* ADDRESS: GOLDDE 0x004ec1b0 */
void __cdecl gm_CollectPopulationStats(void)
{
	char* p;
	int i;
	int idx;

	p = gm_EntitySlotTable;
	memset(g_99f620, 0, 0x68);
	i = 0;
	do {
		if (*(short*) p != -1
		    && *(unsigned char*) (p + 8) > 0
		    && *(unsigned char*) (p + 2) < 0xa) {
			*(int*) &g_99f620[0] += 1;
			idx = (int) MAX(MIN(gm_GetEntityAge(i) * 0.1f, 7.0f), 0.0f);
			g_99f624[idx] += 1;
			if (gm_CheckEntityAgeLimit(i) != 0)
				g_99f644 += 1.0f;
			g_99f648[idx] += gm_GetEntityHealth(p);
			g_99f668[idx] += gm_GetEntityMaxHealth(p);
		}
		p += 0x21c;
		i++;
	} while ((int) p < 0x85a0a0);
	for (p = g_99f620 + 0x48; (int) p < (int) (g_99f620 + 0x68); p += 4) {
		*(float*) (p - 0x20) = (*(float*) (p - 0x20) / *(float*) p) * flt_100_0;
		*(float*) p = *(float*) p / (float) *(int*) (p - 0x44);
	}
	g_99f644 = (g_99f644 / (float) *(int*) &g_99f620[0]) * flt_100_0;
}
#endif

/* Advances the game clock by one tick. Updates day/hour/minute
 * counters, triggers periodic events (taxes, production cycles),
 * and notifies connected clients of time changes. */


#pragma pack(push, 1)
// SIZE 0xe
typedef struct {
	int x00;             /* +0x00 */
	unsigned short x04;  /* +0x04 */
	int x06;             /* +0x06 */
	int x0a;             /* +0x0a */
} SIM_CLOCK;
#pragma pack(pop)

#if defined(REBREW_SERVER)
#pragma optimize("a", on)
void __cdecl sim_AdvanceGameClock(SIM_CLOCK* clock, int arg2, int arg3, int arg4)
{
	unsigned short* p4 = &clock->x04;
	int minutes;
	int days;

	/* Each of the three carries takes its own argument: the target reads
	 * [esp+0x10] before `push esi` (arg4), [esp+0x10] after the push
	 * (arg3) and [esp+0xc] after it (arg2).
	 *
	 * Three shapes are load-bearing for the byte match:
	 *   - `#pragma optimize("a", on)` (assume no aliasing) lets msvc6 hoist
	 *     the x04 read above the x06 store at 0x64, matching the target's
	 *     `xor esi,esi; mov si,[ecx+4]; mov [ecx+6],edx` order.  Without it
	 *     the two are transposed and the body scores 187/197.
	 *   - The two 60-minute carries are written without temporaries: each
	 *     sum appears twice, once under `/ 60` and once under `% 60`, and
	 *     msvc6 CSEs the pair into one imul/idiv chain.  Naming a sum in a
	 *     local costs 5 bytes (192 against the 197-byte target).
	 *   - Both `minutes < 0` and the fallthrough exit through one tail store
	 *     to x04.  With a `return` inside the branch and a duplicated store,
	 *     loop 2's `mov [ecx],esi` schedules ahead of `dec edx` (194/197);
	 *     merged, the store sinks below the decrement as the target has it.
	 *
	 * `minutes += *(volatile int*) &arg2` is required: read plain, msvc6
	 * folds the load into `add esi,[esp+0xc]` and the tail loses 76 bytes.
	 * `p4`, a plain `unsigned short*` alias of x04, gives the target's
	 * `xor esi,esi` + `mov si,word[ecx+4]`; a volatile ushort read emits a
	 * 6-byte `and esi,0xffff` instead. */
	clock->x06 = clock->x06 + (arg4 + clock->x0a) / 60;
	clock->x0a = (arg4 + clock->x0a) % 60;
	clock->x04 = (unsigned short) (clock->x04 + (arg3 + clock->x06) / 60);
	clock->x06 = (arg3 + clock->x06) % 60;
	minutes = *p4;
	minutes += *(volatile int*) &arg2;
	if (minutes >= 24) {
		days = (unsigned int) minutes / 24;
		minutes = minutes - days * 24;
		do {
			clock->x00++;
		} while (--days != 0);
	}
	if (minutes < 0) {
		days = (unsigned int) (23 - minutes) / 24;
		minutes = minutes + days * 24;
		do {
			clock->x00--;
		} while (--days != 0);
	}
	clock->x04 = (unsigned short) minutes;
}
#pragma optimize("", on)
#endif

#if !defined(REBREW_SERVER) && !defined(REBREW_GOLD)
#pragma optimize("a", on)
/* ADDRESS: GOLDTL 0x00500bb0 */
/* ADDRESS: GOLDDE 0x004ec320 */
void __cdecl gm_AddTime(Time* clock, int arg2, int arg3, int arg4)
{
	unsigned short* p4 = &clock->hour;
	int minutes;
	int days;

	clock->min += (arg4 + clock->sec) / 60;
	clock->sec = (arg4 + clock->sec) % 60;
	clock->hour += (unsigned short) ((arg3 + clock->min) / 60);
	minutes = *p4;
	clock->min = (arg3 + clock->min) % 60;
	minutes += arg2;

	days = clock->day;
	if (minutes >= 24) {
		days += (unsigned int) minutes / 24;
		minutes -= (unsigned int) minutes / 24 * 24;
		clock->day = days;
	}
	if (minutes < 0) {
		days -= (unsigned int) (-1 - minutes) / 24 + 1;
		clock->day = days;
		minutes += ((unsigned int) (-1 - minutes) / 24 + 1) * 24;
	}

	clock->hour = (unsigned short) minutes;
}
#pragma optimize("", on)
#endif

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004fe140 */
void __cdecl gm_AddTime(TIME_4FE140* clock, int hours, int minutes, int seconds)
{
	unsigned short* hour = &clock->hour;
	int value;
	int days;
	unsigned int q;

	clock->minute += (seconds + clock->second) / 60;
	clock->second = (seconds + clock->second) % 60;
	clock->hour += (unsigned short) ((minutes + clock->minute) / 60);
	value = *hour;
	clock->minute = (minutes + clock->minute) % 60;
	value += hours;
	days = clock->day;
	if (value >= 24) {
		days += (unsigned int) value / 24;
		value -= (unsigned int) value / 24 * 24;
		clock->day = days;
	}
	if (value < 0) {
		q = (unsigned int) (-1 - value) / 24 + 1;
		days -= q;
		clock->day = days;
		value += q * 24;
	}
	clock->hour = (unsigned short) value;
}
#endif

/* Sets the simulation sync parameters for the entity query
 * engine. Stores target, type, and field values for later use
 * by the query dispatcher. */

/* ADDRESS: GOLDTL 0x00500c50 */
/* ADDRESS: GOLD 0x004fe1e0 */
/* ADDRESS: GOLDDE 0x004ec3c0 */
/* ADDRESS: SERVERDE 0x100140c0 */
void __cdecl sim_SetSyncParams(int target, unsigned char type_id, unsigned int field_6, unsigned int field_10)
{
	*(unsigned int*) (target + 10) = field_10 & 0xff;
	*(unsigned short*) (target + 4) = (unsigned short) type_id;
	*(unsigned int*) (target + 6) = field_6 & 0xff;
}
