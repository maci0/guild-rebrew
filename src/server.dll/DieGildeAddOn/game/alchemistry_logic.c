#include <string.h>

typedef struct {
typedef int(__cdecl* dispatch_fn)(unsigned char*);

extern char* g_table;
extern int __cdecl ResolveEntityById(void** dynamic, int zero1, int zero2, int id);
extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);
extern int __cdecl crt_rand_range(int range);
extern float __cdecl crt_rand_float(void);
extern int __cdecl crt_ftol(void);
extern void* __cdecl AllocateTrackedHeapBlock(unsigned int size, const char* tag);
extern void* __cdecl StartEntityQuery(int, int, int, ...);
extern int __cdecl RemoveObjectByType(void** objectListHead, unsigned int objectTypeId);
extern void __cdecl AddOrAccumulateObject(int p1, int p2, int p3);
extern void __cdecl RefreshMarketAvailability(int season);
extern float fColorScale;
extern int DAT_10030b6c;
extern char DAT_10035439;
extern int __cdecl create_entity(int, int, int, int, int);
extern void __cdecl setup_entity(int, int);
extern float DAT_100256cc;
extern float DAT_100256a0;
extern void* __cdecl LookupEntityRecordById(int entityId);
extern void __cdecl DeallocEntity(int entity, int param);
extern char s__ahm_AllocAhmInfo_1002a0f7[];
extern double dScaleFactor;
extern int DAT_1002c050[];
extern unsigned short* __cdecl NextEntityQueryMatch(void);
extern int* __cdecl LookupEntityInTable(int);
extern dispatch_fn PTR_LAB_1002c5a0[];

	int key;
	int val;
} PAIR;

	char hdr[8];
	int key;
	char pad[4];
	int val;
} SRC;

	char hdr[0xc];
	PAIR entries[6];
} TGT;

// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 130
// SYMBOL: _reset_entity_state
// FUNCTION: SERVER 0x1000BD50
// reset_entity_state
// PROTOTYPE: void __cdecl reset_entity_state(char * param_1)
void* memset(void*, int, unsigned int);

void __cdecl reset_entity_state(char* param_1)
{
	unsigned int* ptr;

	if ((param_1[2] == 1 || param_1[2] == 2) && param_1[0x164] != 0) {
		ptr = (unsigned int*) (param_1 + 0x1b4);
		memset(ptr, 0, 16);
		*(unsigned int*) (param_1 + 0x1c0) = 0xffffffff;
		*ptr = *ptr | 1;
	}
}

// ORIGIN: GAME
// STATUS: RELOC
// SIZE: 70
// SYMBOL: _check_flag
// FUNCTION: SERVER 0x1000BDA0
// check_flag
// PROTOTYPE: int __cdecl check_flag(char * p)

int __cdecl check_flag(char* p)
{
	unsigned char idx;
	char* sub;

	if ((*(unsigned char*) (p + 0x1CC) & 4) && (sub = *(char**) (p + 0x16C)) != 0) {
		idx = *(unsigned char*) sub;
		if (g_table[(unsigned int) idx * 589] == 0x1E) {
			return *(unsigned long*) (sub + 0x65) != 0;
		}
	}
	return 0;
}

// ORIGIN: GAME
// STATUS: MATCHING
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, zero-extend pattern (xor vs mov)
// SIZE: 1002
// SYMBOL: _ahm_ExAllocAlchemist
// BLOCKER_DELTA: 935
// ANALYSIS: Command handler for Allocating Alchemist/Building Entities. Resolves the parent town entity, scans the Static Entities Array (g_static_entities, size 768) for a free slot. Initializes building state including the next global entity id (g_next_entity_id), and links it to the world. Returns the static array index or logs an error.
// FUNCTION: SERVER 0x1000bdf0
// ahm_ExAllocAlchemist

/* GLOBAL: SERVER 0x100a8c30 */
extern int g_entity_type_table;

/* GLOBAL: SERVER 0x10030b6c */
extern int g_next_object_id;

/* GLOBAL: SERVER 0x10035434 */
extern int g_citizen_count;

