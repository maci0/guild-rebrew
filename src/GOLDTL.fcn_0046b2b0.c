#include <string.h>
#include "client_types.h"

extern char* g_1015ea0;
extern void** g_772540;
extern int g_772528;
extern Fld_102d140* g_7725d0;
extern Fld_102d140 g_102d140[];

void __cdecl fcn_0041ddd0(void* p);
void __cdecl fcn_00475f80(void* surf);
void __cdecl fcn_0047a2b0(int h);
int __cdecl fcn_0046f390(int win);
void __cdecl fcn_00469960(int i);
void __cdecl fcn_00465ff0(int x, int y, int w, int h, void* owner);
void* __cdecl fcn_0064d740(void* dst, const void* src, unsigned int n);

/* ADDRESS: GOLDTL 0x0046b2b0 */

/* Releases one entity slot: runs the state-specific teardown, detaches it from
 * its window list and panel, then clears the slot record. */
void __cdecl fcn_0046b2b0(int id)
{
	char* e;
	char* list;
	Fld_102d140* f;
	int n;
	int i;
	int state;

	e = g_1015ea0 + id * 0x2f4;
	if (*(int*) (e + 4) == 0) {
		return;
	}
	state = *(int*) (e + 0x20);
	switch (state) {
	case 0x43:
		if (*(int*) (e + 0x88) != 0) {
			fcn_0041ddd0((void*) *(int*) (e + 0x88));
		}
		break;
	case 4:
		fcn_0047a2b0(*(int*) (e + 0x88));
		break;
	case 0x40:
		fcn_0046f390(*(int*) (e + 0x88));
		break;
	case 0x41:
		f = &g_102d140[*(int*) (e + 0x88)];
		if (g_7725d0 == f) {
			g_7725d0 = 0;
		}
		if (f->def != -1) {
			fcn_00469960(f->def);
		}
		memset(f, 0, sizeof(Fld_102d140));
		break;
	case 9:
		list = *(char**) (e + 0x40);
		if (list != 0) {
			*(int*) (list + 0x3c4) = 0;
		}
		break;
	case 0x47:
		if (*(int*) (e + 0x8c) != 0) {
			fcn_00475f80((void*) *(int*) (e + 0x8c));
		}
		break;
	default:
		break;
	}
	if (*(int*) (e + 0x20) < 0x40) {
		fcn_00469960(*(int*) (e + 8));
	}
	list = *(char**) (e + 0x40);
	if (list != 0) {
		n = *(int*) (list + 0x2c);
		i = 0;
		while (i < n && *(int*) (*(int*) (list + 0x28) + i++ * 4) != id) {
		}
		i--;
		if (i != n) {
			fcn_0064d740((char*) *(int*) (list + 0x28) + i * 4,
			    (char*) *(int*) (list + 0x28) + i * 4 + 4,
			    (n - i) * 4);
		}
		(*(int*) (list + 0x2c))--;
	}
	list = *(char**) (e + 0x50);
	if (list != 0 && *(int*) (list + 0x198) != 0) {
		fcn_00465ff0(*(int*) (e + 0x10), *(int*) (e + 0x14), *(int*) (e + 0x18), *(int*) (e + 0x1c), list);
	}
	for (i = 0; i < 0x3ff; i++) {
		if (g_772540[i] == (void*) e) {
			if (i == 0x3ff) {
				g_772540[0x3ff] = 0;
			} else {
				fcn_0064d740(&g_772540[i], &g_772540[i + 1], (0x3fe - i) * 4);
			}
			break;
		}
	}
	if (id == g_772528) {
		g_772528 = id - 1;
	}
	memset(g_1015ea0 + id * 0x2f4, 0, 0x2f4);
	*(int*) (g_1015ea0 + id * 0x2f4) = id;
}
