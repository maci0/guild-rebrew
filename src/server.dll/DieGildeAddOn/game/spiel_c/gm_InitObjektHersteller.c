// FUNCTION: SERVER 0x100156c0
#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <string.h>
typedef int(__cdecl* ALLOCFN)(int, int, int);

#pragma intrinsic(memcpy, memset)

extern char* g_entity_table; /* 0x101de450 */

// CFLAGS: /O2 /Gd

/* Game function - gm_InitObjektHersteller (initialize object manufacturers)
 *
 * NOTE: NEAR_MATCHING (109/642 exact, rest structural). The control flow,
 * constants, and call sequence are correct, but msvc6's register allocation
 * and scheduler diverge from the original binary: original keeps record_base
 * in ebx and byte_offset in ebp (ours: ebp/esi, zero in esi), original spills
 * mfr_type to a 9th stack slot (frame 0x24 vs ours 0x20), and the original
 * groups the 4 arg pushes of the 0x46d LogMessageInternal call before the 10
 * constant stores while our build interleaves them. The early prev_type/record
 * zero stores are kept by the original but eliminated as dead here. No source
 * ordering tried (decl order, init placement, store-before/after-call)
 * reproduces the original allocation; would need a compiler-build that
 * schedules like the original. */

void __cdecl gm_InitObjektHersteller(void)
{
	int* p;
	int i;
	char* record_base;
	int byte_offset;
	int record_index;
	int same_count;
	int run_length;
	int prev_type;
	char* record;
	int entity_type;

	/* Zero manufacturer table (25 ints) */
	p = (int*) 0x10139820;
	for (i = 0x19; i != 0; i--) {
		*p = 0;
		p++;
	}

	same_count = 0;
	run_length = 0;

	LogMessageInternal((char*) 0x10031004, 0x458, (char*) 0x1003102c, 1);

	*(int*) 0x10139840 = 0x2f;
	*(int*) 0x1013983c = 0x32;
	*(int*) 0x10139838 = 0x29;
	*(int*) 0x10139848 = 0x21;
	*(int*) 0x10139858 = 0x1e;
	*(int*) 0x1013985c = 0x1f;
	*(int*) 0x10139860 = 0x20;
	*(int*) 0x1013984c = 0x17;
	*(int*) 0x10139850 = 0x35;
	*(int*) 0x10139844 = 0x14;

	LogMessageInternal((char*) 0x10031004, 0x46d, (char*) 0x10030fb0, 1);

	record_base = *(char**) 0x100a8c30;

	/* Fill ObjektNr2MinimalHersteller with 0x58 (732 ints) */
	p = (int*) 0x101dd8e0;
	for (i = 0x2dc; i != 0; i--) {
		*p = 0x58;
		p++;
	}

	record_index = 0;
	byte_offset = 0;
	prev_type = 0x58;

	do {
		record = record_base + byte_offset;
		entity_type = *(unsigned char*) record;

		if (entity_type == prev_type) {
			goto same_type;
		}

		same_count = 0;
		run_length = 0;
		prev_type = entity_type;

		if (byte_offset < 0xca78) {
			int idx;
			char* scan = record;
			for (idx = record_index; idx < 0x58; idx++) {
				if (*(unsigned char*) scan != (unsigned char) entity_type) {
					break;
				}
				run_length++;
				scan += 0x24d;
			}
		}
		goto after_branch;

	same_type:
		same_count++;

	after_branch:
		LogMessageInternal((char*) 0x10031004, 0x490, (char*) 0x10030f54, 1);

		record_base = *(char**) 0x100a8c30;

		if (*(unsigned char*) (record + 0x22) != 0) {
			unsigned short* comp_ptr;
			int comp_count;

			comp_ptr = (unsigned short*) (record + 0x23);
			comp_count = 0;

			do {
				unsigned short entry;

				entry = *comp_ptr;

				if (entry != 0xffff) {
					int ent_idx;
					int mfr_start;
					char* mfr_record;
					int mfr_type;
					int consec;
					int new_val;

					ent_idx = entry & 0x7fff;
					mfr_start = *(unsigned char*) (g_entity_table + (ent_idx << 6) + ent_idx + 0x21);
					mfr_start = *(int*) (mfr_start * 4 + 0x10139820);

					mfr_record = record_base + mfr_start * 0x24d;
					mfr_type = *(unsigned char*) mfr_record;
					consec = 0;

					if (mfr_start < 0x58) {
						int j;
						char* scan = mfr_record;
						for (j = mfr_start; j < 0x58; j++) {
							if (*(unsigned char*) scan != (unsigned char) mfr_type) {
								break;
							}
							consec++;
							scan += 0x24d;
						}
					}

					new_val = mfr_start + (consec * same_count) / run_length;
					if (new_val < *(int*) (ent_idx * 4 + 0x101dd8e0)) {
						*(int*) (ent_idx * 4 + 0x101dd8e0) = new_val;
					}
				}

				comp_count++;
				comp_ptr++;
			} while (comp_count < *(unsigned char*) (record + 0x22));
		}

		byte_offset += 0x24d;
		record_index++;
	} while (byte_offset < 0xca78);

	LogMessageInternal((char*) 0x10031004, 0x4ae, (char*) 0x10030eec, 1);

	{
		int* min_ptr;
		unsigned char* type_ptr;

		min_ptr = (int*) 0x101dd8e0;
		type_ptr = (unsigned char*) (g_entity_table + 0x21);

		do {
			if (*min_ptr == 0x58) {
				*min_ptr = *(int*) (*type_ptr * 4 + 0x10139820);
			}
			min_ptr++;
			type_ptr += 0x41;
		} while ((int) min_ptr < 0x101de450);
	}
}


