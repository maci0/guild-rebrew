

#include <string.h>
#pragma intrinsic(memset)

#include "client_types.h"
typedef Group_102cbc4 Group;
// SIZE 0x8c

// SIZE 0x2f4
typedef struct {
	char pad0[0x38];
	int shown;
	int active;
	char pad40[0x2b0];
	unsigned char* obj;
} Slot5ada;

extern Group_102cbc4 g_102cbc4[8];
extern char* g_1015ea0;
extern int g_772514;
extern int g_100f1dc;
extern int g_14ce8e0;
extern int g_774654;
extern int g_67d370;
extern char g_6ab1e4[];
extern char g_6811b0[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText();
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00476b60(void);
int __cdecl fcn_00472250(int, int, int);
int __cdecl fcn_00472830(int k, int j);
void __cdecl fcn_0046e830(int x, int y, int win, int target, int id);
void __cdecl fcn_00469510(int i);
unsigned char* __cdecl fcn_00502cd0(int, int, int, int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
void* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_0050c5d0(unsigned char* o, int* out);
void __cdecl fcn_004c5120(int);
int __cdecl d2_CreateRadioGroup(int n, ...);
void __cdecl fcn_00469470(int g, int id);
int __cdecl fcn_0046c690(int a);
int __cdecl fcn_004c5a60(int a1, int a2, int a3);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_00471e30(int);

void __cdecl fcn_005ada30(char* p)
{
	int n;
	int i;
	int back;
	int val[2];
	unsigned char* carts[8];
	int btns[16];
	unsigned char* e;
	unsigned char* q;
	int refresh;
	int grp;
	int d;
	int j;
	int b;
	int r;

	refresh = 1;
	n = 0;
	grp = -1;
	d = fcn_00470820(0, 0, g_6ab1e4);
	fcn_00471b60(d);
	d2_SetForm(d, 1);
	io_AppendText(0x19fb);
	d2_SetOverlayAnimation(0, 0);
	fcn_00476b60();
	d2_SetForm(d, 3);
	back = fcn_00472250(d, 3, io_AppendText(0x1ba6));
	fcn_0046e830(-1, -1, g_772514, fcn_00472830(d, 2), 0x767);
	do {
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (refresh != 0) {
			memset(carts, 0, sizeof(carts));
			if (grp != -1) {
				fcn_00469510(grp);
				grp = -1;
			}
			d2_SetForm(d, 2);
			io_AppendText(g_6811b0);
			j = 0;
			for (e = fcn_00502cd0(*(int*) (p + 0x5d), 1, 0, 0xca); e != 0 && j < 8; e = gm_NextEntityQueryMatch()) {
				q = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0x2a));
				if (q != 0 && *(unsigned short*) (q + 0x27) != 0xffff) {
					carts[j] = e;
					j++;
				}
			}
			for (i = 0; i < 8; i++) {
				e = carts[i];
				if (e != 0) {
					q = gm_StartFilteredEntitySearch(1, 1, *(int*) (e + 0x2a));
					if (q != 0) {
						if (*(unsigned short*) (q + 0x27) == 0xffff) {
							continue;
						}
						fcn_0050c5d0(q, val);
						b = fcn_00472250(d, 2, io_AppendText(0x19fc, *q + 0x427, *(unsigned short*) (q + 0x27), q, e + 0x1c, val[0], val[1], e[0x37], e[0x36]));
						btns[n] = b;
						((Slot5ada*)g_1015ea0)[b].obj = q;
						if (grp == -1) {
							grp = d2_CreateRadioGroup(1, b);
							((Slot5ada*)g_1015ea0)[b].shown = 1;
							((Slot5ada*)g_1015ea0)[b].active = 1;
							((Slot5ada*)g_1015ea0)[b].obj = q;
							g_102cbc4[grp].sel = 0;
							n++;
						}
						else {
							fcn_00469470(grp, b);
							n++;
						}
					}
					else {
						fcn_004c5120(*(int*) (e + 2));
					}
				}
			}
			refresh = 0;
		}
		if (g_100f1dc != -1 && g_67d370 == back && grp != -1) {
			i = fcn_0046c690(grp);
			if (i >= 0) {
				r = fcn_004c5a60(*(int*) (p + 1), -1, *(int*) (carts[i] + 2));
				while (fcn_004c4450(r) == 0) {
					fcn_00535960();
				}
				refresh = 1;
			}
		}
	} while (fcn_005373e0(fcn_005ada30, 0x677c7) != 0);
	if (grp != -1) {
		fcn_00469510(grp);
	}
	fcn_00532ef0();
	fcn_00471e30(d);
}
