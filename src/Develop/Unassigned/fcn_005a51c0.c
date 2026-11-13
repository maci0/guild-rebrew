#include <string.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* g_77255c;

void __cdecl fcn_00469c40(int, int, int);

/* Slot scan + descending name sort + exit-loop render.
 * Return contract: int, returns 0. Native leaves EAX as leftover (no
 * xor eax on any exit); the sole observed caller at 0x005a5744 ignores
 * EAX (overwrites at 0x005a574c). Return 0 documented as scoped
 * limitation, not native-evidenced void. */
/* ADDRESS: GOLDTL 0x005a51c0 */
int __cdecl fcn_005a51c0(unsigned char* entity)
{
	int* p;
	int i;
	int slot;
	int k;
	int j;
	int remaining;
	char* slot_ptr;
	char* prev_ptr;
	char* next_field;
	char* next_record;
	unsigned short sort_key;
	int slot_val;
	unsigned char* byte_idx;
	int cl;
	char name_a[0x80];
	char name_b[0x80];
	char tmp[0x1c];
	int* gbase;
	int* obj_tbl;
	int off;
	int count;
	char* str;
	int cmp;

	slot = 0;
	p = (int*) (entity + 0x1a4);
	for (i = 0xf; i >= 0; i--) {
		if (p[3] != 0 && p[0] != -1) {
			slot = i + 1;
			break;
		}
		p = (int*) ((char*) p - 0x1c);
	}
	if (slot <= 0)
		return 0;
	slot_ptr = (char*) entity + 0xc;
	for (k = 1; k < slot; k++) {
		remaining = slot - k;
		prev_ptr = slot_ptr - 0xc;
		next_field = slot_ptr + 0x1c;
		j = remaining;
		while (j > 0) {
			byte_idx = (unsigned char*) 0x773d75;
			cl = *byte_idx;
			sort_key = *(unsigned short*) (0x8680b4 + cl * 0x2f4);
			slot_val = *(int*) slot_ptr;
			if (slot_val == (int) sort_key) {
				*(int*) name_a = *(int*) 0x6aac64;
				*(int*) (name_a + 4) = *(int*) 0x6aac68;
				*(unsigned short*) (name_a + 8) = *(unsigned short*) 0x6aac6c;
			} else if (slot_val == 0) {
				*(int*) name_a = *(int*) 0x6aac58;
				*(int*) (name_a + 4) = *(int*) 0x6aac5c;
				*(unsigned short*) (name_a + 8) = *(unsigned short*) 0x6aac60;
			} else {
				str = *(char**) (0x14a79c0 + slot_val * 8);
				strcpy(name_a, str);
			}
			slot_val = *(int*) next_field;
			if (slot_val == (int) sort_key) {
				*(int*) name_b = *(int*) 0x6aac64;
				*(int*) (name_b + 4) = *(int*) 0x6aac68;
				*(unsigned short*) (name_b + 8) = *(unsigned short*) 0x6aac6c;
			} else if (slot_val == 0) {
				*(int*) name_b = *(int*) 0x6aac58;
				*(int*) (name_b + 4) = *(int*) 0x6aac5c;
				*(unsigned short*) (name_b + 8) = *(unsigned short*) 0x6aac60;
			} else {
				str = *(char**) (0x14a79c0 + slot_val * 8);
				strcpy(name_b, str);
			}
			cmp = strcmp(name_a, name_b);
			if (cmp == 1) {
				next_record = next_field - 0xc;
				memcpy(tmp, prev_ptr, 0x1c);
				memcpy(prev_ptr, next_record, 0x1c);
				memcpy(next_record, tmp, 0x1c);
			}
			next_field += 0x1c;
			j--;
		}
		slot_ptr += 0x1c;
	}
	p = (int*) entity;
	off = 0;
	count = slot;
	while (count > 0) {
		int owner;
		int rec1;
		owner = p[0];
		rec1 = p[1];
		if (owner != -1) {
			gbase = (int*) g_77255c;
			obj_tbl = (int*) g_1015ea0;
			fcn_00469c40(*(int*) ((char*) obj_tbl + owner * 0x2f4 + 0x10), *(int*) ((char*) gbase + 8) + off, owner);
			gbase = (int*) g_77255c; obj_tbl = (int*) g_1015ea0; rec1 = p[1];
			fcn_00469c40(*(int*) ((char*) obj_tbl + rec1 * 0x2f4 + 0x10), *(int*) ((char*) gbase + 8) + off + 0x30, rec1);
			off += 0x4c;
		}
		p = (int*) ((char*) p + 0x1c);
		count--;
	}
	return 0;
}
