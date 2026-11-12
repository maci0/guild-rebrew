#include "client_data.h"
extern int g_67fca8;
extern int g_67fca4;
extern unsigned char g_7728d4;
int __cdecl hst_ParseDate(int, int, int*, int);
int __cdecl fcn_004b2dd0(char*, int, int);

/* ADDRESS: GOLDTL 0x004b3720 */
int __cdecl fcn_004b3720(int a0, char* a1, int a2)
{
	int pos;
	int result;
	int slot[4];

	pos = g_67fca8;
	for (;;) {
		if (g_7728d4 == 0) {
			return 3;
		}
		if (!hst_ParseDate(pos, 3, slot, a0)) {
			g_7728d4 = 0;
			return 4;
		}
		result = g_7f4c00.a - slot[0];
		if (result == 1) {
			pos = fcn_004b2dd0(a1, g_67fca8, a2);
			if (pos) {

				if (*a1 == 0) {
					result = 6;
				}
			} else {
				result = 5;
			}
		} else {
			if (result <= 1) {
				return 2;
			}
			result = 0;
		}
		pos = g_67fca8 + 3;
		g_67fca8 = pos;
		if (g_67fca4 < pos) {
			g_7728d4 = 0;
		}
		if (result != 0 && result != 6 && result != 5) {
			break;
		}
	}
	return result;
}
