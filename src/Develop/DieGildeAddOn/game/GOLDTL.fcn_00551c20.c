#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern int g_774800;

void* __cdecl fcn_005463a0(int a1, int a2, int a3, int a4, int a5);
void* __cdecl he_fn_Handlung(void);
void __cdecl fcn_00546190(char* obj);
void __cdecl fcn_00500bb0(void* clock, int arg2, int arg3, int arg4);

/* ADDRESS: GOLDTL 0x00551c20 */
void __cdecl fcn_00551c20(char* obj)
{
	char* v;
	unsigned int idx;
	unsigned char type;
	unsigned char shade;
	unsigned char tilt;
	int t;

	idx = *(unsigned short*) (obj + 8);
	type = *(unsigned char*) (obj + 0xae);
	shade = *(unsigned char*) (type + idx * 0x21c + 0x7f4d20);
	if (*(float*) 0x66413c <= (float) shade) {
		fcn_00546190(obj);
		return;
	}
	{
		v = (char*) fcn_005463a0(2, 2, idx, 0, 0x60);
		while (v != 0) {
			if (v != obj) {
				fcn_00546190(obj);
				return;
			}
			v = (char*) he_fn_Handlung();
		}
		idx = *(unsigned short*) (obj + 8);
		type = *(unsigned char*) (obj + 0xae);
		shade = *(unsigned char*) (type + idx * 0x21c + 0x7f4d20);
		t = (int) ((float) shade * *(float*) 0x664168 + *(float*) 0x6628a0);
		tilt = (unsigned char) t;
		tilt = (unsigned char) (tilt + 2);
		tilt = (unsigned char) (tilt * 2);
		*(unsigned char*) (obj + 0xac) = 0x15;
		*(int*) (obj + 0x70) = 0;
		*(unsigned char*) (obj + 0xad) = tilt;
		*(pos14_7f4c00*) (obj + 0x52) = g_7f4c00;
		if (g_774800 != 0) {
			fcn_00500bb0(obj + 0x52, 0, 0, 1);
		} else {
			fcn_00500bb0(obj + 0x52, 5, 0, 0);
		}
		*(pos14_7f4c00*) (obj + 0x44) = g_7f4c00;
	}
}
