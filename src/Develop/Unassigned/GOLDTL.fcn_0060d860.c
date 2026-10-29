#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0060d860 */
void __fastcall fcn_0060d860(void* self, int d1, int a1, int a2, unsigned short a3)
{
	int* arr;
	int i;
	int v;
	if (a2 == -1) {
		return;
	}
	arr = *(int**) ((char*) self + 0xc4);
	i = a1;
	v = arr[i];
	while (v != a2) {
		if (v == a1) {
			goto out;
		}
		i = v;
		v = arr[i];
	}
	arr[i] = arr[v];
	arr[v] = v;
out:
	*(unsigned char*) (*(char**) ((char*) self + 0x138) + a2) = 1;
	(*(int*) (*(char**) ((char*) self + 0x128) + a3 * 0x14 + 0x10))--;
	(*(int*) ((char*) self + 0xe0))--;
}
