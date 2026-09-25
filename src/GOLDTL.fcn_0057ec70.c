// FUNCTION: GOLD 0x005766d0
// SIZE: 73
// FUNCTION: GOLDTL 0x0057ec70
// SIZE: 73

extern int g_774a14;
extern char* g_665f08;
extern int g_6b7fc0;

int __cdecl fcn_0057ec70(int mask)
{
	char* p;

	if (g_774a14 == 0) {
		return 1;
	}
	p = g_665f08;
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
