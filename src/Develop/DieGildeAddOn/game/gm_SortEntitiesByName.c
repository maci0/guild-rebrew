


#include <string.h>

void __cdecl gm_FormatEntityTitleAndName(int id, int a, int b, char* out);

void __cdecl gm_SortEntitiesByName(int n, int* arr, int flag)
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
			gm_FormatEntityTitleAndName(arr[i], 1, 1, a);
			gm_FormatEntityTitleAndName(arr[j], 1, 1, b);
			if (strcmp(a, b) == 1) {
				t = arr[i];
				arr[i] = arr[j];
				arr[j] = t;
			}
		}
	}
}
