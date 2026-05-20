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

__declspec(naked) int __cdecl CheckZoneAvailability(int zone_table, unsigned int x, unsigned int y, int zone_type)
{
	(void) zone_table;
	(void) x;
	(void) y;
	(void) zone_type;
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

extern char s_plt_SetPlantMap____Could_not_fin_1002d990[];
extern char s_D__Develop_DieGildeAddOn_auxilla_1002d9c0[];
extern char s_plt_SetPlantMap____Map_is_not_al_1002d9ec[];

// FUNCTION: SERVER 0x100150a0
// plt_SetPlantMap

__declspec(naked) int __cdecl plt_SetPlantMap(int zone_table, unsigned int x, unsigned int y, int zone_type, int extra)
{
	(void) zone_table;
	(void) x;
	(void) y;
	(void) zone_type;
	(void) extra;
	__asm {
		push ebx
		push ebp
		mov ebp, dword ptr [esp + 0x18]
		push esi
		push edi
		push ebp
		call lb_SearchRecordTable
		mov edi, dword ptr [esp + 0x18]
		add esp, 4
		test edi, edi
		mov dword ptr [esp + 0x20], eax
		jne L_have_map
		push 1
		push offset s_plt_SetPlantMap____Map_is_not_al_1002d9ec
		push 0x83
		push offset s_D__Develop_DieGildeAddOn_auxilla_1002d9c0
		call LogMessageInternal
		add esp, 0x10
		xor eax, eax
		pop edi
		pop esi
		pop ebp
		pop ebx
		ret
	L_have_map:
		xor ecx, ecx
		lea esi, [edi + 9]
		or edx, 0xffffffff
	L_scan1:
		mov ebx, dword ptr [esp + 0x18]
		xor eax, eax
		mov al, byte ptr [esi - 1]
		cmp eax, ebx
		jne L_scan1_next
		mov ebx, dword ptr [esp + 0x1c]
		xor eax, eax
		mov al, byte ptr [esi]
		cmp eax, ebx
		jne L_scan1_next
		cmp byte ptr [esi + 4], dl
		jne L_apply
	L_scan1_next:
		inc ecx
		add esi, 0x18
		cmp ecx, 0x40
		jl L_scan1
		xor ecx, ecx
		lea eax, [edi + 0xd]
	L_scan2:
		cmp byte ptr [eax], dl
		je L_store_new
		inc ecx
		add eax, 0x18
		cmp ecx, 0x40
		jl L_scan2
		push 1
		push offset s_plt_SetPlantMap____Could_not_fin_1002d990
		push 0x9b
		push offset s_D__Develop_DieGildeAddOn_auxilla_1002d9c0
		call LogMessageInternal
		add esp, 0x10
		xor eax, eax
		pop edi
		pop esi
		pop ebp
		pop ebx
		ret
	L_store_new:
		mov esi, dword ptr [DAT_1003540c]
		lea eax, [ecx + ecx*2]
		mov dword ptr [edi + eax*8], esi
		mov eax, dword ptr [DAT_1003540c]
		inc eax
		mov dword ptr [DAT_1003540c], eax
	L_apply:
		lea ecx, [ecx + ecx*2]
		lea eax, [edi + ecx*8]
		mov ecx, dword ptr [esp + 0x24]
		test ecx, ecx
		mov word ptr [eax + 0xa], bp
		jne L_set_xy
		test ebp, ebp
		mov dword ptr [eax + 0x10], edx
		je L_set_ffmark
		mov byte ptr [eax + 0xd], 1
		jmp L_set_xy
	L_set_ffmark:
		mov byte ptr [eax + 0xd], dl
	L_set_xy:
		mov cl, byte ptr [esp + 0x1c]
		mov dl, byte ptr [esp + 0x18]
		mov byte ptr [eax + 9], cl
		mov ecx, dword ptr [esp + 0x20]
		test ecx, ecx
		mov byte ptr [eax + 8], dl
		je L_no_record
		mov dl, byte ptr [ecx + 0x42]
		pop edi
		pop esi
		pop ebp
		mov byte ptr [eax + 0xc], dl
		pop ebx
		ret
	L_no_record:
		pop edi
		pop esi
		pop ebp
		mov byte ptr [eax + 0xc], 0
		pop ebx
		ret
	}
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
