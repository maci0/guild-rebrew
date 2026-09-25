// FUNCTION: GOLDTL 0x0050dd00
// SIZE: 228

#include <string.h>

void __cdecl fcn_00517c00(int id, int a, int b, char* out);

void __cdecl fcn_0050dd00(int n, int* arr, int flag)
{
	char b[0x80];
	char a[0x80];
	int i;
	int j;
	int t;

	if (flag) {
		return;
	}
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			fcn_00517c00(arr[i], 1, 1, a);
			fcn_00517c00(arr[j], 1, 1, b);
			if (strcmp(a, b) == 1) {
				t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
		}
	}
}
