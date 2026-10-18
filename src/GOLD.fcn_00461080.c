#include "client_scene_loader.h"
#include "client_scene_resources.h"

/* ADDRESS: GOLD 0x00461080 */
void __cdecl fcn_00461080(int selector, SCENE_PROGRESS callback)
{
	unsigned int count;
	unsigned int n;
	unsigned int index;
	int done;
	int total;
	SCENE_RESOURCE *base;
	unsigned char *flags;

	/* Both zero initializations survive in the native function. */
	*(volatile int *)&total = 0;
	count = g_10404a0;
	base = g_104049c;
	if (callback != 0) {
		*(volatile int *)&total = 0;
		if (count > 0) {
			flags = (unsigned char *)base + 0x68;
			n = count;
			do {
				if (*(int *)(flags - 0x28) > 0 && (*flags & 2) == 0)
					total++;
				flags += 0x80;
				n--;
			} while (n != 0);
		}
	}
	done = 0;
	for (index = 0; index < count; index++, base++) {
		if (base->level > 0 && (base->flags & 2) == 0) {
			fcn_00460e40(base, selector);
			if (callback != 0)
				callback(1, done, total);
			count = g_10404a0;
			done++;
		}
	}
	g_6b8af0 = 0;
}
