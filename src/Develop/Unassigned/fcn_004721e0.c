#include "client_data.h"
#include "Develop/Units/d2.v1/d2_window_view.h"

extern int g_772534;
extern char* g_1015ea0;

/* ADDRESS: GOLDTL 0x004721e0 */
int* __cdecl fcn_004721e0(int a, int b, int c)
{
	int n;
	int value;
	int count;
	D2_WIN* win;
	int* arr;
	int idx;
	int flag;

	n = g_772534;
	value = g_1038144[n].i[b];
	win = &((D2_WIN*)g_1015f40)[value];
	count = win->count;
	if (a > count - 1) {
		return (int*) win;
	}
	arr = win->children;
	idx = arr[a];
	flag = (c == 0);
	*(int*) (g_1015ea0 + (idx * 189 + 18) * 4) = flag; /* no return: native leaves the base in eax, no callers */
}
