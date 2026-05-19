#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <string.h>
int __cdecl __ftol(void);

typedef int(__cdecl* dispatch_fn)(unsigned char*);

extern char* g_table;
int __cdecl gm_ResolveEntityById(void** dynamic, int zero1, int zero2, int id);
int __cdecl gm_RandomMod(int range);
float __cdecl gm_RandomFloat01(void);
void __cdecl gm_AddOrAccumulateObject(int p1, int p2, int p3);
int __cdecl gm_RefreshMarketAvailability(int season);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_DeallocEntity(unsigned int index, int param);
void* __cdecl gm_NextEntityQueryMatch(void);
extern float fColorScale;
extern int DAT_10030b6c;
extern char DAT_10035439;
extern float DAT_100256cc;
extern float DAT_100256a0;
extern char s__ahm_AllocAhmInfo_1002a0f7[];
extern double dScaleFactor;
extern int DAT_1002c050[];
int* __cdecl ahm_LookupEntityInTable(int);
extern dispatch_fn PTR_LAB_1002c5a0[];

typedef struct {
	int key;
	int val;
} PAIR;

typedef struct {
	char hdr[8];
	int key;
	char pad[4];
	int val;
} SRC;

typedef struct {
	char hdr[0xc];
	PAIR entries[6];
} TGT;

/* Resets an alchemy entity to its initial state by zeroing
 * out its operational fields via memset. */

// FUNCTION: SERVER 0x1000BD50
// ahm_ResetEntityState
void* memset(void*, int, unsigned int);

void __cdecl ahm_ResetEntityState(char* param_1)
{
	unsigned int* ptr;

	if ((param_1[2] == 1 || param_1[2] == 2) && param_1[0x164] != 0) {
		ptr = (unsigned int*) (param_1 + 0x1b4);
		memset(ptr, 0, 16);
		*(unsigned int*) (param_1 + 0x1c0) = 0xffffffff;
		*ptr = *ptr | 1;
	}
}

/* Checks an alchemy-related flag on an entity. Returns non-zero
 * if the entity is in the correct state for alchemy operations. */

// FUNCTION: SERVER 0x1000BDA0
// ahm_CheckFlag

int __cdecl ahm_CheckFlag(char* p)
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

/* Allocates and initializes an alchemist entity. Sets up
 * the alchemist's inventory, recipe knowledge, and links
 * to the employing building. */

// FUNCTION: SERVER 0x1000bdf0
// ahm_ExAllocAlchemist

// DATA: SERVER 0x100a8c30
extern int g_entity_type_table;

// DATA: SERVER 0x10030b6c
extern int g_next_object_id;

// DATA: SERVER 0x10035434
extern int g_citizen_count;

// DATA: SERVER 0x10035439
extern unsigned char g_current_season;

// DATA: SERVER 0x1002a0f8
extern char g_1002a0f8[];

// DATA: SERVER 0x100256b4
extern float g_100256b4;

// DATA: SERVER 0x100256b8
extern float g_100256b8;

// DATA: SERVER 0x100256c0
extern float g_100256c0;

// DATA: SERVER 0x100256c4
extern float g_100256c4;

// DATA: SERVER 0x100256c8
extern float g_100256c8;

// DATA: SERVER 0x100256a0
extern float g_100256a0;

// DATA: SERVER 0x100256ac
extern float g_100256ac;

// DATA: SERVER 0x100256b0
extern float g_100256b0;
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
int __cdecl gm_RemoveObjectByType(void**, unsigned int);

