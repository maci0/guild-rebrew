#include "Develop/DieGildeAddOn/game/entity.h"

extern unsigned short g_774970;
extern int g_772514;
extern int g_775338;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_005340f0(int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_005c9450(unsigned short*, int, int*);
int __cdecl fcn_00472830(int, int);
void __cdecl fcn_00533f40(int, int, int, int, int, int*, int*, int*);

/* ADDRESS: GOLDTL 0x005c86b0 */
int __cdecl fcn_005c86b0(void)
{
	int a;
	int b;
	int c;
	int h;
	unsigned short* p;

	p = (unsigned short*) &((EntityStruct*) g_slot_table)[g_774970];
	h = fcn_00470820(0, 0, (char*) 0x6ac834);
	fcn_00471b60(h);
	d2_SetForm(h, 0);
	fcn_005340f0(g_772514);
	d2_SetForm(h, 1);
	io_AppendText(0xb2);
	d2_SetForm(h, 2);
	g_775338 = fcn_005c9450(p, 0x80, (int*) 0x778900);
	d2_SetForm(h, 0);
	fcn_00533f40(0x206, 0x167, g_772514,
				 fcn_00472830(h, 2), 0x40, &c, &b, &a);
	return h;
}
