#include "client_data.h"

extern int g_772534;
extern char* g_1015ea0;

/* ADDRESS: GOLDTL 0x004721e0 */
int* __cdecl fcn_004721e0(int a, int b, int c)
{
	int n;
	int value;
	int count;
	Win_1015f40* win;
	int* arr;
	int idx;
	int flag;

	n = g_772534;
	value = g_1038144[n].i[b];
	win = &g_1015f40[value];
	count = *(int*) ((char*) win + 0x2c);
	if (a > count - 1) {
		return (int*) win;
	}
	arr = *(int**) ((char*) win + 0x28);
	idx = arr[a];
	flag = (c == 0);
	*(int*) (g_1015ea0 + (idx * 189 + 18) * 4) = flag;
	return (int*) g_1015ea0;
}
