#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string.h>

#include "client_method_registry.h"
#pragma function(memcpy)

typedef struct VFS_DIR VFS_DIR;
typedef struct AM_EFFECTS AM_EFFECTS;

struct AM_EFFECTS {
	AM_EFFECT e[4];
};

extern VFS_DIR* g_6b7fdc;
extern char g_1008420[];
extern AM_METHOD g_1008540[];

void* __cdecl fcn_0042ff50(const char* name, const char* mode, VFS_DIR* root);
unsigned int __cdecl vfs_fwrite(void* data, int size, int count, char* f);
unsigned int __cdecl vfs_ReadData(char* buf, int size, int count, char* f);
void __cdecl CloseVfsStream(char* f);
int __cdecl fcn_004a1130(char* ini);
int __cdecl fcn_004901d0(char* ini);
int __cdecl fcn_0048f110(char* ini);
int __cdecl fcn_004abff0(char* ini);
void* __cdecl fcn_0064d740(void* dst, const void* src, unsigned int n);

/* ADDRESS: GOLDTL 0x00494820 */
int __cdecl fcn_00494820(void)
{
	char* f;
	char* p;
	char* ini;
	int max;
	int i;
	unsigned int sig;
	unsigned char idx;
	char name[0x20];
	AM_EFFECTS eff;
	AM_EFFECTS sav;
	AM_EFFECTS oef;

	memset(g_1008540, 0, sizeof(AM_METHOD) * 0x49);
	sig = 0x6144466e;
	max = 0x49;
	ini = *(char**) 0x77481c;
	if (ini != 0) {
		int cnt;

		cnt = 0x49;
		GetModuleFileNameA(*(HMODULE*) 0x7e1f80, g_1008420, 0x104);
		p = strrchr(g_1008420, '\\');
		p[1] = 0;
		strcat(g_1008420, "ai_method_addon.ini");
		if (!fcn_004a1130(ini)) {
			return 0;
		}
		if (!fcn_004901d0(ini)) {
			return 0;
		}
		if (!fcn_0048f110(ini)) {
			return 0;
		}
		if (!fcn_004abff0(ini)) {
			return 0;
		}
		f = fcn_0042ff50("/gamedata/ai/ai_data_2.dfn", "wb", g_6b7fdc);
		if (f == 0) {
			return 0;
		}
		if (vfs_fwrite(&sig, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&cnt, 4, 1, f) <= 0) {
			goto fail;
		}
		for (i = 0; i < 0x49; i++) {
			if (vfs_fwrite(&g_1008540[i].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(g_1008540[i].name, 0x20, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects[0].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects[0].value, 4, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects[1].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects[1].value, 4, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects[2].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects[2].value, 4, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects[3].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects[3].value, 4, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other_effects[0].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other_effects[0].value, 4, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other_effects[1].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other_effects[1].value, 4, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other_effects[2].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other_effects[2].value, 4, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other_effects[3].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other_effects[3].value, 4, 1, f) <= 0) {
				goto fail;
			}
		}
		CloseVfsStream(f);
		return 1;
	}
	f = fcn_0042ff50("/gamedata/ai/ai_data_2.dfn", "rb", g_6b7fdc);
	if (f == 0) {
		return 0;
	}
	if (!fcn_004a1130(ini)) {
		goto fail;
	}
	if (!fcn_004901d0(ini)) {
		goto fail;
	}
	if (!fcn_0048f110(ini)) {
		goto fail;
	}
	if (!fcn_004abff0(ini)) {
		goto fail;
	}
	if (vfs_ReadData((char*) &sig, 4, 1, f) <= 0) {
		goto fail;
	}
	if (sig != 0x6144466e) {
		return 0;
	}
	if (vfs_ReadData((char*) &max, 4, 1, f) <= 0) {
		goto fail;
	}
	for (i = 0; i < max; i++) {
		if (vfs_ReadData((char*) &idx, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData(name, 0x20, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &eff.e[0].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &eff.e[0].value, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &eff.e[1].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &eff.e[1].value, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &eff.e[2].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &eff.e[2].value, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &eff.e[3].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &eff.e[3].value, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &oef.e[0].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &oef.e[0].value, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &oef.e[1].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &oef.e[1].value, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &oef.e[2].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &oef.e[2].value, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &oef.e[3].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &oef.e[3].value, 4, 1, f) <= 0) {
			goto fail;
		}
		memcpy(&sav, &eff, 0x20);
		if (idx < 0x49) {
			g_1008540[idx].type = idx;
			strcpy(g_1008540[idx].name, name);
			*(AM_EFFECTS*) g_1008540[idx].effects = eff;
			*(AM_EFFECTS*) g_1008540[idx].other_effects = oef;
			*(AM_EFFECTS*) g_1008540[idx].saved_effects = sav;
		}
	}
	CloseVfsStream(f);
	return 1;
fail:
	CloseVfsStream(f);
	return 0;
}
