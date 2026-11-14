int __cdecl gm_WalkEntityChain(int);
int __cdecl gm_AccumulateTyped2(char*);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472380(int, int, int, int);
int __cdecl fcn_0050b710(int, unsigned char);
int __cdecl fcn_0050b750(int, int);
int __cdecl fcn_00526010(void*, int, int);
void __cdecl fcn_004c5150(int, int, int, int);
void __cdecl fcn_004c4510(void*, int);
int __cdecl fcn_004c4570(unsigned char, unsigned char, unsigned short, char*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c4ef0(char*);
int __cdecl fcn_00471f80(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
extern int g_14ce8e0, g_67d370, g_774654;
#define SHP_REC (g_7f4ca0 + g_774970 * 0x21c)
#define SHP_ID (*(unsigned short*) SHP_REC)
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x005d2470 */
int __cdecl fcn_005d2470(int* arg2, unsigned short* arg3)
{
	int v14 = -1;
	float v4;
	float selected;
	int flags;
	int v8;
	int ebp;
	int flag;
	int dlg;
	int v18 = -1;
	int vc = -1;
	int r;
	int hv;
	int uv;
	int v10;

	v14 = (int) ((float) gm_WalkEntityChain(SHP_ID) * 0.005f);
	if (v14 < 0x640) {
		v14 = 0x640;
	} else {
		v14 = (int) ((float) gm_WalkEntityChain(SHP_ID) * 0.005f);
	}
	v4 = (float) gm_WalkEntityChain(SHP_ID) * 0.05f;
	v8 = gm_AccumulateTyped2(SHP_REC);
	if ((float) v8 > v4) {
		selected = (float) gm_WalkEntityChain(SHP_ID) * 0.05f;
	} else {
		selected = (float) gm_AccumulateTyped2(SHP_REC);
	}
	if ((int) selected < 0xc80) {
		ebp = 0xc80;
	} else {
		v4 = (float) gm_WalkEntityChain(SHP_ID) * 0.05f;
		v8 = gm_AccumulateTyped2(SHP_REC);
		if ((float) v8 > v4) {
			selected = (float) gm_WalkEntityChain(SHP_ID) * 0.05f;
		} else {
			selected = (float) gm_AccumulateTyped2(SHP_REC);
		}
		ebp = (int) selected;
		if (ebp < 1) return 0;
	}
	flag = (*(unsigned int*) ((char*) arg2 + 0x1c8) >> 5) & 1;
	dlg = fcn_00470820(0, 0, (char*) 0x6acbac);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(dlg);
	d2_SetForm(dlg, 1);
	io_AppendText(0x1f4c);
	if (flag != 0) {
		io_AppendText(0x1f4f);
	} else {
		v10 = fcn_00472250(dlg, 1,
		    io_AppendText(0x1f4d, *arg3, *(unsigned char*) &g_773d75));
		hv = io_AppendText(0x1f4e);
		v18 = fcn_00472250(dlg, 1, hv);
		vc = fcn_00472250(dlg, 1, hv + 1);
		fcn_00472380(v10,
		    fcn_0050b710(v14, *(unsigned char*) &g_773d75),
		    fcn_0050b710(ebp, *(unsigned char*) &g_773d75),
		    fcn_0050b710(v14, *(unsigned char*) &g_773d75));
	}
	*(int*) &g_100f1dc = -1;
	r = 0;
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (*(int*) &g_100f1dc == -1 || flag != 0) {
			continue;
		}
		if (g_67d370 == v18) {
			hv = fcn_00471f80(v10);
			uv = fcn_0050b750(hv, *(unsigned char*) &g_773d75);
			if (fcn_00526010((void*) ((unsigned long)&g_7f4ca0 +
				*(unsigned short*) &g_774970 * 0x21c), uv,
				*(unsigned char*) &g_773d75) != 0) {
				flags = *(unsigned int*) ((char*) arg2 + 0x1c8) | 0x20;
				fcn_004c4eb0((char*) 0x6acba4);
				fcn_004c5150(*(int*) ((char*) arg3 + 4),
				    *(int*) ((char*) arg2 + 4),
				    *(unsigned char*) &g_773d75, uv);
				fcn_004c4510(arg2, *(int*) ((char*) arg2 + 4));
				fcn_004c4570(4, 1, 0x1c8, (char*) &flags);
				fcn_004c5360();
				fcn_004c4ef0((char*) 0x6acba4);
			}
			r = 1;
			g_774654 = 1;
		} else if (g_67d370 == vc) {
			g_774654 = 1;
		}
	} while (fcn_005373e0((void*) fcn_005d2470, 0x677c7) != 0);
	fcn_00471e30(dlg);
	return r;
}
