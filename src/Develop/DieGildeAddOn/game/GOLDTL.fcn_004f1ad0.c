#include <string.h>

extern char* lpGebaeudePROT;
extern int gm_NextEntityId;
extern int gm_GameTime;
extern char* g_14a62d8[];
extern char* g_14a5dbc[];
extern char* gm_FemaleNames[];

int __cdecl gm_RandomMod(int n);
char* __cdecl FindSlotEntryFiltered(int a0, void* a1, int a2, void* filter, int a4);
char* __cdecl fcn_004fd9d0(int a0, int a1);

/* ADDRESS: GOLDTL 0x004f1ad0 */
int __cdecl fcn_004f1ad0(void* building, int count)
{
	char* hit;
	char* tbl;
	int i;
	int j;
	int idx;

	idx = (unsigned char) *(char*) building;
	tbl = lpGebaeudePROT + idx * 589;
	if (*tbl != 0x1d) {
		return 0;
	}
	if ((unsigned char) tbl[0x247] < 1 || (unsigned char) tbl[0x247] > 3) {
		return 0;
	}
	i = 0;



	for (; i < count; i++) {
		hit = FindSlotEntryFiltered(0, building, 0, (void*) 0x4f1840, 0);
		if (hit == 0) {
			return i;
		}
		*(int*) *(char**) (hit + 0x10) = gm_NextEntityId;
		gm_NextEntityId = gm_NextEntityId + 1;
		*(int*) (hit + 4) = *(int*) *(char**) (hit + 0x10);
		*(unsigned short*) (hit + 8) = 0x7fff;
		*(unsigned short*) (hit + 0xa) = (unsigned short) (gm_GameTime + 5);
		*(unsigned char*) (hit + 0xc) = 0xff;
		for (j = 0; j < 5; j++) {
			*((char*) *(char**) (hit + 0x10) + j + 0x24) =
			    (char) ((float) (gm_RandomMod(8) & 0xffff) * 21.0f
				+ 42.0f);
		}
		*(int*) (*(char**) (hit + 0x10) + 0x2c) = (gm_RandomMod(9) & 0xffff) + 1;
		*(int*) (*(char**) (hit + 0x10) + 0x30) = (gm_RandomMod(2) & 0xffff) + 1;
		*(int*) (*(char**) (hit + 0x10) + 0x34) = (gm_RandomMod(0x5e) & 0xffff) + 1;
		*(int*) (*(char**) (hit + 0x10) + 0x40) =
		    gm_GameTime - (gm_RandomMod(4) & 0xffff) - 1;
		*(int*) (*(char**) (hit + 0x10) + 0x38) = gm_RandomMod(2) & 0xffff;
		strncpy(*(char**) (hit + 0x10) + 0x14,
		    g_14a62d8[gm_RandomMod(0x95) & 0xffff], 0xf);
		tbl = fcn_004fd9d0(*(int*) (*(char**) (hit + 0x10) + 0x38),
		    *(int*) (*(char**) (hit + 0x10) + 0x34));
		*(int*) (*(char**) (hit + 0x10) + 0x3c) = 0xff;
		idx = gm_RandomMod(4) & 0xffff;
		j = 4;
		while (j != 0) {
			if (*(int*) (tbl + idx * 4 + 0x34) != 0xff) {
				*(int*) (*(char**) (hit + 0x10) + 0x3c) =
				    *(int*) (tbl + idx * 4 + 0x34) + 0x639;
				break;
			}
			j--;
			idx = (idx + 1) % 4;
		}
		if (*(int*) (*(char**) (hit + 0x10) + 0x38) == 0) {
			strncpy(*(char**) (hit + 0x10) + 4,
			    g_14a5dbc[gm_RandomMod(0xbf) & 0xffff], 0xf);
		} else {
			strncpy(*(char**) (hit + 0x10) + 4,
			    gm_FemaleNames[gm_RandomMod(0x70) & 0xffff], 0xf);
		}
	}
	return i;
}
