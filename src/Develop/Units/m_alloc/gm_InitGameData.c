#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"

#include <stdio.h>
#include <string.h>

extern unsigned int g_868118;
extern unsigned int g_85ab84;
extern unsigned int g_6965d8[0xaa0];
extern unsigned char* lpGebaeudePROT;
extern unsigned char* lpGebaeudeINST;
extern char* lpObjektePROT;
extern unsigned short* lpObjekteINST;

void* __cdecl m_alloc(int, char*);
void __cdecl init_BuildObjectProducerTables(void);
void __cdecl gm_KillAllSpieler(void);
void __cdecl srv_SeedRandomWithTime(void);

int __cdecl gm_InitGameData(char* dir)
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
	(*(char**)&lpGebaeudePROT) = m_alloc(0xca78, "f3_gm:lpGebaeudePROT");
	if ((*(char**)&lpGebaeudePROT) == 0) {
		return -1;
	}
	lpGebaeudeINST = m_alloc(0xa900, "f3_gm:lpGebaeudeINST");
	memset(lpGebaeudeINST, 0, 0xa900);
	if (lpGebaeudeINST == 0) {
		return -2;
	}
	sprintf(path, "%s%s", dir, "A_Geb.dat");
	f = fopen(path, "rb");
	if (f == 0) {
		return -3;
	}
	fread((*(char**)&lpGebaeudePROT), 0x24d, 0x58, f);
	fclose(f);
	lpObjektePROT = m_alloc(0xb9dc, "f3_gm:lpObjektePROT");
	if (lpObjektePROT == 0) {
		return -4;
	}
	lpObjekteINST = m_alloc(0x14f218, "f3_gm:lpObjekteINST");
	if (lpObjekteINST == 0) {
		return -5;
	}
	memset(lpObjekteINST, 0, 0x14f218);
	sprintf(path, "%s%s", dir, "A_Obj.dat");
	f = fopen(path, "rb");
	if (f == 0) {
		return -6;
	}
	fread(lpObjektePROT, 0x41, 0x2dc, f);
	fclose(f);
	init_BuildObjectProducerTables();
	gm_KillAllSpieler();
	row = 0;
	do {
		count = 0;
		left = 0x40;
		slot = ((BUILDING_PROTOTYPE*)(*(char**)&lpGebaeudePROT))[row].components;
		do {
			entry = *slot;
			if (entry != 0xffff) {
				idx = entry & 0x7fff;
				category = ((OBJECT_PROTOTYPE*)lpObjektePROT)[idx].kind;
				if ((category == 2 || category == 6) && idx != 0xfd && (entry & 0x8000) != 0) {
					count++;
				}
			}
			slot++;
			left--;
		} while (left != 0);
		((BUILDING_PROTOTYPE*)(*(char**)&lpGebaeudePROT))[row].count_021 += (char) count;
		row++;
	} while (row < 0x58);
	srv_SeedRandomWithTime();
	return 0;
}
