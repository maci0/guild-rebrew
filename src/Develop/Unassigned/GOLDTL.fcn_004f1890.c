

extern int g_6652f8[];

int __cdecl fcn_004f1890(int* needle, int* list)
{
	int n;
	int i;

	i = 0;
	n = g_6652f8[*list];
	for (; i < n; i++) {
		if (*(int*) (*(char**) (list + 4) + i * 0x44) == *needle) {
			return 1;
		}
	}
	return 0;
}
