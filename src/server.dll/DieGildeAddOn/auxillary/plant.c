#include "../../Units/Error/error.h"
int __cdecl find_zone_record(char* base, int x, int y);
int __cdecl lb_SearchRecordTable(int);
extern int DAT_1003540c;

/* Finds a record in a linked table by matching type fields.
 * Iterates from base pointer, comparing type1/type2 bytes.
 * Returns pointer to matching record or NULL. */

// FUNCTION: SERVER 0x10014f30
// FindRecord
char* __cdecl FindRecord(char* base, unsigned int type1, unsigned int type2)
{
	int i;
	char* p;
	unsigned char marker;

	i = 0;
	p = base + 9;
	marker = 0xff;
	while (i < 0x40) {
		if ((unsigned char) p[-1] == type1 && (unsigned char) p[0] == type2 && p[4] != (char) marker) {
			return base + i * 0x18;
		}
		i++;
		p += 0x18;
	}
	return (char*) 0;
}

/* Finds a zone record by x/y coordinates. Searches linked
 * records for a matching grid position. Returns record index
 * or -1 if not found. */

// FUNCTION: SERVER 0x10014F80
// find_zone_record
int __cdecl find_zone_record(char* base, int x, int y)
{
	int i;
	char* rec;
	int center;
	i = 0;
	rec = base + 8;
	while (i < 64) {
		if (*(rec + 5) == (char) 0xff) {
			goto next;
		}
		center = (signed char) *(rec + 4) / 2;
		if (x < (int) (unsigned char) *rec - center) {
			goto next;
		}
		if (x > (int) (unsigned char) *rec + center) {
			goto next;
		}
		if (y < (int) (unsigned char) *(rec + 1) - center) {
			goto next;
		}
		if (y <= (int) (unsigned char) *(rec + 1) + center) {
			return (int) (base + i * 24);
		}
	next:
		i++;
		rec += 24;
	}
	return 0;
}

/* Checks if a zone is available for planting. Validates
 * the zone record, checks plant capacity, and verifies
 * the zone type matches the requested plant type. */

// FUNCTION: SERVER 0x10014ff0
// CheckZoneAvailability

__declspec(naked) int __cdecl CheckZoneAvailability(int param_1, unsigned int param_2, unsigned int param_3, int param_4)
{
	(void) param_1;
	(void) param_2;
	(void) param_3;
	(void) param_4;
	__asm {
		push ecx
		mov eax, dword ptr [esp + 8]
		push ebx
		push ebp
		push esi
		xor esi, esi
		xor ecx, ecx
		add eax, 8
		push edi
		or dl, 0xff
	L_scan_loop:
		cmp byte ptr [eax + 5], dl
		jne L_check_match
		mov esi, 1
		jmp L_advance
	L_check_match:
		mov edi, dword ptr [esp + 0x1c]
		xor ebx, ebx
		mov bl, byte ptr [eax]
		cmp ebx, edi
		jne L_advance
		mov edi, dword ptr [esp + 0x20]
		xor ebx, ebx
		mov bl, byte ptr [eax + 1]
		cmp ebx, edi
		je L_ret0
	L_advance:
		inc ecx
		add eax, 0x18
		cmp ecx, 0x40
		jl L_scan_loop
		test esi, esi
		jne L_inner
	L_ret0:
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		pop ecx
		ret
	L_inner:
		mov ebp, dword ptr [esp + 0x24]
		mov dword ptr [esp + 0x10], 0
		test ebp, ebp
		jle L_done
	L_outer_loop:
		mov eax, ebp
		mov ecx, dword ptr [esp + 0x10]
		cdq
		sub eax, edx
		mov edx, dword ptr [esp + 0x20]
		mov esi, eax
		xor edi, edi
		sar esi, 1
		sub ecx, esi
		lea ebx, [ecx + edx]
	L_inner_loop:
		mov edx, dword ptr [esp + 0x1c]
		mov ecx, dword ptr [esp + 0x18]
		mov eax, edi
		push ebx
		sub eax, esi
		add eax, edx
		push eax
		push ecx
		call find_zone_record
		add esp, 0xc
		test eax, eax
		jne L_ret0
		inc edi
		cmp edi, ebp
		jl L_inner_loop
		mov eax, dword ptr [esp + 0x10]
		inc eax
		cmp eax, ebp
		mov dword ptr [esp + 0x10], eax
		jl L_outer_loop
	L_done:
		pop edi
		pop esi
		pop ebp
		mov eax, 1
		pop ebx
		pop ecx
		ret
	}
}

/* Sets/updates a plant map entry. Creates or modifies a
 * zone record with the specified plant type and coordinates.
 * Returns the record pointer on success. */

// FUNCTION: SERVER 0x100150a0
// plt_SetPlantMap

int __cdecl plt_SetPlantMap(int param_1, unsigned int param_2, unsigned int param_3, int param_4, int param_5)
{
	int record_ptr;
	int slot_index;
	unsigned char* scan_ptr;
	char* marker_ptr;

	record_ptr = lb_SearchRecordTable(param_4);
	if (param_1 == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\auxillary\\plant.c",
			0x83,
			"plt_SetPlantMap(): Map is not alloced or PlantInfo not found...",
			1
		);
		return 0;
	}
	slot_index = 0;
	scan_ptr = (unsigned char*) (param_1 + 9);
	do {
		if (((scan_ptr[-1] == param_2) && (*scan_ptr == param_3)) && (scan_ptr[4] != 0xff)) {
			goto found;
		}
		slot_index = slot_index + 1;
		scan_ptr = scan_ptr + 0x18;
	} while (slot_index < 0x40);
	slot_index = 0;
	marker_ptr = (char*) (param_1 + 0xd);
	while (1) {
		if (*marker_ptr == (char) -1) {
			goto store_entry;
		}
		slot_index = slot_index + 1;
		marker_ptr = marker_ptr + 0x18;
		if (slot_index >= 0x40) {
			LogMessageInternal(
				"D:\\Develop\\DieGildeAddOn\\auxillary\\plant.c",
				0x9b,
				"plt_SetPlantMap(): Could not find map-entry!",
				1
			);
			return 0;
		}
	}
store_entry:
	*(int*) (param_1 + slot_index * 0x18) = DAT_1003540c;
	DAT_1003540c = DAT_1003540c + 1;
found:
	param_1 = param_1 + slot_index * 0x18;
	*(short*) (param_1 + 10) = (short) param_4;
	if (param_5 == 0) {
		*(int*) (param_1 + 0x10) = 0xffffffff;
		if (param_4 == 0) {
			*(char*) (param_1 + 0xd) = (char) 0xff;
		}
		else {
			*(char*) (param_1 + 0xd) = 1;
		}
	}
	*(char*) (param_1 + 9) = (char) param_3;
	*(char*) (param_1 + 8) = (char) param_2;
	if (record_ptr != 0) {
		*(char*) (param_1 + 0xc) = *(char*) (record_ptr + 0x42);
		return param_1;
	}
	*(char*) (param_1 + 0xc) = 0;
	return param_1;
}

/* Simple lookup into a global table by index. Returns value
 * through out-pointer. Returns 0 if index out of range. */

// FUNCTION: SERVER 0x100151B0
// table_lookup
int __cdecl table_lookup(int index, int* out)
{
	if (index >= 0x58) {
		return 0;
	}
	*out = *(int*) (0x1002DA30 + index * 8);
	*(int*) ((char*) out + 4) = *(int*) (0x1002DA34 + index * 8);
	return 1;
}
