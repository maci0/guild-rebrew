#include <string.h>

extern char* g_773da8;
extern unsigned char g_773d75;
extern int g_7f4c00;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern float g_6628a0;
extern float g_6628cc;
extern float g_662c30;
extern float g_664178;
extern float g_66417c;
extern float g_6652e8[];
extern int g_6652f8[];

extern int __cdecl gm_RandomMod(int a, ...);
extern float __cdecl gm_RandomFloat01(void);
extern void* __cdecl FindSlotEntryFiltered(void* a, void* b, int c, void* d, int e);
extern int __cdecl fcn_004f1790(char* a, void* e);
extern int __cdecl fcn_004f2810(int slot, int record, int item, int value, int a, int b);
extern int __cdecl fcn_004f2a10(int a, int record, int item, int value);
extern int __cdecl fcn_004f2d30(int record, int item, int value, int delta);
extern int __cdecl fcn_004f4440(int slot, int byte, int item, int zero, int* out);
extern int __cdecl fcn_004f13a0(char* record);
extern void __cdecl fcn_004f2e80(char* record, int value);
extern void* __cdecl gm_LookupEntityRecordById(int id);
extern int __cdecl fcn_0050d320(char* slot, char mode);
extern int __cdecl fcn_004c4450(int handle);
extern void __cdecl fcn_004c3ff0(void);
extern void __cdecl fcn_004c4940(void);
extern void __cdecl cm_ExecCommand(void);
extern int __cdecl fcn_004c54c0(unsigned int a, unsigned int b, int value);
extern void __cdecl fcn_005b2d50(int slot, int record, int count, int total);
extern void __cdecl fcn_005b2c60(int slot, int record);

