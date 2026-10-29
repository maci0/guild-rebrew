#include <string.h>

#pragma intrinsic(memset)

/* SIZE 0x54 */
typedef struct {
	char pad0[0xc];
	int f0c;
	int armor[2];
	int weapon[6];
	int f30;
	int f34;
	int f38;
	int f3c;
	int f40;
	int f44;
	int f48;
	int f4c;
	int f50;
} Out50c1b0;

extern char* lpGebaeudePROT;
extern unsigned char g_773d75;
extern double g_6640e8;

float __cdecl fcn_0050b8d0(unsigned char* p, int k, int a, int b);
void* __cdecl fcn_004ec7d0(unsigned char* e);
int __cdecl fcn_004ee160(char* e);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0050b810(int, unsigned char b);

/* ADDRESS: GOLDTL 0x0050c1b0 */
int __cdecl fcn_0050c1b0(unsigned char* e, int id, char* out)
{
	unsigned char* row;
	int slot;
	int t;
	char* p;
	int var;
	int total;
	int found;
	int i;
	int v;

	memset(out, 0, 0x54);
	row = (unsigned char*) lpGebaeudePROT + (unsigned int) *e * 0x24d;
	total = 0;
	var = 0;
	if (id != *(unsigned short*) (e + 0x27)) {
		goto tail;
	}
	slot = 0x7f4ca0 + id * 0x21c;
	if (*row == 0x1e) {
		if (fcn_004ec7d0(e) != 0) {
			v = fcn_004ee160((char*) e);
			*(int*) (out + 0x18) = v;
			total = v;
		}
		goto finalize;
	}
	for (t = 0x7f4ca0; t < 0x85a0a0; t += 0x21c) {
		if (*(int*) (t + 0x16c) != (int) e) {
			continue;
		}
		found = 0;
		for (i = 0; i < 6; i++) {
			if (row[i + 0x223] != 0 && row[i + 0x223] == *(unsigned char*) (t + 0x164) &&
			    *(unsigned char*) (t + 2) != 0x14) {
				v = (int) (fcn_0050b8d0((unsigned char*) slot, *e, i, -1) *
					   ((double) *(int*) (e + 0x3d) * g_6640e8));
				*(int*) (out + 0x18 + i * 4) += v;
				total += v;
				found = 1;
			}
		}
		for (i = 0; i < 2; i++) {
			if (row[i + 0x22f] != 0 && row[i + 0x22f] == *(unsigned char*) (t + 0x165) &&
			    *(unsigned char*) (t + 2) != 0x14) {
				v = (int) (fcn_0050b8d0((unsigned char*) slot, *e, -1, i) *
					   ((double) *(int*) (e + 0x3d) * g_6640e8));
				*(int*) (out + 0x10 + i * 4) += v;
				total += v;
				found = 1;
			}
		}
		if (found == 0 && *(unsigned char*) (t + 2) != 0x14) {
			v = (int) (fcn_0050b8d0((unsigned char*) slot, *e, -1, 0) *
				   ((double) *(int*) (e + 0x3d) * g_6640e8));
			*(int*) (out + 0x10) += v;
			total += v;
		}
	}
finalize:
	*(int*) (out + 0xc) = total;
	*(int*) (out + 0x48) = *(int*) (e + 0x4d);
	if (*row == 5) {
		*(int*) (out + 0x28) = *(int*) (e + 0x55);
		var = *(int*) (e + 0x55);
	}
	if (*row == 7) {
		p = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0xe8);
		if (p != 0) {
			v = fcn_0050b810(*(int*) (p + 0x14), g_773d75);
			*(int*) (out + 0x30) += v;
			var += v;
		}
		p = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0xf0);
		if (p != 0) {
			v = fcn_0050b810(*(int*) (p + 0x14), g_773d75);
			*(int*) (out + 0x3c) += v;
			var += v;
		}
		*(int*) (out + 0x34) += *(int*) (e + 0x65);
		*(int*) (out + 0x38) += *(int*) (e + 0x69);
		var += *(int*) (out + 0x34) + *(int*) (out + 0x38);
	} else if (*row == 0x16) {
		v = *(int*) (e + 0x6d);
		*(int*) (out + 0x4c) = v;
		var += v;
	}
tail:
	*(int*) (out + 0x40) = total;
	*(int*) (out + 0x44) = var;
	*(int*) (out + 0x50) = var - total;
	if (total == 0 && var == 0) {
		return 0;
	}
	return 1;
}
