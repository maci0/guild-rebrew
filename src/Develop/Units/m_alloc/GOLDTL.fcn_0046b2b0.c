#include <string.h>
#include "client_types.h"

extern char* g_1015ea0;
extern void** g_772540;
extern int g_772528;
extern Fld_102d140* tp_d2_SelectedControl;
extern Fld_102d140 g_102d140[];

void __cdecl m_FreeTracked(void* p);
void __cdecl fcn_00475f80(void* surf);
void __cdecl d2_ClearAnimationSlot(int h);
int __cdecl d2_DestroyWindow(int win);
void __cdecl d2_SubRefcount(int i);
void __cdecl d2_AddDirtyRect(int x, int y, int w, int h, void* owner);
void* __cdecl fcn_0064d740(void* dst, const void* src, unsigned int n);

#include "Develop/Units/d2.v1/d2_gui.h"
/* Releases one entity slot: runs the state-specific teardown, detaches it from
 * its window list and panel, then clears the slot record. */
/* ADDRESS: GOLDTL 0x0046b2b0 */
void __cdecl d2_DestroyElement(int id)
{
	char* e;
	char* list;
	Fld_102d140* f;
	int n;
	int i;
	int state;

	e = (char*) &((D2_CONTROL_TL*) g_1015ea0)[id];
	if ((*(D2_CONTROL_TL*) e).value_004 == 0) {
		return;
	}
	state = (*(D2_CONTROL_TL*) e).kind;
	switch (state) {
	case 0x43:
		if ((*(D2_CONTROL_TL*) e).value_088 != 0) {
			m_FreeTracked((void*) (*(D2_CONTROL_TL*) e).value_088);
		}
		break;
	case 4:
		d2_ClearAnimationSlot((*(D2_CONTROL_TL*) e).value_088);
		break;
	case 0x40:
		d2_DestroyWindow((*(D2_CONTROL_TL*) e).value_088);
		break;
	case 0x41:
		f = &g_102d140[(*(D2_CONTROL_TL*) e).value_088];
		if (tp_d2_SelectedControl == f) {
			tp_d2_SelectedControl = 0;
		}
		if (f->def != -1) {
			d2_SubRefcount(f->def);
		}
		memset(f, 0, sizeof(Fld_102d140));
		break;
	case 9:
		list = *(char**) (&(*(D2_CONTROL_TL*) e).parent);
		if (list != 0) {
			*(int*) (list + 0x3c4) = 0;
		}
		break;
	case 0x47:
		if ((*(D2_CONTROL_TL*) e).payload.fields.value_08c != 0) {
			fcn_00475f80((void*) (*(D2_CONTROL_TL*) e).payload.fields.value_08c);
		}
		break;
	default:
		break;
	}
	if ((*(D2_CONTROL_TL*) e).kind < 0x40) {
		d2_SubRefcount((*(D2_CONTROL_TL*) e).value_008);
	}
	list = *(char**) (&(*(D2_CONTROL_TL*) e).parent);
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
	list = *(char**) (&(*(D2_CONTROL_TL*) e).value_050);
	if (list != 0 && *(int*) (list + 0x198) != 0) {
		d2_AddDirtyRect((*(D2_CONTROL_TL*) e).x, (*(D2_CONTROL_TL*) e).y, (*(D2_CONTROL_TL*) e).width, (*(D2_CONTROL_TL*) e).height, list);
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
	memset((char*) &((D2_CONTROL_TL*) g_1015ea0)[id], 0, 0x2f4);
	*(int*) ((char*) &((D2_CONTROL_TL*) g_1015ea0)[id]) = id;
}
