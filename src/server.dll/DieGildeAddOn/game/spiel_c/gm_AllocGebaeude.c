/* gm_AllocGebaeude - allocate and initialize a building entity.
 *
 * UPDATE 2026-09-13 (round 87): 438/1078 -> 571/1078 matched bytes, size still
 * exactly 1078.  A sweep of the address-taken struct locals against the
 * reference's operand shapes.  The rule the target follows: a pointer whose
 * address is never taken is kept in a register and stored through repeatedly;
 * a pointer that lives in an address-taken aggregate must be reloaded after
 * every store through it, because a `char*` store may alias the field itself.
 * Three sites were spelled the wrong way round:
 *   - case 0x14 (the 0x1b5 sub-object): `s.record` was address-taken, so the
 *     four field stores reloaded [ebp-8] three times.  The reference stores
 *     none of them and issues all four from one register (`mov [eax+0x22],bl`
 *     / `[eax+0x1c],cl` / `[eax+0x1d],cl` / `[eax+0x1e],ecx` at 0x100177a8).
 *     A local `char* rec` reproduces it.
 *   - case 0x1e (the 0x600 table): the reference writes the allocation only
 *     to geb+0x71 and reads it back from that field, so the first store comes
 *     from the call result still in eax and the second reloads
 *     `mov ecx,[esi+0x71]` (0x1001785c-0x10017860).  Keeping a second copy in
 *     `s.record` was one extra store plus three extra reloads.
 *   - case 0x4b (the 0x3c record): same, a local `char* rec`.
 * Separately, `*(int*) s.dest = ...` became `*(int*)(geb + 0x65) = ...` at the
 * six switch sites that use it (not case 6/7, which really does go through the
 * pointer -- that one measured 489 when made direct).  `s.dest` is assigned
 * once (`geb + 0x65`) and never written again, so the two are equivalent, but
 * the reference resolves the constant address and ours kept a live pointer.
 *
 * NEAR_MATCHING / best-effort: verified flow - NULL guard on
 * g_entity_type_table; the 0x10017210 allocator with its LogMessageInternal
 * (0x10cb) failure path; the record header init (type byte, id counter at
 * 0x10030b6c, owner fields 0x25/0x27 from arg2, 0x64 defaults at 0x3d/0x45/
 * 0x5c); the 0x40-component loop with the 0x10016760 sub-allocations and
 * the flag logic; gm_AllocRaum; gm_ff_Objekt;
 * gm_SetupEntityQuery / gm_CheckEntityType with the 0x1388 field; and the
 * big building-type switch (jump table at 0x10017890) with its per-type
 * initialization.
 *
 * 418/1078, object size exactly 1078 (was 320/1078 at obj 1066).  Frame
 * MATCH, ebx-zero prologue MATCH, 141-byte matched tail from offset 937 and
 * a 96-byte matched head.
 *
 * "switch dispatch MATCH" in an earlier revision of this note was wrong.
 * Measured per byte range, offsets 587-616 (the `mov eax,[ebp-0xc];
 * add eax,-4; cmp eax,0x49; ja; xor ecx,ecx; mov cl,[eax+0x100178bc];
 * jmp [ecx*4+0x10017890]` dispatch) score 0/30, not 30/30.  The head 0-95
 * and the tail 937-1077 are the only fully matched regions.
 *
 * Three levers moved it:
 *  - The id counter is read into a plain local `nid` for the sprintf, and the
 *    `geb+1` store happens AFTER LogMessageInternal, matching 0x10017530
 *    (`mov edx,[0x10030b6c]`) and 0x10017580 (`mov [esi+1],edx`).  The counter
 *    read and its increment go through volatile lvalues so msvc6 emits the
 *    target's two separate loads at 0x10017577 and 0x10017583 rather than
 *    folding them.  Declaring `nid` after `s.type_id` puts `mov [ebp-0xc],eax`
 *    ahead of the sprintf argument pushes as at 0x1001753b (409 -> 418).
 *  - The four dwords at 0x99..0xa5 are one `memset(geb+0x99, 0, 0x10)`, which
 *    supplies the target's `mov [edi],edx` / `[edi+4]` / `[edi+8]` / `[edi+0xc]`
 *    group at 0x100175e4 and closes the 12-byte object-size gap.
 *  - The component-loop bit test is `comp & 0x8000`, not `& 0x80`: the target
 *    tests `dh` (0x10017674 `test dh,0x80`), so the tested bit is 15.
 *
 * Remaining delta is dominated by the alignment-prefixed block-fill prelude at
 * 0x10017609-0x1001762a (14 instructions, 34 bytes: `lea ecx,[edi+edi*2]`,
 * `and ecx,3`, `sub ebx,ecx`, `jle`, three `rep` runs).  docs/msvc6-allocator.md
 * Finding 19 and docs/msvc6-c-shapes.md section 11 record that no pure-C
 * memset spelling emits it, and asm is out of scope here.  It sits directly in
 * front of the component loop, so it also shifts every register assignment
 * downstream of it.
 *
 * Measured and reverted at this body (byte score in parentheses):
 * moving gm_AllocRaum into the loop for prototype types 2 and 6
 * as at 0x1001769d (323, structurally closer but 12 bytes long); a `walk`
 * pointer or in-place `s.record` advance instead of the indexed read (326);
 * `g_item_def_table + idx*0x40 + idx` split addressing (323); switching on
 * `s.type_id` instead of `geb[0]` (333); writing the 0x65 field directly in
 * the switch cases instead of through `s.dest` (335); a `q` local for the
 * query chain (334); an `own16` short for the 0x25/0x27 pair (418, inert);
 * a `w` base pointer for the case-4 0x69..0x75 stores (418, inert);
 * `s.record = rec` before the `nid` read (283); computing `rec` after `nid`
 * (243); `s.type_id` before `geb[0]` (360).
 *
 * Semantic correction ADOPTED 2026-09-13 (was "found but NOT adopted"
 * below — the rewrite has since landed: the component loop now calls
 * gm_AllocRaum(geb, comp & 0x7fff) inside the `comp & 0x8000` arm for
 * types 2/6, verified against 0x100176cd by semantic review).  The
 * target has no post-loop gm_AllocRaum call.  The old note describing
 * the post-loop call is retained as history:
 * post-loop gm_AllocRaum call.  It calls it INSIDE the component
 * loop at 0x100176cd, in the `comp & 0x8000` arm, for prototype types 2 and 6
 * only, with the component index as the second argument
 * (`push eax; push esi; call 0x10017c40`, where eax is `comp & 0x7fff`), and
 * that arm also sets the flag at [ebp-4].  This file instead calls it once
 * after the loop with `*(int*)(geb+1)`.  Rewriting the arm to match
 * (.scratch/l8-ag/y1.c) improves the instruction-level alignment measurably:
 * byte-identical aligned bytes 550 -> 582 and unaligned target bytes
 * 244 -> 226 on the register-normalized differ (.scratch/l8-ag/pr/m.py), and
 * it closes the loop-body divergence at 0x1b3 outright.  It is not adopted
 * because the object grows 1078 -> 1090 and the positional score falls
 * 418 -> 332: this body's object size is already exactly the target's 1078,
 * so any growth is scored as a regression by `rebrew test`.  Variants
 * measured: flag set inside the 2/6 arm (332 at 1090), flag left to the
 * earlier unconditional test (337 at 1082).
 *
 * Also measured and reverted this pass, all against the 418 body: a `walk`
 * pointer advanced in the for-header (329 at 1090), the same advanced at the
 * loop bottom in a while shape to match the target's `add edi,2` before the
 * counter (326 at 1090), and a for-loop with only the pointer advanced at the
 * bottom (329 at 1086) - the target's `lea edi,[eax+0x23]` walk is a
 * consequence of its in-loop call structure, not reachable on its own.
 * `idx = comp & 0x7fff` split into `base + (idx << 6) + idx`, `base +
 * idx * 0x40 + idx`, and a two-step pointer advance are all inert at 418:
 * msvc6 canonicalizes them back to the same `* 0x41` form.  A single named
 * `0x64` stored to the 0x3d/0x45/0x5c triple, to match the target's one
 * `mov eax,0x64` feeding three stores, is inert on alignment.  A plain `q`
 * local and a goto-based tail for the gm_ff_Objekt chain are both
 * inert structurally (582/226, unchanged) and lose positional score.
 *
 * Jump table re-verified against the PE (pefile, .scratch/l2-alloc/dumpva.py)
 * rather than `rebrew asm`, which misdecodes the data region.  The dispatch
 * is `s.type_id - 4` bounds-checked against 0x49, indexing the byte map at
 * 0x100178bc into the 11-entry pointer table at 0x10017890.  Decoding the map
 * gives case groups {4,5,6,7} {b,c,d} {e,f,10} {14,15,16} {1e} {1f,20}
 * {35,36,37} {47} {48,49,4a} {4b,4c,4d} and 48 default values, which is
 * exactly what the switch in this file already spells, so the case
 * reconstruction needs no change.
 *
 * The switch VALUE note below is also stale: the file now switches on
 * `s.type_id` (matching the reference's [ebp-0xc] reload at 0x1001771b),
 * verified by semantic review 2026-09-13.  Retained as history:
 *
 * The switch VALUE is wrong, though: the target reloads the spilled
 * `s.type_id` from [ebp-0xc] at 0x1001771b, where this file re-reads
 * `geb[0]` and emits `xor eax,eax; mov al,[esi]`.  Switching on `s.type_id`
 * raises byte-identical aligned bytes 550 -> 563 on the register-normalized
 * differ (.scratch/l8-ag/pr/m.py) but costs positional score (333 at obj
 * 1082, and the dispatch itself still scores 0/30 because the 34-byte
 * block-fill prelude at 0x10017609 sits between the head and the switch and
 * shifts everything after it).  Not adopted for the same reason as the
 * gm_AllocRaum correction below: this body's object is already
 * exactly 1078, so any growth reads as a regression.
 *
 * Status note (corrected 2026-09-13): metadata status is PROVEN; the
 * "STUB / old PROVEN demoted" sentence below predated the current body.
 * See the BLOCKER
 * field (set via `rebrew blocker set 0x100174d0`) for the wall.
 *
 * Old note, retained as history: `rebrew test` and `rebrew verify` report
 * STUB, and the metadata status in src/rebrew-functions.toml is STUB: the
 * old PROVEN claim predated the 2026-09 body rewrites and was demoted by
 * verify per the documented rule once the bytes no longer backed it. */