/* GLOBAL: SERVER 0x10035439 */
extern unsigned char g_current_season;

/* GLOBAL: SERVER 0x1002a0f8 */
extern char g_1002a0f8[];

/* GLOBAL: SERVER 0x100256b4 */
extern float g_100256b4;

/* GLOBAL: SERVER 0x100256b8 */
extern float g_100256b8;

/* GLOBAL: SERVER 0x100256c0 */
extern float g_100256c0;

/* GLOBAL: SERVER 0x100256c4 */
extern float g_100256c4;

/* GLOBAL: SERVER 0x100256c8 */
extern float g_100256c8;

/* GLOBAL: SERVER 0x100256a0 */
extern float g_100256a0;

/* GLOBAL: SERVER 0x100256ac */
extern float g_100256ac;

/* GLOBAL: SERVER 0x100256b0 */
extern float g_100256b0;

unsigned short __cdecl ahm_ExAllocAlchemist(int param_1)
{
	unsigned short* puVar1;
	unsigned short uVar2;
	unsigned short* puVar3;
	char cVar6;
	unsigned short uVar7;
	int iVar9;
	int iVar10;
	int iVar11;
	unsigned int* puVar13;
	unsigned int uVar15;
	char* pcVar16;
	unsigned char* puStack_8;
	int iStack_4;

	ResolveEntityById((void**) &puStack_8, 0, 0, *(int*) (param_1 + 8));
	if (puStack_8 == 0) {
		pcVar16 = "ahm_ExAllocAlchemist: cant find target geb...";
		uVar15 = 0x449;
	}
	else {
		if (*(char*) (g_entity_type_table + *puStack_8 * 0x24d) == '\x1e') {
			iVar11 = 0;
			iVar10 = 0x100358a0;
			do {
				if (*(short*) iVar10 == -1) {
					break;
				}
				iVar10 = iVar10 + 0x21c;
				iVar11 = iVar11 + 1;
			} while (iVar10 < 0x1009aca0);
			if (iVar11 == 0x300) {
				iVar11 = 0;
				pcVar16 = (char*) 0x100358a2;
				do {
					if (*pcVar16 == '\x0f') {
						break;
					}
					pcVar16 = pcVar16 + 0x21c;
					iVar11 = iVar11 + 1;
				} while (pcVar16 < (char*) 0x1009aca2);
				if (iVar11 == 0x300) {
					pcVar16 = "ahm_ExAllocAlchemist: array overflow...";
					uVar15 = 0x45d;
					goto code_r0x1000be9f;
				}
			}
			iVar10 = iVar11 * 0x21c;
			if (*(char*) (iVar10 + 0x100358a2) == '\x0f') {
				g_citizen_count = g_citizen_count + -1;
			}
			puVar1 = (unsigned short*) (iVar10 + 0x100358a0);
			memset(puVar1, 0, 0x21c);
			*puVar1 = 0xffff;
			*(int*) (iVar10 + 0x100358a4) = -1;
			memset((char*) (iVar10 + 0x100358fc), 0xff, 0x20);
			g_citizen_count = g_citizen_count + 1;
			*puVar1 = (unsigned short) iVar11;
			*(int*) ((char*) puVar1 + 0x170) = (int) puStack_8;
			*(int*) ((char*) puVar1 + 0x16c) = (int) puStack_8;
			*((char*) puVar1 + 2) = 0;
			*(int*) ((char*) puVar1 + 4) = g_next_object_id;
			g_next_object_id = g_next_object_id + 1;
			*(int*) ((char*) puVar1 + 0x1f0) = 0;
			*(int*) ((char*) puVar1 + 0x210) = -1;
			*((char*) puVar1 + 0x215) = 0;
			*((char*) puVar1 + 0x216) = 0;
			*((char*) puVar1 + 0x217) = 0;
			*((unsigned char*) puVar1 + 0x218) = 1;
			*(int*) ((char*) puVar1 + 0x1e4) = 0x3f800000;
			*((char*) puVar1 + 8) = 100;
			*(short*) ((char*) puVar1 + 0xa) = (unsigned char) *(char*) (param_1 + 0x10);
			*((char*) puVar1 + 0x164) = 0x52;
			*((char*) puVar1 + 0x166) = 0;
			*((char*) puVar1 + 0x165) = 0;
			*(int*) ((char*) puVar1 + 0x1f4) = 0;
			*(int*) ((char*) puVar1 + 0x190) = 4;
			*(int*) ((char*) puVar1 + 0x194) = 0;
			*((char*) puVar1 + 0xd) = 1;
			*(int*) ((char*) puVar1 + 0x18c) = -1;
			*(int*) ((char*) puVar1 + 0x20c) = -1;
			*(short*) ((char*) puVar1 + 0x50) = 0x7fff;
			iVar11 = 0;
			do {
				cVar6 = (char) crt_rand_range(0x40);
				*((char*) puVar1 + 0x80 + iVar11) = cVar6 + 'T';
				iVar11 = iVar11 + 1;
			} while (iVar11 < 5);
			*((char*) puVar1 + 9) = 0;
			*(int*) ((char*) puVar1 + 0x1c) = 0x447a0000;
			{
				float fVar14;
				float fVar4;
				float fVar5;
				fVar14 = crt_rand_float();
				fVar4 = g_100256c8;
				*(int*) ((char*) puVar1 + 0x20) = 0x41400000;
				*(float*) ((char*) puVar1 + 0x14) = (fVar14 * fVar4 + g_100256c4) - g_100256c0;
				uVar15 = (unsigned int) crt_ftol();
				uVar7 = (unsigned short) crt_rand_range(uVar15);
				fVar5 = *(float*) ((char*) puVar1 + 0x1c) * g_100256b8;
				*(int*) ((char*) puVar1 + 0x18) = *(int*) ((char*) puVar1 + 0x1c);
				iStack_4 = 0;
				iVar11 = 0;
				*(float*) ((char*) puVar1 + 0x10) =
					(fVar5 + (float) uVar7) - *(float*) ((char*) puVar1 + 0x1c) * g_100256b4;
			}
			do {
				uVar7 = *puVar1;
				cVar6 = (char) crt_rand_range(0x40);
				*(char*) (uVar7 + iVar11 + 0x100a9820) = cVar6 + -0x20;
				uVar2 = *puVar1;
				*(char*) (uVar7 + iVar11 + 0x1014d8e0) = 0;
				iVar9 = uVar2 * 0x300 + iStack_4;
				cVar6 = (char) crt_rand_range(0x40);
				iVar11 = iVar11 + 0x300;
				iStack_4 = iStack_4 + 1;
				*(char*) (iVar9 + 0x100a9820) = cVar6 + -0x20;
				*(char*) (iVar9 + 0x1014d8e0) = 0;
			} while (iVar11 < 0x90000);
			if (*(int*) (puStack_8 + 0x65) == 0) {
				uVar15 = (unsigned int) AllocateTrackedHeapBlock(0x3c, g_1002a0f8);
				*(unsigned int*) (puStack_8 + 0x65) = uVar15;
			}
			puVar13 = *(unsigned int**) (puStack_8 + 0x65);
			for (iVar11 = 0xf; iVar11 != 0; iVar11 = iVar11 + -1) {
				*puVar13 = 0;
				puVar13 = puVar13 + 1;
			}
			**(int**) (puStack_8 + 0x65) = *(int*) ((char*) puVar1 + 4);
			{
				int tmp;
				tmp = *(char*) (param_1 + 0xf);
				*(float*) (*(int*) (puStack_8 + 0x65) + 4) = (tmp * g_100256ac + g_100256a0) * g_100256b0;
			}
			*(char*) (*(int*) (puStack_8 + 0x65) + 8) = *(char*) (param_1 + 0xc);
			*(char*) (*(int*) (puStack_8 + 0x65) + 9) = *(char*) (param_1 + 0xd);
			*(char*) (*(int*) (puStack_8 + 0x65) + 10) = *(char*) (param_1 + 0xe);
			*(char*) (*(int*) (puStack_8 + 0x65) + 0xb) = *(char*) (param_1 + 0xf);
			*(char*) (*(int*) (puStack_8 + 0x65) + 0xc) = *(char*) (param_1 + 0x14);
			iVar11 = StartEntityQuery(*(int*) (puStack_8 + 0x5d), 2, 6, 0, 0xff);
			if (iVar11 != 0) {
				puVar3 = *(unsigned short**) (iVar11 + 0x14);
				while (puVar3 != 0) {
					RemoveObjectByType(iVar11 + 0x14, *puVar3);
					puVar3 = *(unsigned short**) (iVar11 + 0x14);
				}
			}
			*(int*) (*(int*) (puStack_8 + 0x65) + 0x10) = *(int*) (param_1 + 0x20);
			if (iVar11 != 0) {
				AddOrAccumulateObject(*(int*) (iVar11 + 2), *(int*) (param_1 + 0x14), 2);
			}
			RefreshMarketAvailability((int) g_current_season);
			*(int*) ((char*) puVar1 + 0x1cc) = *(int*) ((char*) puVar1 + 0x1cc) | 4;
			return *puVar1;
		}
		pcVar16 = "ahm_ExAllocAlchemist: wrong type of target geb...";
		uVar15 = 0x451;
	}
code_r0x1000be9f:
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\alchemistry_logic.c", uVar15, pcVar16, 1);
	return 0xffff;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 160
// SYMBOL: _ApplyColorComponent
// FUNCTION: SERVER 0x1000c1e0
// ApplyColorComponent
// PROTOTYPE: int __cdecl ApplyColorComponent(char * param_1, char * param_2)

int __cdecl ApplyColorComponent(char* param_1, char* param_2)
{
	switch (*(int*) (param_1 + 8)) {
	case 0:
		*(unsigned char*) (param_2 + 8) = (unsigned char) (int) (*(float*) (param_1 + 0x10) * fColorScale);
		return 1;
	case 1:
		*(unsigned char*) (param_2 + 9) = (unsigned char) (int) (*(float*) (param_1 + 0x10) * fColorScale);
		return 1;
	case 2:
		*(unsigned char*) (param_2 + 0xa) = (unsigned char) (int) (*(float*) (param_1 + 0x10) * fColorScale);
		return 1;
	case 3:
		*(unsigned char*) (param_2 + 0xb) = (unsigned char) (int) (*(float*) (param_1 + 0x10) * fColorScale);
		return 1;
	default:
		return 0;
	}
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 130
// SYMBOL: _AllocateEntitySlot
// FUNCTION: SERVER 0x1000c280
// AllocateEntitySlot
// PROTOTYPE: int __stdcall AllocateEntitySlot(int param_1, int param_2, int param_3)

int __cdecl AllocateEntitySlot(int param_1, int param_2, int param_3)
{
	int* piVar1;
	void* pvVar2;
	int iVar3;

	iVar3 = 0;
	piVar1 = (int*) (param_2 + 0xc);
	do {
		if (*piVar1 == 0) {
			pvVar2 = StartEntityQuery(*(int*) (param_3 + 0x5d), 2, 6, 0, 0xff);
			*(int*) (param_1 + 0x14) = DAT_10030b6c;
			*(int*) (param_2 + 0xc + iVar3 * 8) = *(int*) (param_1 + 8);
			*(int*) (param_2 + 0x10 + iVar3 * 8) = *(int*) (param_1 + 0x10);
			if (pvVar2 != (void*) 0) {
				AddOrAccumulateObject(*(int*) ((char*) pvVar2 + 2), *(int*) (param_1 + 8), 2);
			}
			RefreshMarketAvailability((int) DAT_10035439);
			return 1;
		}
		iVar3 = iVar3 + 1;
		piVar1 = piVar1 + 2;
	} while (iVar3 < 6);
	return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov)
// BLOCKER_DELTA: 110
// SIZE: 110
// SYMBOL: _slot_clear_match
// FUNCTION: SERVER 0x1000C310
// slot_clear_match
// PROTOTYPE: int __cdecl slot_clear_match(char * data, char * target, char * src)

int __cdecl slot_clear_match(char* data, char* target, char* src)
{
	int i;
	char* slot_ptr;
	int key;
	int ent;
	key = *(int*) (data + 8);
	i = 0;
	slot_ptr = target + 0xc;
	while (i < 6) {
		if (*(int*) slot_ptr == key) {
			goto found;
		}
		i++;
		slot_ptr += 8;
	}
	return 0;
found:
	ent = create_entity(*(int*) (src + 0x5d), 2, 6, 0, 0xff);
	if (ent) {
		setup_entity(ent + 0x14, *(int*) (data + 8));
	}
	*(int*) (target + i * 8 + 0xc) = 0;
	*(int*) (target + i * 8 + 0x10) = 0;
	return 1;
}

// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 51
// SYMBOL: _search_and_set
// FUNCTION: SERVER 0x1000C380
// search_and_set
// PROTOTYPE: int __cdecl search_and_set(SRC * src, TGT * tgt)

int __cdecl search_and_set(SRC* src, TGT* tgt)
{
	int i;
	for (i = 0; i < 6; i++) {
		if (tgt->entries[i].key == src->key) {
			tgt->entries[i].val = src->val;
			return 1;
		}
	}
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: jump condition swap
// SIZE: 83
// SYMBOL: _ClampFloatValue
// BLOCKER_DELTA: 47
// FUNCTION: SERVER 0x1000c3c0
// ClampFloatValue
// PROTOTYPE: int __cdecl ClampFloatValue(int param_1, int param_2)

int __cdecl ClampFloatValue(int param_1, int param_2)
{
	float fVar1;

	fVar1 = *(float*) (param_1 + 0x10) + *(float*) (param_2 + 4);
	if (fVar1 > DAT_100256cc) {
		if (fVar1 >= DAT_100256a0) {
			*(float*) (param_2 + 4) = DAT_100256a0;
			return 1;
		}
		*(float*) (param_2 + 4) = fVar1;
		return 1;
	}
	*(float*) (param_2 + 4) = DAT_100256cc;
	return 1;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 166
// SYMBOL: _FireEntityAndCleanup
// FUNCTION: SERVER 0x1000c420
// FireEntityAndCleanup
// PROTOTYPE: int __cdecl FireEntityAndCleanup(int param_1, int * param_2, int param_3)

int __cdecl FireEntityAndCleanup(int param_1, int* param_2, int param_3)
{
	unsigned short* puVar1;
	void* pvVar2;
	unsigned int* puVar3;
	int iVar4;

	puVar1 = (unsigned short*) LookupEntityRecordById(*param_2);
	if (puVar1 != (unsigned short*) 0) {
		pvVar2 = StartEntityQuery(*(int*) (param_3 + 0x5d), 2, 6, 0, 0xff);
		*(int*) (puVar1 + 0xb8) = 0;
		*(int*) (puVar1 + 0xb6) = 0;
		puVar3 = (unsigned int*) (param_2 + 3);
		iVar4 = 6;
		do {
			if (*puVar3 != 0) {
				if (pvVar2 != (void*) 0) {
					RemoveObjectByType((void**) ((int) pvVar2 + 0x14), *puVar3);
				}
				*puVar3 = 0;
				puVar3[1] = 0;
			}
			puVar3 = puVar3 + 2;
			iVar4 = iVar4 - 1;
		} while (iVar4 != 0);
		for (iVar4 = 0xf; iVar4 != 0; iVar4--) {
			*param_2 = 0;
			param_2 = param_2 + 1;
		}
		DeallocEntity(*puVar1, 1);
		return 1;
	}
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 295
// SYMBOL: _ahm_AllocAhmInfo
// BLOCKER_DELTA: 269
// FUNCTION: SERVER 0x1000c4d0
// ahm_AllocAhmInfo
// PROTOTYPE: int __cdecl ahm_AllocAhmInfo(int param_1, int param_2)

int __cdecl ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, int streamCtx);
void* __cdecl AllocateTrackedHeapBlock(unsigned int allocSize, char* groupTag);

int __cdecl ahm_AllocAhmInfo(int param_1, int param_2)
{
	int bVar1;
	void* pvVar2;
	int iVar3;
	unsigned char* outBuffer;
	unsigned int* puVar4;
	unsigned int* puVar5;
	unsigned int local_3c;
	unsigned char local_38[4];
	unsigned char local_34;
	unsigned char local_33;
	unsigned char local_32;
	unsigned char local_31[5];
	unsigned char local_2c[44];

	bVar1 = ReadVfsDataChecked(&local_3c, 4, 1, param_1);
	if (bVar1 == 0) {
		return 0;
	}
	bVar1 = ReadVfsDataChecked(local_38, 4, 1, param_1);
	if (bVar1 == 0) {
		return 0;
	}
	bVar1 = ReadVfsDataChecked(&local_34, 1, 1, param_1);
	if (bVar1 == 0) {
		return 0;
	}
	bVar1 = ReadVfsDataChecked(&local_33, 1, 1, param_1);
	if (bVar1 != 0) {
		bVar1 = ReadVfsDataChecked(&local_32, 1, 1, param_1);
		if (bVar1 == 0) {
			return 0;
		}
		bVar1 = ReadVfsDataChecked(local_31, 1, 1, param_1);
		if (bVar1 != 0) {
			iVar3 = 0;
			outBuffer = local_2c;
			while (bVar1 = ReadVfsDataChecked(outBuffer - 4, 4, 1, param_1), bVar1 != 0) {
				bVar1 = ReadVfsDataChecked(outBuffer, 4, 1, param_1);
				if (bVar1 == 0) {
					return 0;
				}
				iVar3 = iVar3 + 1;
				outBuffer = outBuffer + 8;
				if (5 < iVar3) {
					if (*(int*) (param_2 + 0x65) == 0) {
						pvVar2 = AllocateTrackedHeapBlock(0x3c, s__ahm_AllocAhmInfo_1002a0f7 + 1);
						*(void**) (param_2 + 0x65) = pvVar2;
					}
					puVar4 = &local_3c;
					puVar5 = *(unsigned int**) (param_2 + 0x65);
					iVar3 = 0xf;
					do {
						*puVar5 = *puVar4;
						puVar4 = puVar4 + 1;
						puVar5 = puVar5 + 1;
						iVar3 = iVar3 - 1;
					} while (iVar3 != 0);
					return 1;
				}
			}
		}
		return 0;
	}
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 109
// SYMBOL: _InitRandomEntity
// FUNCTION: SERVER 0x1000c600
// InitRandomEntity
// PROTOTYPE: char * InitRandomEntity(void)

int __cdecl RandomBelow(unsigned short max);

char* __cdecl InitRandomEntity(void)
{
	unsigned int idx;
	int tries;
	float* pfVar;
	int i;
	int offset;

	idx = (unsigned short) RandomBelow(0x20);
	tries = 0x20;
	do {
		if (*(char*) (0x1002a2c2 + idx * 0xf4) == '\0') {
			i = 0xe;
			offset = idx * 0xf4;
			pfVar = (float*) (0x1002a200 + offset);
			do {
				*pfVar = (float) (pfVar[-1] * (float) dScaleFactor);
				pfVar = pfVar + 3;
				i = i - 1;
			} while (i != 0);
			*(char*) (0x1002a2c2 + offset) = 1;
			return (char*) (0x1002a1d0 + offset);
		}
		tries = tries - 1;
		idx = (idx + 1) & 0x1f;
	} while (tries != 0);
	return (char*) 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), jump condition swap
// BLOCKER_DELTA: 72
// SIZE: 45
// SYMBOL: _LookupEntityInTable
// GHIDRA: find_by_id
// FUNCTION: SERVER 0x1000c670
// LookupEntityInTable
// PROTOTYPE: int * __cdecl LookupEntityInTable(int param_1)

int* __cdecl LookupEntityInTable(int param_1)
{
	int i;
	int* p;

	for (i = 0, p = DAT_1002c050; (int) p < (int) (DAT_1002c050 + 0x17 * 10); p += 0x17, i++) {
		if (*p == param_1) {
			return DAT_1002c050 + i * 0x17;
		}
	}
	return (int*) 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, jump condition swap
// SIZE: 102
// SYMBOL: _QueryEntityBuildingType
// BLOCKER_DELTA: 55
// FUNCTION: SERVER 0x1000c6a0
// QueryEntityBuildingType
// PROTOTYPE: void __cdecl QueryEntityBuildingType(int param_1)

void __cdecl QueryEntityBuildingType(int param_1)
{
	unsigned short* puVar1;
	int iVar2;

	puVar1 = StartEntityQuery(*(int*) (param_1 + 0x178), 1, 5);
	if (puVar1 != (unsigned short*) 0) {
		while (iVar2 = (int) LookupEntityInTable(*puVar1), iVar2 == 0) {
			puVar1 = NextEntityQueryMatch();
			if (puVar1 == (unsigned short*) 0) {
				LookupEntityInTable(0);
				return;
			}
		}
		if (*(int*) (iVar2 + 0x58) != 1 && *(int*) (iVar2 + 0x58) != 2) {
			return;
		}
		if (0 < *(int*) ((char*) puVar1 + 0x20)) {
			return;
		}
	}
	LookupEntityInTable(0);
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: loop rotation / branch layout, zero-extend pattern (xor vs mov)
// SIZE: 752
// SYMBOL: _GetCommandPayloadSize
// FUNCTION: SERVER 0x1000c710
// GetCommandPayloadSize

/* TODO: Add extern declarations for globals and called functions */

/* Auto-generated Ghidra decompilation */
// BLOCKER_DELTA: 569
// PROTOTYPE: int __cdecl GetCommandPayloadSize(uchar * param_1)
int GetCommandPayloadSize(unsigned char* param_1)

{
	int iVar1;
	unsigned char* puVar2;
	int iVar3;
	int iVar4;

	// switch table (103 cases) at 0x1000c864
	switch (*param_1) {
	case 3:
	case 0x13:
	case 0x1a:
	case 0x25:
	case 0x2b:
	case 0x34:
	case 0x36:
	case 0x38:
	case 0x47:
	case 0x52:
	case 0x54:
	case 0x5b:
	case 0x5d:
		return 0x1c;
	case 4:
		return 0x11;
	default:
		return 0x91;
	case 8:
	case 0x1c:
	case 0x28:
	case 0x31:
	case 0x3b:
	case 0x42:
	case 0x43:
	case 0x4a:
	case 0x4d:
	case 0x57:
	case 0x58:
	case 0x69:
		return 0x14;
	case 10:
		return 0x50;
	case 0xb:
		return 0x2a;
	case 0xc:
		return 0x49;
	case 0xd:
	case 0x21:
	case 0x23:
	case 0x24:
	case 0x26:
	case 0x27:
	case 0x29:
	case 0x2a:
	case 0x33:
	case 0x39:
	case 0x3a:
	case 0x5a:
	case 0x66:
	case 0x68:
		return 0x18;
	case 0xf:
	case 0x2c:
		return 0x21;
	case 0x11:
	case 0x3d:
		return 0x27;
	case 0x12:
	case 0x1e:
		return 0x1e;
	case 0x14:
		return 0x16;
	case 0x15:
		return 0x39;
	case 0x16:
	case 0x17:
		puVar2 = param_1 + (*param_1 == 0x16 ? 0x15 : 0x15);
		iVar3 = 0x15;
		break;
	case 0x18:
		return param_1[0x14] * 5 + 0x15;
	case 0x19:
	case 0x53:
		return 0x24;
	case 0x1b:
	case 100:
		return 0x28;
	case 0x1d:
		return 0x5f;
	case 0x20:
		return (-(param_1[0x10] != '\x0e') & 0x7c) + 0x11;
	case 0x22:
		return 0x3d;
	case 0x2d:
	case 0x45:
		return 0x1f;
	case 0x2e:
	case 0x3c:
		return 0x20;
	case 0x2f:
	case 0x30:
		return 0x3c;
	case 0x32:
	case 0x3e:
	case 0x4f:
	case 0x5e:
	case 99:
		return 0x34;
	case 0x35:
		return 0x5d;
	case 0x37:
		return 0x45;
	case 0x40:
	case 0x60:
		return 0x2f;
	case 0x41:
		return 0x4a;
	case 0x44:
		return 0x17;
	case 0x46:
		return 0x19;
	case 0x48:
		return 0x15;
	case 0x49:
		return 0x36;
	case 0x4b:
	case 0x67:
		return 0x90;
	case 0x4c:
		return 0x35;
	case 0x4e:
		return 0x40;
	case 0x50:
	case 0x51:
		return 0x44;
	case 0x55:
		return 0x61;
	case 0x56:
		return 0x38;
	case 0x5c:
		return 0x1a;
	case 0x5f:
		return 0x80;
	case 0x61:
	case 0x62:
		return 0x29;
	}
	for (iVar4 = param_1[0x14]; iVar4 > 0; iVar4 = iVar4 - 1) {
		iVar1 = puVar2[1] * *puVar2 + 4;
		iVar3 = iVar3 + iVar1;
		puVar2 = puVar2 + iVar1;
	}
	return iVar3;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 130
// SYMBOL: _ProcessEntityChain
// BLOCKER_DELTA: 83
// ANALYSIS: Iterates through a linked list of CommandPackets generated from a Command 0x05 / 0x06 block. Runs secondary validation handlers from g_entity_chain_handlers. Re-flags commands to 0x01/0x02 status based on success/fail.
// FUNCTION: SERVER 0x1000ca00
// ProcessEntityChain
// PROTOTYPE: int __cdecl ProcessEntityChain(char * param_1)

int __cdecl ProcessEntityChain(char* param_1)
{
	char cVar1;
	int bVar2;
	int iVar3;
	unsigned char* pbVar4;

	bVar2 = 1;
	pbVar4 = *(unsigned char**) (param_1 + 0x95);
	do {
		if (*pbVar4 == 6) {
			goto check_result;
		}
		iVar3 = PTR_LAB_1002c5a0[*pbVar4](pbVar4);
		if (iVar3 != 0) {
			bVar2 = 0;
		}
		pbVar4 = *(unsigned char**) (pbVar4 + 0x95);
	} while (bVar2);
error_path:
	cVar1 = *param_1;
	while (cVar1 != 6) {
		*param_1 = 2;
		param_1 = *(char**) (param_1 + 0x95);
		cVar1 = *param_1;
	}
	*param_1 = 2;
	return 1;
check_result:
	if (!bVar2) {
		goto error_path;
	}
	*param_1 = 1;
	cVar1 = *param_1;
	while (cVar1 != 6) {
		param_1 = *(char**) (param_1 + 0x95);
		cVar1 = *param_1;
	}
	*param_1 = 1;
	return 1;
}

// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 130
// SYMBOL: _get_field_by_type
// FUNCTION: SERVER 0x1000CA90
// get_field_by_type
// PROTOTYPE: int __cdecl get_field_by_type(char * p, int type)
int __cdecl get_field_by_type(char* p, int type)
{
	unsigned int idx;
	if (type == -2) {
		idx = *(unsigned char*) (p + 3);
		idx = ((((idx << 4) + idx) << 8) + idx) << 4;
		idx = idx + *(unsigned char*) (p + 3);
		return *(int*) ((char*) 0x10442d00 + idx * 9 * 4);
	}
	if (type == -3) {
		idx = *(unsigned char*) (p + 3);
		idx = ((((idx << 4) + idx) << 8) + idx) << 4;
		idx = idx + *(unsigned char*) (p + 3);
		return *(int*) ((char*) 0x10442d04 + idx * 9 * 4);
	}
	if (type == -4) {
		idx = *(unsigned char*) (p + 3);
		idx = ((((idx << 4) + idx) << 8) + idx) << 4;
		idx = idx + *(unsigned char*) (p + 3);
		return *(int*) ((char*) 0x10442d08 + idx * 9 * 4);
	}
}
