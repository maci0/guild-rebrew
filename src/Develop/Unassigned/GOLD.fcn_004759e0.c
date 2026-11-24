#include "gold_gui.h"

int __cdecl fcn_004690a0(int);

/* ADDRESS: GOLD 0x004759e0 */
int __cdecl fcn_004759e0(int id, int* out, int* out2)
{
	char* rec;
	char* font;
	char* sub;
	int kind;
	unsigned short w;

	if (id != -1) {
		rec = (char*) &g_00f8f080[id];
		kind = *(int*) (rec + 0x18);
		if (kind == 1 || kind == 8 || kind == 5) {
			font = (char*) fcn_004690a0(*(int*) (rec + 8));
			if (font != 0) {
				kind = *(int*) (rec + 0x18);
				if (kind == 8 || kind == 5) {
					sub = font + *(int*) (font + *(int*) (rec + 0x78) * 4 + 0x45);
					if (sub != 0) {
						w = *(unsigned short*) (sub + 6);
						*out = w;
						w = *(unsigned short*) (sub + 0xa);
						*out2 = w;
					}
					return 1;
				}
				*out = *(unsigned short*) (font + 0x2c);
				*out2 = *(unsigned short*) (font + 0x2e);
				return 1;
			}
		}
	}
	return 0;
}