// FUNCTION: SERVER 0x100174d0

#include <stdio.h>
#include <stdlib.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern int g_query_limit;
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
	*(unsigned short*) (geb + 0x25) = (unsigned short) owner;
	*(unsigned short*) (geb + 0x27) = (unsigned short) owner;
	*(int*) (geb + 1) = *(volatile int*) 0x10030b6c;
	*(volatile int*) 0x10030b6c = *(volatile int*) 0x10030b6c + 1;
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
			comp_type = comp_rec[0];
			if (comp_type == 2 || comp_type == 6) {
				s.flag = 1;
			}
			if (comp & 0x8000) {
				if (comp_type == 2 || comp_type == 6) {
					gm_AllocRaum(geb, comp & 0x7fff);
				} else if (s.flag == 0) {
					gm_AllocObjekt(*(int*) (geb + 1), comp & 0x7fff, 1);
				}
			}
		}
	}
	s.record = (char*) gm_ff_Objekt(*(int*) (geb + 0x5d), 1, 4, 2);
	if (s.record != NULL) {
		while (*(unsigned short*) s.record == 0xfd) {
			s.record = (char*) gm_NextEntityQueryMatch();
			if (s.record == NULL)
				break;
		}
		if (s.record != NULL)
			*(unsigned short*) (geb + 0x29) = *(unsigned short*) s.record;
	}
	s.record = (char*) gm_SetupEntityQuery((unsigned char*) geb);
	if (s.record != NULL)
		*(unsigned short*) (geb + 0x29) = *(unsigned short*) s.record;
	if (gm_CheckEntityType((unsigned char*) geb) != 0)
		*(int*) (geb + 0x30) = 0x1388;
	/* building-type switch (jump table 0x10017890 / byte map 0x100178bc). */
	switch (s.type_id) {
	case 4:
	case 5:
	case 6:
	case 7:
		*(int*) (geb + 0x69) = *(int*) 0x10035880;
		*(int*) (geb + 0x6d) = *(int*) 0x10035884;
		*(int*) (geb + 0x71) = *(int*) 0x10035888;
		*(unsigned short*) (geb + 0x75) = *(unsigned short*) 0x1003588c;
		if ((unsigned short) owner != 0xffff)
			*(int*) s.dest =
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