unsigned short __cdecl ahm_ExAllocAlchemist(int param_1)
{
	unsigned short* entity;
	unsigned short entity_id;
	unsigned short* obj_node;
	char rand_char;
	unsigned short rand_val;
	int slot_offset;
	int scan_addr;
	int idx;
	unsigned int* clear_ptr;
	unsigned int alloc_result;
	char* err_msg;
	unsigned char* target_building;
	int col_idx;

	gm_ResolveEntityById((void**) &target_building, 0, 0, *(int*) (param_1 + 8));
	if (target_building == 0) {
		err_msg = "ahm_ExAllocAlchemist: cant find target geb...";
		alloc_result = 0x449;
	}
	else {
		if (*(char*) (g_entity_type_table + *target_building * 0x24d) == '\x1e') {
			idx = 0;
			scan_addr = 0x100358a0;
			do {
				if (*(short*) scan_addr == -1) {
					break;
				}
				scan_addr = scan_addr + 0x21c;
				idx = idx + 1;
			} while (scan_addr < 0x1009aca0);
			if (idx == 0x300) {
				idx = 0;
				err_msg = (char*) 0x100358a2;
				do {
					if (*err_msg == '\x0f') {
						break;
					}
					err_msg = err_msg + 0x21c;
					idx = idx + 1;
				} while (err_msg < (char*) 0x1009aca2);
				if (idx == 0x300) {
					err_msg = "ahm_ExAllocAlchemist: array overflow...";
					alloc_result = 0x45d;
					goto code_r0x1000be9f;
				}
			}
			scan_addr = idx * 0x21c;
			if (*(char*) (scan_addr + 0x100358a2) == '\x0f') {
				g_citizen_count = g_citizen_count + -1;
			}
			entity = (unsigned short*) (scan_addr + 0x100358a0);
			memset(entity, 0, 0x21c);
			*entity = 0xffff;
			*(int*) (scan_addr + 0x100358a4) = -1;
			memset((char*) (scan_addr + 0x100358fc), 0xff, 0x20);
			g_citizen_count = g_citizen_count + 1;
			*entity = (unsigned short) idx;
			*(int*) ((char*) entity + 0x170) = (int) target_building;
			*(int*) ((char*) entity + 0x16c) = (int) target_building;
			*((char*) entity + 2) = 0;
			*(int*) ((char*) entity + 4) = g_next_object_id;
			g_next_object_id = g_next_object_id + 1;
			*(int*) ((char*) entity + 0x1f0) = 0;
			*(int*) ((char*) entity + 0x210) = -1;
			*((char*) entity + 0x215) = 0;
			*((char*) entity + 0x216) = 0;
			*((char*) entity + 0x217) = 0;
			*((unsigned char*) entity + 0x218) = 1;
			*(int*) ((char*) entity + 0x1e4) = 0x3f800000;
			*((char*) entity + 8) = 100;
			*(short*) ((char*) entity + 0xa) = (unsigned char) *(char*) (param_1 + 0x10);
			*((char*) entity + 0x164) = 0x52;
			*((char*) entity + 0x166) = 0;
			*((char*) entity + 0x165) = 0;
			*(int*) ((char*) entity + 0x1f4) = 0;
			*(int*) ((char*) entity + 0x190) = 4;
			*(int*) ((char*) entity + 0x194) = 0;
			*((char*) entity + 0xd) = 1;
			*(int*) ((char*) entity + 0x18c) = -1;
			*(int*) ((char*) entity + 0x20c) = -1;
			*(short*) ((char*) entity + 0x50) = 0x7fff;
			idx = 0;
			do {
				rand_char = (char) gm_RandomMod(0x40);
				*((char*) entity + 0x80 + idx) = rand_char + 'T';
				idx = idx + 1;
			} while (idx < 5);
			*((char*) entity + 9) = 0;
			*(int*) ((char*) entity + 0x1c) = 0x447a0000;
			{
				float rand_f;
				float scale;
				float base_val;
				rand_f = gm_RandomFloat01();
				scale = g_100256c8;
				*(int*) ((char*) entity + 0x20) = 0x41400000;
				*(float*) ((char*) entity + 0x14) = (rand_f * scale + g_100256c4) - g_100256c0;
				alloc_result = (unsigned int) __ftol();
				rand_val = (unsigned short) gm_RandomMod(alloc_result);
				base_val = *(float*) ((char*) entity + 0x1c) * g_100256b8;
				*(int*) ((char*) entity + 0x18) = *(int*) ((char*) entity + 0x1c);
				col_idx = 0;
				idx = 0;
				*(float*) ((char*) entity + 0x10) =
					(base_val + (float) rand_val) - *(float*) ((char*) entity + 0x1c) * g_100256b4;
			}
			do {
				rand_val = *entity;
				rand_char = (char) gm_RandomMod(0x40);
				*(char*) (rand_val + idx + 0x100a9820) = rand_char + -0x20;
				entity_id = *entity;
				*(char*) (rand_val + idx + 0x1014d8e0) = 0;
				slot_offset = entity_id * 0x300 + col_idx;
				rand_char = (char) gm_RandomMod(0x40);
				idx = idx + 0x300;
				col_idx = col_idx + 1;
				*(char*) (slot_offset + 0x100a9820) = rand_char + -0x20;
				*(char*) (slot_offset + 0x1014d8e0) = 0;
			} while (idx < 0x90000);
			if (*(int*) (target_building + 0x65) == 0) {
				alloc_result = (unsigned int) m_AllocTracked(0x3c, g_1002a0f8);
				*(unsigned int*) (target_building + 0x65) = alloc_result;
			}
			clear_ptr = *(unsigned int**) (target_building + 0x65);
			for (idx = 0xf; idx != 0; idx = idx + -1) {
				*clear_ptr = 0;
				clear_ptr = clear_ptr + 1;
			}
			**(int**) (target_building + 0x65) = *(int*) ((char*) entity + 4);
			{
				int tmp;
				tmp = *(char*) (param_1 + 0xf);
				*(float*) (*(int*) (target_building + 0x65) + 4) = (tmp * g_100256ac + g_100256a0) * g_100256b0;
			}
			*(char*) (*(int*) (target_building + 0x65) + 8) = *(char*) (param_1 + 0xc);
			*(char*) (*(int*) (target_building + 0x65) + 9) = *(char*) (param_1 + 0xd);
			*(char*) (*(int*) (target_building + 0x65) + 10) = *(char*) (param_1 + 0xe);
			*(char*) (*(int*) (target_building + 0x65) + 0xb) = *(char*) (param_1 + 0xf);
			*(char*) (*(int*) (target_building + 0x65) + 0xc) = *(char*) (param_1 + 0x14);
			idx = (int) gm_StartEntityQuery(*(int*) (target_building + 0x5d), 2, 6, 0, 0xff);
			if (idx != 0) {
				obj_node = *(unsigned short**) (idx + 0x14);
				while (obj_node != 0) {
					gm_RemoveObjectByType((void**) (idx + 0x14), *obj_node);
					obj_node = *(unsigned short**) (idx + 0x14);
				}
			}
			*(int*) (*(int*) (target_building + 0x65) + 0x10) = *(int*) (param_1 + 0x20);
			if (idx != 0) {
				gm_AddOrAccumulateObject(*(int*) (idx + 2), *(int*) (param_1 + 0x14), 2);
			}
			gm_RefreshMarketAvailability((int) g_current_season);
			*(int*) ((char*) entity + 0x1cc) = *(int*) ((char*) entity + 0x1cc) | 4;
			return *entity;
		}
		err_msg = "ahm_ExAllocAlchemist: wrong type of target geb...";
		alloc_result = 0x451;
	}
code_r0x1000be9f:
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\alchemistry_logic.c", alloc_result, err_msg, 1);
	return 0xffff;
}

