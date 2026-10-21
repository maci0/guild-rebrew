#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string.h>

#include "client_method_registry.h"
#pragma function(memcpy)

typedef struct VFS_DIR VFS_DIR;

/* Native method record: type, 0x20-byte name, three callback pointers and
   three 4-entry effect blocks; stride 0x94. */
typedef struct AM_EFFECTS {
	AM_EFFECT e[4];
} AM_EFFECTS;

typedef struct AM_METHOD_DATA {
	unsigned char type;
	char name[0x20];
	void* score;
	void* start;
	void* run;
	AM_EFFECTS effects;
	AM_EFFECTS saved;
	AM_EFFECTS other;
	int flags;
} AM_METHOD_DATA;

extern VFS_DIR* g_6b7fdc;
extern char g_1008420[];
extern AM_METHOD_DATA g_1008540[];
extern char* g_77481c;
extern int g_7e1f80;

void* __cdecl fcn_0042ff50(const char* name, const char* mode, VFS_DIR* root);
unsigned int __cdecl vfs_fwrite(void* data, int size, int count, char* f);
unsigned int __cdecl vfs_ReadData(char* buf, int size, int count, char* f);
void __cdecl CloseVfsStream(char* f);
int __cdecl fcn_004a1130(char* ini);
int __cdecl fcn_004901d0(char* ini);
int __cdecl fcn_0048f110(char* ini);
int __cdecl fcn_004abff0(char* ini);

/* ADDRESS: GOLDTL 0x00494820 */
int __cdecl fcn_00494820(void)
{
	AM_METHOD_DATA tmp;
	unsigned int nmeth;
	int sig;
	unsigned int count;
	char* f;
	unsigned int i;
	unsigned int n;

	count = 0x49;
	memset(g_1008540, 0, sizeof(AM_METHOD_DATA) * 0x49);
	sig = 0x6144466e;
	if (g_77481c != 0) {
		GetModuleFileNameA((HMODULE) *(int*) 0x7e1f80, g_1008420, 0x104);
		nmeth = 0x49;
		strrchr(g_1008420, '\\')[1] = 0;
		strcat(g_1008420, "ai_method_addon.ini");
		if (fcn_004a1130(g_77481c) == 0) {
			goto bad;
		}
		if (fcn_004901d0(g_77481c) == 0) {
			goto bad;
		}
		if (fcn_0048f110(g_77481c) == 0) {
			goto bad;
		}
		if (fcn_004abff0(g_77481c) == 0) {
			goto bad;
		}
		f = fcn_0042ff50("/gamedata/ai/ai_data_2.dfn", "wb", g_6b7fdc);
		if (f == 0) {
			goto bad;
		}
		if (vfs_fwrite(&sig, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_fwrite(&nmeth, 4, 1, f) <= 0) {
			goto fail;
		}
		for (i = 0; i < 0x49; i++) {
			if (vfs_fwrite(&g_1008540[i].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(g_1008540[i].name, 0x20, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects.e[0].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects.e[0].value, 4, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects.e[1].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects.e[1].value, 4, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects.e[2].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects.e[2].value, 4, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects.e[3].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].effects.e[3].value, 4, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other.e[0].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other.e[0].value, 4, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other.e[1].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other.e[1].value, 4, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other.e[2].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other.e[2].value, 4, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other.e[3].type, 1, 1, f) <= 0) {
				goto fail;
			}
			if (vfs_fwrite(&g_1008540[i].other.e[3].value, 4, 1, f) <= 0) {
				goto fail;
			}
		}
		CloseVfsStream(f);
		return 1;
	}
	f = fcn_0042ff50("/gamedata/ai/ai_data_2.dfn", "rb", g_6b7fdc);
	if (f == 0) {
		goto bad;
	}
	if (fcn_004a1130(g_77481c) == 0) {
		goto fail;
	}
	if (fcn_004901d0(g_77481c) == 0) {
		goto fail;
	}
	if (fcn_0048f110(g_77481c) == 0) {
		goto fail;
	}
	if (fcn_004abff0(g_77481c) == 0) {
		goto fail;
	}
	if (vfs_ReadData((char*) &sig, 4, 1, f) <= 0) {
		goto fail;
	}
	if (sig != 0x6144466e) {
		goto bad;
	}
	if (vfs_ReadData((char*) &count, 4, 1, f) <= 0) {
		goto fail;
	}
	for (n = 0; n < count; n++) {
		if (vfs_ReadData((char*) &tmp.type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData(tmp.name, 0x20, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.effects.e[0].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.effects.e[0].value, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.effects.e[1].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.effects.e[1].value, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.effects.e[2].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.effects.e[2].value, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.effects.e[3].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.effects.e[3].value, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.other.e[0].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.other.e[0].value, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.other.e[1].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.other.e[1].value, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.other.e[2].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.other.e[2].value, 4, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.other.e[3].type, 1, 1, f) <= 0) {
			goto fail;
		}
		if (vfs_ReadData((char*) &tmp.other.e[3].value, 4, 1, f) <= 0) {
			goto fail;
		}
		memcpy(&tmp.saved, &tmp.effects, 0x20);
		if (tmp.type < 0x49) {
			g_1008540[tmp.type].type = tmp.type;
			strcpy(g_1008540[tmp.type].name, tmp.name);
			g_1008540[tmp.type].effects = tmp.effects;
			g_1008540[tmp.type].other = tmp.other;
			g_1008540[tmp.type].saved = tmp.saved;
		}
	}
	CloseVfsStream(f);
	return 1;
fail:
	CloseVfsStream(f);
bad:
	return 0;
}
