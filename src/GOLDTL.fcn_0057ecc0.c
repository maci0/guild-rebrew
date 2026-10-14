


extern int* g_665f08;
extern int g_774a14;

int __cdecl fcn_0057ecc0(void)
{
	int* p;

	if (*(int*) ((char*)&g_774a14) == 0) {
		return 1;
	}
	p = g_665f08;
	if (*(int*) ((char*) p + 0x3c) == 2 || *p == 5) {
		return 0;
	}
	return 1;
}
