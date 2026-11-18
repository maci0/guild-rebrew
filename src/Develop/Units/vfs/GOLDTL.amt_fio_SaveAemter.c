


#include <stdio.h>

// SIZE 0x18
typedef struct {
	char a;
	int b;
	char c;
	int d;
	char e;
	int f;
} Rec;

#include "client_types.h"
extern Rec18_68da68 amt_OfficeSlots[42];
extern char g_68de60[];

int __cdecl vfs_fwrite(void* p, int size, int n, void* file);

int __cdecl amt_fio_SaveAemter(void* file)
{
	int ver;
	char buf[256];
	int i;

	ver = 0x2a;
	if (file == 0) {
		return 0;
	}
	if (!vfs_fwrite(&ver, 4, 1, file)) {
		return 0;
	}
	sprintf(buf, g_68de60, ver);
	for (i = 0; i < 42; i++) {
		if (!vfs_fwrite(&((Rec*)amt_OfficeSlots)[i].a, 1, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((Rec*)amt_OfficeSlots)[i].b, 4, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((Rec*)amt_OfficeSlots)[i].c, 1, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((Rec*)amt_OfficeSlots)[i].d, 4, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((Rec*)amt_OfficeSlots)[i].e, 1, 1, file)) {
			return 0;
		}
		if (!vfs_fwrite(&((Rec*)amt_OfficeSlots)[i].f, 4, 1, file)) {
			return 0;
		}
	}
	return 1;
}
