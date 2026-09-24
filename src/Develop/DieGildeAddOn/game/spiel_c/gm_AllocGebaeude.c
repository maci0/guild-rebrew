// FUNCTION: GOLDTL 0x5974e0
// SIZE: 1113
// FUNCTION: SERVER 0x100174d0

#include <stdio.h>
#include <stdlib.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

void* __cdecl gm_AllocObjekt(int, int, int);
char* __cdecl gm_AllocRaum(char*, int);
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
int __cdecl gm_CheckEntityType(unsigned char*);
void* __cdecl gm_SearchStruct(void); /* 0x10017210 */
void* __cdecl memset(void* dest, int c, unsigned int size);
void* __cdecl m_AllocTracked(unsigned int size, const char* tag);
int __cdecl gv_AllocGraveyardField(char* geb);
void __cdecl gv_SpawnEntities(char* geb, int param);
void __cdecl gm_SetBuildingWorkerLimits(unsigned char* geb);
int __cdecl gm_GetBuildingTypeCategory(int btype);
void __cdecl gm_AllocBuildingDefaults(unsigned char* geb);

/* The reference builds a frame (push ebp; mov ebp,esp; sub esp,0x410) and
 * addresses the 0x410 scratch buffer off ebp; section 13 of
 * docs/msvc6-c-shapes.md. */
/* The 14 bytes from g_current_year (0x10035880) onward, copied whole
 * into the building at +0x69: the reference emits a struct copy
 * (`lea edx,[esi+0x69]`, stores through edx) from absolute operands. */
#pragma pack(push, 1)
struct blk14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack(pop)