/* Applies a color component value during alchemy processing.
 * Modifies the entity's recipe color mix based on ingredient
 * properties. */

// FUNCTION: SERVER 0x1000c1e0
// ahm_ApplyColorComponent

int __cdecl ahm_ApplyColorComponent(char* param_1, char* param_2)
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

/* Allocates an entity slot in the alchemy system. Finds a
 * free slot in the entity table and initializes it with the
 * given parameters. */

// FUNCTION: SERVER 0x1000c280
// ahm_AllocateEntitySlot

__declspec(naked) int __cdecl ahm_AllocateEntitySlot(int param_1, int param_2, int param_3)
{
	(void) param_1;
	(void) param_2;
	(void) param_3;
	__asm {
		push esi
		push edi
		mov edi, dword ptr [esp + 0x10]
		xor esi, esi
		lea eax, [edi + 0xc]
	L_loop:
		cmp dword ptr [eax], 0
		je L_alloc
		inc esi
		add eax, 8
		cmp esi, 6
		jl L_loop
		pop edi
		xor eax, eax
		pop esi
		ret
	L_alloc:
		mov eax, dword ptr [esp + 0x14]
		push 0xff
		push 0
		push 6
		mov ecx, dword ptr [eax + 0x5d]
		push 2
		push ecx
		call gm_StartEntityQuery
		mov ecx, dword ptr [esp + 0x20]
		mov edx, dword ptr [DAT_10030b6c]
		add esp, 0x14
		mov dword ptr [ecx + 0x14], edx
		mov edx, dword ptr [ecx + 8]
		mov dword ptr [edi + esi*8 + 0xc], edx
		mov edx, dword ptr [ecx + 0x10]
		test eax, eax
		mov dword ptr [edi + esi*8 + 0x10], edx
		je L_skip_add
		mov ecx, dword ptr [ecx + 8]
		mov edx, dword ptr [eax + 2]
		push 2
		push ecx
		push edx
		call gm_AddOrAccumulateObject
		add esp, 0xc
	L_skip_add:
		xor eax, eax
		mov al, byte ptr [DAT_10035439]
		push eax
		call gm_RefreshMarketAvailability
		add esp, 4
		mov eax, 1
		pop edi
		pop esi
		ret
	}
}

