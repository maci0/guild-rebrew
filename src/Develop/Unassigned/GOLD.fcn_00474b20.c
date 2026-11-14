#include <string.h>
#include "Develop/Units/d2.v1/d2_gui.h"
#include "client_types.h"

/* Gold window table 0xf8f120; the Gold record is 0x3c4 bytes, not the shared
 * Win_1015f40 size, so rows are addressed with the native stride. */
extern Win_1015f40 g_1015f40[0x60];

int __cdecl fcn_004741e0(int, int, char*);
int __cdecl fcn_00478cb0(void*, int);

/* Opens a screen page: creates it, flags its window and every child GUI entity
 * (+0x38), and builds the two 0x40-byte descriptors stored at +0x1a4/+0x1a8. */
/* ADDRESS: GOLD 0x00474b20 */
int __cdecl fcn_00474b20(int a0, int a1, char* a2)
{
	int buf[0x10];
	int r;
	char* rec;
	char* w;
	int i;
	int j;

	r = fcn_004741e0(a0, a1, a2);
	if (r != 0) {
		rec = (char*) 0xfb1020 + r * 0x2ac;
		for (i = 0; i < *(int*) (rec + 0x184); i++) {
			w = (char*) g_1015f40 + ((int*) (rec + 4))[i] * 0x3c4;
			*(int*) ((char*) &g_00f8f080[*(int*) (w + 0x26c)] + 0x38) = 1;
			for (j = 0; j < *(short*) (w + 0x1c); j++) {
				*(int*) ((char*) &g_00f8f080[(*(int**) (w + 0x18))[j]] + 0x38) = 1;
			}
		}
		*(int*) (rec + 0x198) = 1;
		w = (char*) g_1015f40 + *(int*) (rec + 4) * 0x3c4;
		memset(buf, 0, sizeof(buf));
		buf[1] = *(short*) (w + 8);
		buf[2] = *(short*) (w + 0xa);
		*(int*) (rec + 0x1a4) = fcn_00478cb0(buf, 3);
		memset(buf, 0, sizeof(buf));
		buf[1] = *(short*) (w + 8);
		buf[2] = *(short*) (w + 0xa);
		*(int*) (rec + 0x1a8) = fcn_00478cb0(buf, 3);
		return r;
	}
	return 0;
}
