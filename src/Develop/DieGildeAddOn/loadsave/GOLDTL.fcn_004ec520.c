


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
extern char g_68de84[];

void __cdecl srv_LogWinsockError(void);
#include "Develop/DieGildeAddOn/loadsave/loadsave.h"

int __cdecl amt_fio_LoadAemter(void* file, int version)
{
	int cnt;
	char buf[256];
	unsigned int n;
	unsigned int i;

	n = version >= 0x10051 ? 0x2a : 0x25;
	srv_LogWinsockError();
	if (file == 0) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(&cnt, 4, 1, file)) {
		return 0;
	}
	if ((unsigned int)cnt != n) {
		sprintf(buf, g_68de84, cnt, 0x2a);
		return 0;
	}
	for (i = 0; i < n; i++) {
		if (!ls_ReadVfsDataChecked(&((Rec*)amt_OfficeSlots)[i].a, 1, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec*)amt_OfficeSlots)[i].b, 4, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec*)amt_OfficeSlots)[i].c, 1, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec*)amt_OfficeSlots)[i].d, 4, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec*)amt_OfficeSlots)[i].e, 1, 1, file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(&((Rec*)amt_OfficeSlots)[i].f, 4, 1, file)) {
			return 0;
		}
	}
	return 1;
}