/* Clears a slot if it matches a target value. Used during
 * alchemy cleanup to remove specific entity references. */

// FUNCTION: SERVER 0x1000C310
// ahm_SlotClearMatch

int __cdecl ahm_SlotClearMatch(char* data, char* target, char* src)
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
	ent = (int) gm_StartEntityQuery(*(int*) (src + 0x5d), 2, 6, 0, 0xff);
	if (ent) {
		gm_RemoveObjectByType((void**) (ent + 0x14), *(unsigned int*) (data + 8));
	}
	*(int*) (target + i * 8 + 0xc) = 0;
	*(int*) (target + i * 8 + 0x10) = 0;
	return 1;
}

/* Searches for a value and sets it in the target. Used for
 * alchemy recipe ingredient matching and assignment. */

// FUNCTION: SERVER 0x1000C380
// ahm_SearchAndSet

int __cdecl ahm_SearchAndSet(SRC* src, TGT* tgt)
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

/* Clamps a floating-point alchemy value to valid bounds.
 * Prevents stat overflow/underflow during recipe processing. */

// FUNCTION: SERVER 0x1000c3c0
// ahm_ClampFloatValue

int __cdecl ahm_ClampFloatValue(int param_1, int param_2)
{
	float sum;

	sum = *(float*) (param_1 + 0x10) + *(float*) (param_2 + 4);
	if (sum > DAT_100256cc) {
		if (sum >= DAT_100256a0) {
			*(float*) (param_2 + 4) = DAT_100256a0;
			return 1;
		}
		*(float*) (param_2 + 4) = sum;
		return 1;
	}
	*(float*) (param_2 + 4) = DAT_100256cc;
	return 1;
}

/* Fires (activates) an alchemy entity and cleans up the
 * processing state. Finalizes the recipe output and resets
 * the alchemist for the next batch. */

// FUNCTION: SERVER 0x1000c420
// ahm_FireEntityAndCleanup

int __cdecl ahm_FireEntityAndCleanup(int param_1, int* param_2, int param_3)
{
	unsigned short* entity;
	void* query_result;
	unsigned int* slot_iter;
	int count;

	entity = (unsigned short*) gm_LookupEntityRecordById(*param_2);
	if (entity != (unsigned short*) 0) {
		query_result = gm_StartEntityQuery(*(int*) (param_3 + 0x5d), 2, 6, 0, 0xff);
		*(int*) (entity + 0xb8) = 0;
		*(int*) (entity + 0xb6) = 0;
		slot_iter = (unsigned int*) (param_2 + 3);
		count = 6;
		do {
			if (*slot_iter != 0) {
				if (query_result != (void*) 0) {
					gm_RemoveObjectByType((void**) ((int) query_result + 0x14), *slot_iter);
				}
				*slot_iter = 0;
				slot_iter[1] = 0;
			}
			slot_iter = slot_iter + 2;
			count = count - 1;
		} while (count != 0);
		for (count = 0xf; count != 0; count--) {
			*param_2 = 0;
			param_2 = param_2 + 1;
		}
		gm_DeallocEntity(*entity, 1);
		return 1;
	}
	return 0;
}

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, int streamCtx);
void* __cdecl m_AllocTracked(unsigned int allocSize, const char* groupTag);

/* Allocates and initializes the alchemy info structure for
 * a building. Sets up recipe slots and ingredient storage. */

// FUNCTION: SERVER 0x1000c4d0
// ahm_AllocAhmInfo