#pragma optimize("y", off)
char* __cdecl gm_AllocGebaeude(int geb_type, int owner)
{
	char* geb;
	/* 0x410-byte locals block: 0x400 log buffer + 4 pointer/int slots. */
	// SIZE 0x410
	struct {
		char msg[0x400];
		char* dest;
		int type_id;
		char* record;
		int flag;
	} s;

	if (g_entity_type_table == 0) {
		return NULL;
	}
	s.flag = 0;
	geb = (char*) gm_SearchStruct();
	if (geb == NULL) {
		LogMessageInternal((char*) 0x10031004, 0x10cb, (char*) 0x10031454, 1);
		return NULL;
	}
	{
		char* rec;
		int nid;
		rec = g_entity_type_table + (unsigned char) geb_type * 0x24d;
		geb[0] = (char) geb_type;
		s.type_id = (unsigned char) geb_type;
		nid = *(int*) 0x10030b6c;
		s.record = rec;
		sprintf(s.msg, (char*) 0x10031438, nid, s.type_id);
	}
	LogMessageInternal((char*) 0x10031004, 0x10d8, s.msg, 8);
	*(int*) (geb + 1) = *(int*) 0x10030b6c;
	*(int*) 0x10030b6c = *(int*) 0x10030b6c + 1;
	*(unsigned short*) (geb + 0x25) = (unsigned short) owner;
	*(unsigned short*) (geb + 0x27) = (unsigned short) owner;
	*(int*) (geb + 0x3d) = 0x64;
	*(int*) (geb + 0x45) = 0x64;
	geb[0x5c] = 0x64;
	*(unsigned short*) (geb + 0x29) = 0;
	*(int*) (geb + 0x2b) = 0;
	geb[0x2f] = 0;
	*(int*) (geb + 0x5d) = 0;
	*(int*) (geb + 0x61) = 0;
	*(int*) (geb + 0x30) = 0;
	*(int*) (geb + 0x39) = 0x7d00;
	*(int*) (geb + 0x41) = 2;
	*(int*) (geb + 0x49) = 0x3f800000;
	*(int*) (geb + 0x95) = -1;
	memset(geb + 0x99, 0, 0x10);
	*(int*) (geb + 0xa5) = -1;
	*(int*) (geb + 0x99) |= 1;
	/* target: mov [ebp+8],0x30; lea eax,[esi+0x65]; mov [ebp-0x10],eax; stos */
	geb_type = 0x30;
	s.dest = geb + 0x65;
	/* The original's fill here is the 24-byte hand-written block-fill prelude
	 * (docs/msvc6-allocator.md Finding 19); no msvc6 C memset spelling emits
	 * it.  Reproduced as a block-fill with ordinary named operands. */
	__asm {
		mov edi, s.dest
		mov ebx, geb_type
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	/* component loop: counter reuses geb_type (ebp+8) */
	{
		/* The target walks a pointer (`lea edi,[record+0x23]`, `add edi,2`
		 * in the for-increment) rather than indexing by the counter, and it
		 * keeps the pointer increment AHEAD of the counter increment.  Both
		 * increments have to be in the header, or the `continue` below skips
		 * the pointer. */
		unsigned short* rec;

		geb_type = 0;
		rec = (unsigned short*) (s.record + 0x23);
		for (; geb_type < 0x40; geb_type++, rec++) {
			unsigned short comp = *rec;
			char* comp_rec;
			unsigned char comp_type;

			if (comp == 0) {
				break;
			}
			if (comp == 0xffff) {
				continue;
			}
			comp_rec = (char*) g_item_def_table + (comp & 0x7fff) * 0x41;
			/* A volatile read is not folded into `[eax+ebx]`: the reference
			 * materialises the address (`mov ecx,eax; add ecx,ebx; mov cl,[ecx]`,
			 * 0x1001765d), and those 3 bytes push the loop's `je` to rel32. */
			comp_type = *(volatile unsigned char*) comp_rec;
			if (comp_type == 2 || comp_type == 6) {
				s.flag = 1;
			}
			if (comp & 0x8000) {
				if (comp_type == 2 || comp_type == 6) {
					/* the reference repeats the store here (0x1001769f) */
					s.flag = 1;
					gm_AllocRaum(geb, comp & 0x7fff);
				} else if (s.flag == 0) {
					gm_AllocObjekt(*(int*) (geb + 1), comp & 0x7fff, 1);
				}
			}
		}
	}
	{
		/* A register local: the reference never stores the query pointer. */
		unsigned short* q;

		q = gm_ff_Objekt(*(int*) (geb + 0x5d), 1, 4, 2);
		while (q != NULL) {
			if (*q != 0xfd) {
				*(unsigned short*) (geb + 0x29) = *q;
				break;
			}
			q = (unsigned short*) gm_NextEntityQueryMatch();
		}
		q = gm_SetupEntityQuery((unsigned char*) geb);
		if (q != NULL)
			*(unsigned short*) (geb + 0x29) = *q;
	}
	if (gm_CheckEntityType((unsigned char*) geb) != 0)
		*(int*) (geb + 0x30) = 0x1388;
	/* building-type switch (jump table 0x10017890 / byte map 0x100178bc). */
	switch (s.type_id) {
	case 4:
	case 5:
	case 6:
	case 7:
		*(struct blk14*) (geb + 0x69) = *(struct blk14*) &g_current_year;
		if ((unsigned short) owner != 0xffff)
			*(int*) (geb + 0x65) =
			    *(int*) ((char*) 0x100358a4 + (unsigned short) owner * 0x21c);
		else
			*(int*) (geb + 0x65) = -1;
		break;
	case 0x14:
	case 0x15:
	case 0x16:
		{
			/* The reference keeps this pointer in a register: there is no
			 * store of it anywhere, and the four field stores issue from the
			 * same register with no reload between them.  A local whose
			 * address is never taken cannot be aliased by a store through
			 * itself; an address-taken struct member can, which is why the
			 * previous `s.record` spelling reloaded [ebp-8] three times. */
			char* rec = (char*) gm_AllocObjekt(*(int*) (geb + 1), 0x1b5, 1);
			if (rec != NULL) {
				rec[0x22] = 0;
				rec[0x1c] = (char) -1;
				rec[0x1d] = (char) -1;
				*(int*) (rec + 0x1e) = -1;
			}
		}
		break;
	case 0x47:
		*(int*) (geb + 0x30) = 0x13880;
		break;
	case 0x1e:
		/* The reference writes the allocation only to geb+0x71 and then reads
		 * the pointer back out of that field for every use: the first store
		 * issues from the call's own result (still in eax), the second
		 * reloads `mov ecx,[esi+0x71]` because the intervening char store may
		 * alias the field.  Keeping a second copy in `s.record` was an extra
		 * store plus three extra reloads. */
		*(int*) (geb + 0x71) = (int) m_AllocTracked(0x600, (const char*) 0x10031428);
		geb_type = 0;
		while (geb_type < 0x600) {
			geb_type += 0x18;
			*((char*) *(int*) (geb + 0x71) + (geb_type - 0xb)) = (char) 0xff;
			*(int*) ((char*) *(int*) (geb + 0x71) + (geb_type - 4)) = 0;
		}
		/* fall through into 0x1f/0x20 stores */
	case 0x1f:
	case 0x20:
		*(int*) (geb + 0x30) = 0x64;
		*(int*) (geb + 0x49) = 0x3f4ccccd;
		break;
	case 0x35:
	case 0x36:
	case 0x37:
		*(int*) (geb + 0x65) = 0;
		*(unsigned short*) (geb + 0x69) = 0;
		*(unsigned short*) (geb + 0x6b) = 0;
		*(int*) (geb + 0x6d) = 0;
		break;
	case 0xb:
	case 0xc:
	case 0xd:
		*(int*) (geb + 0x65) = -1;
		break;
	case 0xe:
	case 0xf:
	case 0x10:
		*(int*) (geb + 0x65) = 0xa;
		*(int*) (geb + 0x69) = 3;
		*(int*) (geb + 0x6d) = 5;
		break;
	case 0x48:
	case 0x49:
	case 0x4a:
		*(int*) (geb + 0x65) = gv_AllocGraveyardField(geb);
		gv_SpawnEntities(geb, 3);
		break;
	case 0x4b:
	case 0x4c:
	case 0x4d:
		{
			char* rec = (char*) m_AllocTracked(0x3c, (const char*) 0x1002d504);
			*(int*) (geb + 0x65) = (int) rec;
			*(int*) rec = -1;
		}
		break;
	}
	if (geb[0] == 0x26)
		*(unsigned short*) (geb + 0x29) = 0x10e;
	gm_SetBuildingWorkerLimits((unsigned char*) geb);
	gm_GetBuildingTypeCategory((unsigned char) geb[0]);
	gm_AllocBuildingDefaults((unsigned char*) geb);
	return geb;
}
#pragma optimize("", on)

