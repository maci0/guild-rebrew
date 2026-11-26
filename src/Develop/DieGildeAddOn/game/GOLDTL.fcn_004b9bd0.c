#include "client_types.h"
#include "Develop/DieGildeAddOn/game/spiel.h"
#include <string.h>

#pragma pack(push, 2)






#pragma pack(pop)
// SIZE 0xe

extern char g_868060[];

extern pos14_7f4c00 gm_GameTime;

unsigned short* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(unsigned short*, int);
char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);

int __cdecl gm_CheckEntityType(char*);
unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x004b9bd0 */
int __cdecl fcn_004b9bd0(int* a1)
{
	char* x1;
	char* x2;
	char* y;
	pos14_7f4c00 d;
	char* ys[8];
	char* ss[8];
	char buf[0x200];
	unsigned short* e;
	char* s;
	int count;
	int index;

	count = 0;
	e = gm_LookupEntityRecordById(a1[0]);
	if (e == 0)
		return 1;
	if (gm_HasActiveSpecialObject(e, 0x290))
		return 0x400;
	for (s = he_StartHandlungSearch(1, 0, 0xf); s != 0 && count < 8; s = he_fn_Handlung()) {
		gm_ResolveEntityById(0, (void**) (&y), 0, *(int*) (s + 0xac));
		if (y != 0 && *(int*) (y + 0xa) == *e) {
			gm_ResolveEntityById((void**) (&x1), 0, 0, *(int*) (s + 0xb4));
			gm_ResolveEntityById((void**) (&x2), 0, 0, *(int*) (s + 0xb0));
			if ((x1 != 0 && gm_CheckEntityType(x1) != 0) || (x2 != 0 && gm_CheckEntityType(x2) != 0)) {
				if ((x1 != 0 && x2 != 0 && *x2 == 'G') || *x1 == 'G') {
					ss[count] = s;
					ys[count] = y;
					count++;
				}
			}
		}
	}
	if (count == 0)
		return 0x400;
	d = (*(pos14_7f4c00*)&gm_GameTime);
	d.a++;
	index = gm_RandomMod(count);
	s = ss[index];
	y = ys[index];
	gm_ResolveEntityById((void**) (&x2), 0, 0, *(int*) (s + 0xb0));
	gm_ResolveEntityById((void**) (&x1), 0, 0, *(int*) (s + 0xb4));
	if (x2 != 0 && x1 != 0) {
		if (*x2 == 'G')
			io_FormatTextBuffer(buf, *(unsigned short*) (a1 + 1) + 0x12e7, g_868060 + *(int*) (x2 + 0x65) * 756, g_868060, &d, g_868060);
		else
			io_FormatTextBuffer(buf, *(unsigned short*) (a1 + 1) + 0x12e7, g_868060, g_868060 + *(int*) (x1 + 0x65) * 756, &d, g_868060 + *(int*) (x1 + 0x65) * 756);
		fcn_00545d40(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x5ef, 0);
	}
	return 0;
}