/* ADDRESS: GOLDTL 0x004f3ef0 */
void __cdecl fcn_004f3ef0(char* a0)
{
	char* home;
	char* slot;
	int* entry;
	int idx;
	int handle;
	int n;
	int rc;
	int value;
	int extra;
	int total;
	int count;
	int hits;
	int kind;
	int i;
	int out;
	int result;

	home = 0;
	slot = 0;
	handle = -1;
	n = 0;
	hits = 0;
	count = 0;
	total = 0;
	out = 0;
	idx = *(unsigned short*) (a0 + 0x27);
	if (idx != 0xffff && idx != *(unsigned short*) g_773da8) {
		slot = (char*) (idx * 0x21c + 0x7f4ca0);
		home = slot;
	}
	entry = (int*) FindSlotEntryFiltered(0, a0, 0, (void*) 0x4f1850, 0xff);
	if (entry != 0) {
		do {
			if (n >= 0x40 && handle != -1) {
				while (fcn_004c4450(handle) == 0) {
					fcn_004c3ff0();
					fcn_004c4940();
					cm_ExecCommand();
				}
				n = 0;
				handle = -1;
			}
			slot = (char*) gm_LookupEntityRecordById(entry[1]);
			if (slot != 0) {
				value = (int) ((gm_RandomFloat01() + g_6628a0) * g_6628cc
					* (float) *(unsigned char*) ((char*) entry + 0xc) * g_662c30
					* g_6652e8[entry[0]]);
				if (value >= 1) {
					extra = fcn_004f1790((char*) *(int*) (a0 + 0x65), entry);
					if (((extra ^ g_7f4c00) & 1) == 0) {
						rc = fcn_004f1790((char*) *(int*) (a0 + 0x65), entry);
						handle = fcn_004f2d30((int) a0, entry[0], rc, -value);
						n++;
					}
				}
				if (home != 0) {
					if (slot != home) {
						if ((g_7f4c00 & 3) == (*(unsigned int*) (slot + 4) & 3)
							&& (float) *(unsigned char*) ((char*) entry + 0xc) * g_662c30 < g_664178) {
							extra = gm_RandomMod(0x10, 1);
							handle = fcn_004c54c0(*(unsigned int*) (home + 4),
								*(unsigned int*) (slot + 4),
								0xfffffffb - (extra & 0xffff));
							n++;
							hits++;
						}
					}
					if (*(unsigned short*) ((char*) entry + 0xa) == (unsigned short) g_7f4c00) {
						result = fcn_004f4440((int) slot,
							*(unsigned char*) ((char*) entry + 0xc), entry[0], 0, &out);
						if (slot == home) {
							rc = fcn_004f1790((char*) *(int*) (a0 + 0x65), entry);
							rc = fcn_004f2810((int) slot, (int) a0, entry[0], rc, 0x0a, 0);
						} else if (*(char*) (slot + 2) != 6 && *(char*) (slot + 2) != 7) {
							idx = fcn_0050d320(slot, (char) g_773d75);
							if (out < (int) ((float) out * g_66417c)) {
								rc = fcn_004f1790((char*) *(int*) (a0 + 0x65), entry);
								rc = fcn_004f2810((int) slot, (int) a0, entry[0], rc, 0x0a, 0);
								n++;
								count++;
								total += out;
							} else {
								rc = fcn_004f1790((char*) *(int*) (a0 + 0x65), entry);
								rc = fcn_004f2a10(0, (int) a0, entry[0], rc);
							}
						} else {
							unsigned int block[0x3e];
							memset(block, 0, sizeof(block));
							*(unsigned char*) ((char*) block + 4) = 0x92;
							*(int*) ((char*) block + 8) = *(int*) (slot + 4);
							*(int*) ((char*) block + 0xc) = *(int*) (a0 + 1);
							*(int*) ((char*) block + 0x28) = g_7f4c00;
							*(int*) ((char*) block + 0x2c) = g_7f4c04;
							*(int*) ((char*) block + 0x30) = g_7f4c08;
							*(unsigned short*) ((char*) block + 0x34) = (unsigned short) g_7f4c0c;
							*(unsigned char*) ((char*) block + 0x36) = 9;
							*(int*) ((char*) block + 0x5c) = entry[0];
							*(char*) ((char*) block + 0x60) = (char) fcn_004f1790((char*) *(int*) (a0 + 0x65), entry);
							*(int*) ((char*) block + 0x64) = idx;
							*(int*) ((char*) block + 0x68) = 10;
							fcn_004c5530((int) block);
						}
						n++;
					}
				}
			} else {
				idx = entry[0];
				kind = g_6652f8[idx];
				if (kind >= 1) {
					int* item;
					item = (int*) entry[4];
					i = 0;
					do {
						if (*item != -1) {
							value = (int) gm_RandomFloat01();
							if (value > 0) {
								rc = fcn_004f1790((char*) *(int*) (a0 + 0x65), entry);
								if (((rc ^ g_7f4c00) & 1) == 0) {
									rc = fcn_004f1790((char*) *(int*) (a0 + 0x65), entry);
									handle = fcn_004f2d30((int) a0, idx, rc, -value);
								}
							}
							break;
						}
						i++;
						item += 0x11;
					} while (i < kind);
				}
				rc = fcn_004f1790((char*) *(int*) (a0 + 0x65), entry);
				rc = fcn_004f2a10(0, (int) a0, idx, rc);
				n++;
			}
			entry = (int*) FindSlotEntryFiltered(0, a0, entry, (void*) 0x4f1850, 0xff);
		} while (entry != 0);
		slot = home;
	}
	if (fcn_004f13a0(a0) <= 3)
		fcn_004f2e80(a0, (gm_RandomMod(2) & 0xffff) + 1);
	if (slot != 0 && (*(char*) (slot + 2) == 6 || *(char*) (slot + 2) == 7)) {
		if (count >= 1)
			fcn_005b2d50((int) slot, (int) a0, count, total);
		if (hits != 0)
			fcn_005b2c60((int) slot, (int) a0);
	}
}
