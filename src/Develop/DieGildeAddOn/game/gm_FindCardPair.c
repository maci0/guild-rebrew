

typedef struct Card {
	int v;
	int a;
	int b;
	int c;
} Card;
// SIZE 0x10

#include "Develop/client_types.h"
extern Card_1007ce0 g_1007ce0[24];

int __cdecl gm_FindCardPair(int* h, int* out, int skipFirst)
{
	int i;
	int j;
	int v;

	i = skipFirst ? 2 : 0;
	if (h[i] < 0 || h[i + 1] < 0) {
		return 0;
	}
	for (; i < 4; i++) {
		v = ((Card*)g_1007ce0)[h[i]].v;
		out[0] = h[i];
		for (j = i + 1; j < 5; j++) {
			if (h[j] < 0) {
				return 0;
			}
			if (((Card*)g_1007ce0)[h[j]].v == v) {
				out[1] = h[j];
				return 1;
			}
		}
	}
	return 0;
}
