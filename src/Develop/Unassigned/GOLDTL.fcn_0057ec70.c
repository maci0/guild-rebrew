


extern int g_774a14;
extern int* g_665f08;
extern int g_6b7fc0;

int __cdecl fcn_0057ec70(int mask)
{
	char* p;

	if (g_774a14 == 0) {
		return 1;
	}
	p = ((char*)g_665f08);
	if (*(int*) (p + 0x3c) == 2 || *(int*) p == 5) {
		return 0;
	}
	p = *(char**) (p + 0x18);
	if (p == 0) {
		return 1;
	}
	if (g_6b7fc0 != 0) {
		return 0;
	}
	return (*(int*) (p + 0x6c) & mask) != 0;
}
