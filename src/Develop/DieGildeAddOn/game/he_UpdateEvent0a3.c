#include "Develop/client_types.h"

extern pos14_7f4c00 gm_GameTime;

unsigned short* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl gm_RandomMod(unsigned short n);
void __cdecl gm_AddTime(void* clock, int arg2, int arg3, int arg4);
void __cdecl gm_ModifyHealth(int a, int b);
void __cdecl io_FormatTextBuffer(int a, int b, ...);
void __cdecl he_PostEntityMessage(int a, int b, void* buf, int d, int e, void* f);
void __cdecl he_FreeAction(char* a);


/* ADDRESS: GOLDDE 0x00563810 */
void __cdecl he_UpdateEvent0a3(char* a)
{
	unsigned short* e;
	int v;
	char buf[0x400];

	e = gm_LookupEntityRecordById(*(int*) (a + 0xc));
	if (*(int*) (a + 0x70) == -1 || *(int*) (a + 0x70) == -2 || *(int*) (a + 0x70) > 3 || e == 0) {
		he_FreeAction(a);
		return;
	}
	*(int*) (a + 0x70) = *(int*) (a + 0x70) + 1;
	gm_AddTime(a + 0x52, (gm_RandomMod(3) & 0xffff) + 3, 0, 0);
	v = *(int*) ((char*) e + 0x194);
	if (v < 1)
		return;
	if ((int) ((gm_RandomMod(2) & 0xffff) + 1) < v)
		v = (int) ((gm_RandomMod(2) & 0xffff) + 1);
	gm_ModifyHealth(*(int*) ((char*) e + 4), -v);
	if (*(char*) ((char*) e + 2) == 6 || *(char*) ((char*) e + 2) == 7) {
		io_FormatTextBuffer((int) buf, 0x1008, v);
		he_PostEntityMessage(*(int*) ((char*) e + 4), -1, buf, 0, 0x5fb, 0);
	}
	if (*(int*) (a + 0x70) <= 3)
		return;
	*(pos14_7f4c00*) (a + 0x52) = gm_GameTime;
}
