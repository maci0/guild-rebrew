


extern int* g_665f08;
extern int g_774a14;

int __cdecl fcn_005809a0(int a1)
{
	int* p;

	if (*(int*) ((char*)&g_774a14) == 0) {
		return -4;
	}
	p = g_665f08;
	*(int*) ((char*) p + 0x1c) = a1;
	*(int*) ((char*) g_665f08 + 0x20) = -1;
	return 0;
}
