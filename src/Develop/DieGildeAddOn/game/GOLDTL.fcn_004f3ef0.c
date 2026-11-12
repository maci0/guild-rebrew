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

extern unsigned short __cdecl gm_RandomMod(int a);
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
extern int __cdecl fcn_004c54c0(unsigned int a, unsigned int b, int value, int d);
extern void __cdecl fcn_005b2d50(int slot, int record, int count, int total);
extern void __cdecl fcn_005b2c60(int slot, int record);

extern char g_7f4ca0[];
extern int __cdecl fcn_004f1850();
extern int __cdecl fcn_004c5530(void* msg);

/* ADDRESS: GOLDTL 0x004f3ef0 */
void __cdecl fcn_004f3ef0(char* a0)
{
	int n;
	int result;
	char* home;
	int value;
	int hits;
	int count;
	int total;
	int out;
	char* list;
	unsigned int block[0x3e];
	char* slot;
	int* entry;
	int handle;
	int k;
	int i;
	float a;

	handle = -1;
	home = 0;
	n = 0;
	hits = 0;
	count = 0;
	total = 0;
	if (*(unsigned short*) (a0 + 0x27) != 0xffff
	    && *(unsigned short*) (a0 + 0x27) != *(unsigned short*) g_773da8) {
		home = g_7f4ca0 + *(unsigned short*) (a0 + 0x27) * 0x21c;
	}
	entry = (int*) FindSlotEntryFiltered(0, a0, 0, (void*) fcn_004f1850, 0xff);
	if (entry != 0) {
		do {
			if (n >= 0x40 && handle != -1) {
				for (;;) {
					if (fcn_004c4450(handle) != 0)
						break;
					fcn_004c3ff0();
					fcn_004c4940();
					cm_ExecCommand();
				}
				n = 0;
				handle = -1;
			}
			slot = (char*) gm_LookupEntityRecordById(entry[1]);
			if (slot == 0) {
				result = entry[0];
				k = g_6652f8[result];

				for (i = 0; i < k; i++) {
					if (((int*) entry[4])[i * 0x11] != -1)
						break;
				}
				if (i >= k) {
					handle = fcn_004f2a10(0, (int) a0, result,
						fcn_004f1790((char*) *(int*) (a0 + 0x65), entry));
				} else {
					a = (gm_RandomFloat01() + g_6628a0) * g_6628cc;
					value = (int) (*(unsigned char*) ((char*) entry + 0xc) * g_662c30
						* g_6652e8[entry[0]] * a);
					if (value <= 0)
						continue;
					if (((fcn_004f1790((char*) *(int*) (a0 + 0x65), entry) ^ g_7f4c00) & 1) != 0)
						continue;
					handle = fcn_004f2d30((int) a0, entry[0],
						fcn_004f1790((char*) *(int*) (a0 + 0x65), entry), -value);
				}
				n++;
				continue;
			}
			result = entry[0];
			a = (gm_RandomFloat01() + g_6628a0) * g_6628cc;
			value = (int) (*(unsigned char*) ((char*) entry + 0xc) * g_662c30
				* g_6652e8[entry[0]] * a);
			if (value > 0) {
				list = (char*) *(int*) (a0 + 0x65);
				if (((fcn_004f1790(list, entry) ^ g_7f4c00) & 1) == 0) {
					handle = fcn_004f2d30((int) a0, result, fcn_004f1790(list, entry), -value);
					n++;
				}
			}
			if (home == 0)
				continue;
			if (slot != home && g_7f4c00 % 4 == (*(int*) (slot + 4) & 3)
			    && *(unsigned char*) ((char*) entry + 0xc) * g_662c30 < g_664178) {
				handle = fcn_004c54c0(*(unsigned int*) (home + 4), *(unsigned int*) (slot + 4),
					-5 - gm_RandomMod(0x10), 1);
				n++;
				hits++;
			}
			if (*(unsigned short*) ((char*) entry + 0xa) != g_7f4c00)
				continue;
			result = fcn_004f4440((int) slot, *(unsigned char*) ((char*) entry + 0xc), entry[0], 0, &out);
			if (slot == home) {
				handle = fcn_004f2810((int) slot, (int) a0, entry[0],
					fcn_004f1790((char*) *(int*) (a0 + 0x65), entry), 10, 0);
			} else if (*(char*) (slot + 2) != 6 && *(char*) (slot + 2) != 7) {
				value = fcn_0050d320(slot, (char) g_773d75);
				if ((int) (value * g_66417c) > result) {
					handle = fcn_004f2810((int) slot, (int) a0, entry[0],
						fcn_004f1790((char*) *(int*) (a0 + 0x65), entry), 10, result);
					n++;
					count++;
					total += out;
					continue;
				}
				handle = fcn_004f2a10(0, (int) a0, entry[0],
					fcn_004f1790((char*) *(int*) (a0 + 0x65), entry));
			} else {
				memset(block, 0, sizeof(block));
				*(int*) ((char*) block + 8) = *(int*) (slot + 4);
				*(int*) ((char*) block + 0x28) = g_7f4c00;
				*(int*) ((char*) block + 0x30) = g_7f4c08;
				*(int*) ((char*) block + 0xc) = *(int*) (a0 + 1);
				*(int*) ((char*) block + 0x2c) = g_7f4c04;
				*(int*) ((char*) block + 0x58) = *(int*) (a0 + 1);
				*(unsigned char*) ((char*) block + 4) = 0x92;
				*(unsigned short*) ((char*) block + 0x34) = (unsigned short) g_7f4c0c;
				*(unsigned char*) ((char*) block + 0x36) = 9;
				*(int*) ((char*) block + 0x5c) = entry[0];
				*(char*) ((char*) block + 0x60) = (char) fcn_004f1790((char*) *(int*) (a0 + 0x65), entry);
				*(int*) ((char*) block + 0x64) = result;
				*(int*) ((char*) block + 0x68) = 10;
				handle = fcn_004c5530(block);
			}
			n++;
		} while ((entry = (int*) FindSlotEntryFiltered(0, a0, entry, (void*) fcn_004f1850, 0xff)) != 0);
	}
	if (fcn_004f13a0(a0) < 4)
		fcn_004f2e80(a0, gm_RandomMod(2) + 1);
	if (home != 0 && (*(char*) (home + 2) == 6 || *(char*) (home + 2) == 7)) {
		if (count > 0)
			fcn_005b2d50((int) home, (int) a0, count, total);
		if (hits != 0)
			fcn_005b2c60((int) home, (int) a0);
	}
}
