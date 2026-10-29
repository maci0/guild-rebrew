#include "client_types.h"

extern double g_6629f8;
extern double g_662908;
extern int g_7f4c00;
extern char g_7f4ca0[];

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_00500d20(void*, void*);
void __cdecl fcn_0050ff70(void*, int);
char* __cdecl fcn_0050dc90(void*);
void __cdecl fcn_00500bb0(void*, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, void*);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_00546190(void*);

/* ADDRESS: GOLDTL 0x005639a0 */
void __cdecl fcn_005639a0(int a)
{
	char buf[0x100];
	char* r;
	char* q;
	int t;
	int id;
	int ofs;

	if (*(int*) (a + 0x70) < -2) {
		return;
	}
	if (*(int*) (a + 0x70) >= 0) {
		if (*(int*) (a + 0x70) != 0) {
			return;
		}
		r = gm_StartFilteredEntitySearch(1, 1, *(int*) (a + 0xac));
		if (r == 0) {
			fcn_00546190((void*) a);
			return;
		}
		t = fcn_00500d20((void*) (a + 0x60), (void*) &g_7f4c00);
		t = (int) ((double) t * g_6629f8 + g_662908);
		*(int*) (a + 0xb0) -= t;
		fcn_0050ff70(r, t);
		if (*(int*) (a + 0xb0) > 0) {
			*(pos14_7f4c00*) (a + 0x60) = *(pos14_7f4c00*) &g_7f4c00;
			*(pos14_7f4c00*) (a + 0x52) = *(pos14_7f4c00*) &g_7f4c00;
			fcn_00500bb0((void*) (a + 0x52), 0, 0xa, 0);
			return;
		}
		id = 0x5f6;
		q = fcn_0050dc90(r);
		if (q != 0 && *(char*) (q + 2) == 1 && (*(unsigned char*) (q + 0x1b4) & 1)) {
			id = 0x60b;
		}
		fcn_0051af00(buf, 0x17cb, (int) (unsigned char) r[0] * 0xe + 0x48e);
		if (*(unsigned short*) (a + 8) != 0xffff) {
			ofs = *(unsigned short*) (a + 8) * 0x21c;
			if (*(char*) (g_7f4ca0 + ofs + 2) == 6 || *(char*) (g_7f4ca0 + ofs + 2) == 7) {
				he_MessageBoxQuickjump(*(int*) (g_7f4ca0 + ofs + 4), -1, buf, 0, id, *(int*) (r + 1), -1, 0, (void*) 0x6a65b8);
			}
		}
		*(int*) (a + 0x70) = -1;
		return;
	}
	r = gm_StartFilteredEntitySearch(1, 1, *(int*) (a + 0xac));
	if (r != 0) {
		fcn_004c5420(*(int*) (r + 1), 0x5a, 2, 0, 4);
	}
	fcn_00546190((void*) a);
}
