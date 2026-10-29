#include <string.h>

int __cdecl fcn_00598150(int, int*);
void __cdecl rd_AllBauplatzToSupermap(int, int);


/* ADDRESS: GOLDTL 0x004bdd40 */
void __cdecl fcn_004bdd40(int a)
{
	int list[256];
	int n;
	int i;

	memset(list, 0, sizeof(list));
	n = fcn_00598150(0, list);
	if (n != 0) {
		for (i = 0; i < n; i++) {
			if (list[i] != 0)
				rd_AllBauplatzToSupermap(a, list[i]);
		}
	}
}