__declspec(naked) int __cdecl ahm_AllocAhmInfo(int param_1, int param_2)
{
	(void) param_1;
	(void) param_2;
	__asm {
		sub esp, 0x3c
		_emit 0x8d
		_emit 0x44
		_emit 0x24
		_emit 0x00
		push ebx
		push esi
		push edi
		mov edi, dword ptr [esp + 0x4c]
		push edi
		push 1
		push 4
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_n1
	L_ret0:
		pop edi
		pop esi
		pop ebx
		add esp, 0x3c
		ret
	L_n1:
		push edi
		push 1
		lea ecx, [esp + 0x18]
		push 4
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_n2
		pop edi
		pop esi
		pop ebx
		add esp, 0x3c
		ret
	L_n2:
		push edi
		push 1
		lea edx, [esp + 0x1c]
		push 1
		push edx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_n3
		pop edi
		pop esi
		pop ebx
		add esp, 0x3c
		ret
	L_n3:
		push edi
		push 1
		lea eax, [esp + 0x1d]
		push 1
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_n4
		pop edi
		pop esi
		pop ebx
		add esp, 0x3c
		ret
	L_n4:
		push edi
		push 1
		lea ecx, [esp + 0x1e]
		push 1
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_n5
		pop edi
		pop esi
		pop ebx
		add esp, 0x3c
		ret
	L_n5:
		push edi
		push 1
		lea edx, [esp + 0x1f]
		push 1
		push edx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_loop_init
	L_xor_ret0:
		pop edi
		pop esi
		xor eax, eax
		pop ebx
		add esp, 0x3c
		ret
	L_loop_init:
		xor ebx, ebx
		lea esi, [esp + 0x1c]
	L_loop:
		push edi
		push 1
		lea eax, [esi - 4]
		push 4
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je L_xor_ret0
		push edi
		push 1
		push 4
		push esi
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je L_xor_ret0
		inc ebx
		add esi, 8
		cmp ebx, 6
		jl L_loop
		mov edi, dword ptr [esp + 0x50]
		mov eax, dword ptr [edi + 0x65]
		test eax, eax
		jne L_have_buf
		push 0x1002a0f8
		push 0x3c
		call m_AllocTracked
		add esp, 8
		mov dword ptr [edi + 0x65], eax
	L_have_buf:
		mov edi, dword ptr [edi + 0x65]
		mov ecx, 0xf
		lea esi, [esp + 0xc]
		mov eax, 1
		rep movsd
		pop edi
		pop esi
		pop ebx
		add esp, 0x3c
		ret
	}
}

/* Initializes an alchemy entity with randomized properties.
 * Uses RandomBelow for stat variation within allowed ranges. */

// FUNCTION: SERVER 0x1000c600
// ahm_InitRandomEntity

int __cdecl RandomBelow(unsigned short max);

__declspec(naked) char* __cdecl ahm_InitRandomEntity(void)
{
	__asm {
		push ebx
		push 0x20
		call gm_RandomMod
		add esp, 4
		and eax, 0xffff
		mov edx, 0x20
	L_scan:
		lea ecx, [eax + eax*2]
		lea ecx, [ecx + ecx*4]
		lea ecx, [eax + ecx*4]
		mov bl, byte ptr [ecx*4 + 0x1002a2c2]
		test bl, bl
		je L_found
		dec edx
		inc eax
		and eax, 0x1f
		test edx, edx
		jne L_scan
		xor eax, eax
		pop ebx
		ret
	L_found:
		lea ecx, [eax + eax*2]
		lea edx, [ecx + ecx*4]
		lea ecx, [eax + edx*4]
		mov edx, 0xe
		shl ecx, 2
		lea eax, [ecx + 0x1002a200]
	L_fmul_loop:
		fld dword ptr [eax - 4]
		fmul dScaleFactor
		fstp dword ptr [eax]
		add eax, 0xc
		dec edx
		jne L_fmul_loop
		mov byte ptr [ecx + 0x1002a2c2], 1
		lea eax, [ecx + 0x1002a1d0]
		pop ebx
		ret
	}
}

/* Looks up an alchemy entity in the global table by ID.
 * Returns pointer to the entity's table entry. */

// FUNCTION: SERVER 0x1000c670
// ahm_LookupEntityInTable

int* __cdecl ahm_LookupEntityInTable(int param_1)
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

/* Queries what building type an alchemy entity belongs to.
 * Returns the building type category for alchemy purposes. */

// FUNCTION: SERVER 0x1000c6a0
// ahm_QueryEntityBuildingType

