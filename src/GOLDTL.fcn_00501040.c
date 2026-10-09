// FUNCTION: GOLDTL 0x00501040

#include <stdio.h>
#include <string.h>

extern unsigned int g_868118;
extern unsigned int g_85ab84;
extern unsigned int g_6965d8[0xaa0];
extern unsigned char* g_868050;
extern unsigned char* g_90e094;
extern char* g_99ec10;
extern unsigned short* g_868054;

void* __cdecl fcn_0041db70(int, char*);
void __cdecl fcn_00500e40(void);
void __cdecl gm_KillAllSpieler(void);
void __cdecl srv_SeedRandomWithTime(void);

int __cdecl fcn_00501040(char* dir)
{
	unsigned int* src;
	unsigned int* dst;
	FILE* f;
	unsigned short entry;
	char category;
	int count;
	unsigned short* slot;
	int left;
	int idx;
	char path[0x200];
	int row;
	char* def_row;
	char* cat_p;
	char* total;

	src = &g_868118;
	dst = &g_85ab84;
	do {
		unsigned int* copy_dst;
		unsigned int* base;

		base = dst + 2;
		copy_dst = dst + 3;
		base[-3] = src[-0x14];
		base[-2] = 1000;
		base[-1] = *src;
		base[0] = 1000;
		memcpy(copy_dst, g_6965d8, sizeof(g_6965d8));
		src += 0xbd;
		dst += 0xaa4;
	} while ((int) src < (int) &g_868118 + 0xbd * 4 * 5);
	(*(char**)&g_868050) = fcn_0041db70(0xca78, "f3_gm:lpGebaeudePROT");
	if ((*(char**)&g_868050) == 0) {
		return -1;
	}
	g_90e094 = fcn_0041db70(0xa900, "f3_gm:lpGebaeudeINST");
	memset(g_90e094, 0, 0xa900);
	if (g_90e094 == 0) {
		return -2;
	}
	sprintf(path, "%s%s", dir, "A_Geb.dat");
	f = fopen(path, "rb");
	if (f == 0) {
		return -3;
	}
	fread((*(char**)&g_868050), 0x24d, 0x58, f);
	fclose(f);
	g_99ec10 = fcn_0041db70(0xb9dc, "f3_gm:lpObjektePROT");
	if (g_99ec10 == 0) {
		return -4;
	}
	g_868054 = fcn_0041db70(0x14f218, "f3_gm:lpObjekteINST");
	if (g_868054 == 0) {
		return -5;
	}
	memset(g_868054, 0, 0x14f218);
	sprintf(path, "%s%s", dir, "A_Obj.dat");
	f = fopen(path, "rb");
	if (f == 0) {
		return -6;
	}
	fread(g_99ec10, 0x41, 0x2dc, f);
	fclose(f);
	fcn_00500e40();
	gm_KillAllSpieler();
	row = 0;
	do {
		count = 0;
		left = 0x40;
		slot = (unsigned short*) ((*(char**)&g_868050) + row * 0x24d + 0x23);
		do {
			entry = *slot;
			if (entry != 0xffff) {
				idx = entry & 0x7fff;
				def_row = g_99ec10 + idx * 0x40;
				cat_p = (char*) idx;
				cat_p += (int) def_row;
				category = *(volatile char*) cat_p;
				if ((category == 2 || category == 6) && idx != 0xfd && (entry & 0x8000) != 0) {
					count++;
				}
			}
			slot++;
			left--;
		} while (left != 0);
		total = (*(char**)&g_868050) + row * 0x24d + 0x21;
		row++;
		*total += (char) count;
	} while (row < 0x58);
	srv_SeedRandomWithTime();
	return 0;
}
