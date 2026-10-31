#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_00545780(char* a);
void __cdecl fcn_00546190(char* a);
int __cdecl fcn_00545670(char* a, int b, int c, char* d, int e);
void __cdecl fcn_0057b070(char* a);
void __cdecl fcn_0057b160(char* a);
void __cdecl fcn_00471b60(int id);
void __cdecl d2_SetForm(int a, int b);
void __cdecl fcn_004c30a0(int a, int b, char* c, int d, int e);
int __cdecl io_AppendText(int a, ...);
int __cdecl fcn_00500cb0(void* a, void* b);

/* ADDRESS: GOLDTL 0x0057b1f0 */
void __cdecl fcn_0057b1f0(char* a)
{
	int state;

	state = *(int*) (a + 0x70);
	if (state == -2) {
		if (*(int*) (a + 0x74) != 0)
			fcn_00545780(a);
		fcn_00546190(a);
		return;
	}
	switch (state) {
	case 1:
		if (fcn_00500cb0((void*) 0x7f4c00, a + 0x52) > 0)
			goto activate;
		if (*(int*) (a + 0x74) == 0) {
			*(int*) (a + 0x70) = 0;
			return;
		}
		if (*(int*) 0x100f884 != *(int*) (*(int*) (a + 0x74) + 8))
			return;
		if (*(int*) 0x100f1dc == -1)
			return;
		if (*(int*) 0x100f1dc == 2) {
			fcn_0057b070(a);
			fcn_00545780(a);
			fcn_00546190(a);
			return;
		}
		if (*(int*) 0x100f1dc != 1)
			return;
	activate:
		fcn_0057b160(a);
		fcn_00545780(a);
		fcn_00546190(a);
		return;
	case 0:
		if (*(int*) (a + 0x74) == 0)
			fcn_00545670(a, 0, 0, (char*) 0x6a5a10, 0x5ec);
	if (*(int*) (a + 0x74) == 0) {
		fcn_00546190(a);
		return;
	}
	fcn_00471b60(*(int*) (*(int*) (a + 0x74) + 8));
	d2_SetForm(*(int*) (*(int*) (a + 0x74) + 8), 0);
	io_AppendText(0x6811b0);
	io_AppendText(0x411c, *(int*) (a + 0xb8));
	fcn_004c30a0(-7, 0, (char*) 0x6a8034, -1, 0);
	*(int*) (a + 0x70) = 1;
	}
}
