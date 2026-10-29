


// SIZE 0xa
typedef struct {
	unsigned char state;
	char pad[9];
} Slot10;

extern unsigned int g_100581c;
extern unsigned int g_aed204;
#include "client_types.h"
extern cell10_fb5760 g_fb5760[0x8000];

int __cdecl fcn_004c44c0(void)
{
	unsigned int i;
	unsigned int end;
	int r;

	i = g_100581c;
	end = g_aed204;
	r = 1;
	while (i != end) {
		if (i >= end) {
			break;
		}
		if (((Slot10*)g_fb5760)[i & 0x7fff].state == 0) {
			return 0;
		}
		if (((Slot10*)g_fb5760)[i & 0x7fff].state == 2) {
			r = -1;
		}
		i++;
		if (i >= end) {
			break;
		}
	}
	return r;
}
