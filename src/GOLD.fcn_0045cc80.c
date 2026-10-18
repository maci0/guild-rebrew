#include "client_scene_resources.h"

typedef struct Inner5cc80 {
	int f0;
	int f4;
	int f8;
	int fc;
} Inner5cc80;

typedef struct Holder5cc80 {
	SCENE_RESOURCE* p;
	int pad;
	Inner5cc80* n;
} Holder5cc80;


/* ADDRESS: GOLD 0x0045cc80 */
void __cdecl fcn_0045cc80(Holder5cc80* h)
{
	Inner5cc80* n;

	if (h->p != 0) {
		n = h->n;
		if (n != 0) {
			n->f4 = 0;
			n->f0 = 0;
			n->fc = 0;
		}
		fcn_0045fbb0(h->p);
		h->p = 0;
		h->n = 0;
	}
}
