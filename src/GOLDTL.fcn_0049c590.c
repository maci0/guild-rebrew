/* Command handler for the entity selection dialog: reacts to the show (0x12)
 * and hide (0x0f) command of the dialog record and drives the GUI helpers. */

#include <math.h>

extern char* g_7f4ca0;
extern char g_773d75;
extern float g_1009b6c;
extern float g_1009b74;
extern float g_1009b7c;
extern float g_1009b8c;
extern float g_1009b94;
extern float g_1009b9c;

int __cdecl fcn_00503fe0(int a0, int a1, int a2);
int __cdecl fcn_00502cd0(int a0, int a1, int a2, int a3, int a4);
void __cdecl fcn_004c4510(int a0, int a1);
void __cdecl fcn_004c4670(int a0, int a1, int a2, char* a3);
int __cdecl fcn_004c5360(void);
int __cdecl fcn_004c51a0(int a0, int a1, char a2, int a3);
void __cdecl fcn_004f5e20(int a0, int a1);
void __cdecl fcn_005b2150(int a0, char* a1, int a2, int a3, int a4);
void __cdecl fcn_005100f0(int a0, int a1);
void __cdecl fcn_005b21d0(int a0, char* a1, int a2);

/* ADDRESS: GOLDTL 0x0049c590 */
int __cdecl fcn_0049c590(int a0, char* a1, char* a2, int a3)
{
	int rec;
	int v5;
	unsigned char cmd;

	if (*(unsigned char*) a1 != 4) {
		return 0;
	}
	rec = fcn_00503fe0(1, 1, *(int*) (a1 + 4));
	if (rec == 0) {
		return 0;
	}
	if (*(unsigned short*) (rec + 0x27) == 0xffff) {
		return 0;
	}
	v5 = fcn_00502cd0(*(int*) (rec + 0x5d), 2, 6, 0, 0xf2);
	cmd = *(unsigned char*) a2;
	if (cmd == 0x12) {
		fcn_004c4510(a0, *(int*) (a0 + 4));
		fcn_004c4670(4, 1, 0x1ac, a1 + 0x10);
		fcn_004c5360();
		fcn_004c51a0(-1, *(int*) (a0 + 4), g_773d75,
		    *(int*) (a1 + 0x10));
		fcn_004c51a0(*(int*) (g_7f4ca0
			+ *(unsigned short*) (rec + 0x27) * 0x21c + 4),
		    -1, g_773d75, a3);
		fcn_004f5e20(*(int*) (a0 + 4), (int) *(float*) (a1 + 0x14));
		fcn_005b2150(a0,
		    g_7f4ca0 + *(unsigned short*) (rec + 0x27) * 0x21c,
		    rec, a3, *(int*) (a1 + 0x10));
		g_1009b8c = g_1009b6c * *(float*) (a1 + 0x14);
		g_1009b94 = g_1009b74 * *(float*) (a1 + 0x14);
		g_1009b9c = g_1009b7c * *(float*) (a1 + 0x14);
		return 0x26;
	}
	if (cmd == 0x0f && v5 != 0) {
		fcn_004f5e20(*(int*) (a0 + 4), (int) *(float*) (a1 + 0x14));
		fcn_005100f0(*(int*) (a0 + 4), -*(int*) (a1 + 0x10));
		fcn_005100f0(*(int*) (g_7f4ca0
			+ *(unsigned short*) (rec + 0x27) * 0x21c + 4), 1);
		fcn_005b21d0(a0,
		    g_7f4ca0 + *(unsigned short*) (rec + 0x27) * 0x21c, rec);
		return 0x26;
	}
	return 0;
}