int __cdecl ahm_QueryEntityBuildingType(int param_1)
{
	unsigned short* entity;
	int table_entry;

	entity = gm_StartEntityQuery(*(int*) (param_1 + 0x178), 1, 5);
	if (entity != (unsigned short*) 0) {
		while (table_entry = (int) ahm_LookupEntityInTable(*entity), table_entry == 0) {
			entity = gm_NextEntityQueryMatch();
			if (entity == (unsigned short*) 0) {
				ahm_LookupEntityInTable(0);
				return 0;
			}
		}
		if (*(int*) (table_entry + 0x58) != 1 && *(int*) (table_entry + 0x58) != 2) {
			return 0;
		}
		if (0 < *(int*) ((char*) entity + 0x20)) {
			return 0;
		}
	}
	ahm_LookupEntityInTable(0);
	return 0;
}

/* Calculates the payload size of a command packet based on
 * the command type and field count. Used for buffer allocation
 * and validation. */

// FUNCTION: SERVER 0x1000c710
// GetCommandPayloadSize

/* TODO: Add extern declarations for globals and called functions */

/* Auto-generated Ghidra decompilation */
int GetCommandPayloadSize(unsigned char* param_1)

{
	int entry_size;
	unsigned char* cursor;
	int total_size;
	int count;

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
		cursor = param_1 + (*param_1 == 0x16 ? 0x15 : 0x15);
		total_size = 0x15;
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
	for (count = param_1[0x14]; count > 0; count = count - 1) {
		entry_size = cursor[1] * *cursor + 4;
		total_size = total_size + entry_size;
		cursor = cursor + entry_size;
	}
	return total_size;
}

/* Processes an alchemy entity chain. Iterates linked alchemy
 * entities and applies processing steps (mixing, timing,
 * completion checks). */

// FUNCTION: SERVER 0x1000ca00
// ahm_ProcessEntityChain

int __cdecl ahm_ProcessEntityChain(char* param_1)
{
	char cmd_type;
	int success;
	int handler_ret;
	unsigned char* node;

	success = 1;
	node = *(unsigned char**) (param_1 + 0x95);
	do {
		if (*node == 6) {
			goto check_result;
		}
		handler_ret = PTR_LAB_1002c5a0[*node](node);
		if (handler_ret != 0) {
			success = 0;
		}
		node = *(unsigned char**) (node + 0x95);
	} while (success);
error_path:
	cmd_type = *param_1;
	while (cmd_type != 6) {
		*param_1 = 2;
		param_1 = *(char**) (param_1 + 0x95);
		cmd_type = *param_1;
	}
	*param_1 = 2;
	return 1;
check_result:
	if (!success) {
		goto error_path;
	}
	*param_1 = 1;
	cmd_type = *param_1;
	while (cmd_type != 6) {
		param_1 = *(char**) (param_1 + 0x95);
		cmd_type = *param_1;
	}
	*param_1 = 1;
	return 1;
}

/* Resolves a field value by type from a command packet.
 * Performs entity ID resolution through the global entity
 * tables. Returns the resolved value or 0 on failure. */

// FUNCTION: SERVER 0x1000CA90
// gm_GetFieldByType
__declspec(naked) int __cdecl gm_GetFieldByType(char* p, int type)
{
	(void) p;
	(void) type;
	__asm {
		mov eax, dword ptr [esp + 8]
		cmp eax, -2
		jne L_t3
		mov eax, dword ptr [esp + 4]
		xor ecx, ecx
		mov cl, byte ptr [eax + 3]
		mov eax, ecx
		shl eax, 4
		add eax, ecx
		shl eax, 8
		add eax, ecx
		shl eax, 4
		add eax, ecx
		lea ecx, [eax + eax*8]
		mov eax, dword ptr [ecx*4 + 0x10442d00]
		ret
	L_t3:
		cmp eax, -3
		jne L_t4
		mov edx, dword ptr [esp + 4]
		xor ecx, ecx
		mov cl, byte ptr [edx + 3]
		mov eax, ecx
		shl eax, 4
		add eax, ecx
		shl eax, 8
		add eax, ecx
		shl eax, 4
		add eax, ecx
		lea eax, [eax + eax*8]
		mov eax, dword ptr [eax*4 + 0x10442d04]
		ret
	L_t4:
		cmp eax, -4
		jne L_ret0
		mov edx, dword ptr [esp + 4]
		xor ecx, ecx
		mov cl, byte ptr [edx + 3]
		mov eax, ecx
		shl eax, 4
		add eax, ecx
		shl eax, 8
		add eax, ecx
		shl eax, 4
		add eax, ecx
		lea eax, [eax + eax*8]
		mov eax, dword ptr [eax*4 + 0x10442d08]
	L_ret0:
		ret
	}
}
