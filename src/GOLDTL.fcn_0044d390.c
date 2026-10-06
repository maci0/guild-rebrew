// GLOBAL: GOLDTL 0x662d18
extern char g_662d18[];
// GLOBAL: GOLD 0x5ebb58
extern char g_662d18[];
// GLOBAL: GOLDTL 0x67b608
extern char g_67b608[];
// GLOBAL: GOLD 0x5fc698
extern char g_67b608[];

char* __cdecl fcn_0064f026(char* s, const char* delim);
int __cdecl fcn_0064eeec(const char* s);
void* __cdecl fcn_0041db70(int size, char* tag);

// FUNCTION: GOLD 0x0044eb20
// FUNCTION: GOLDTL 0x44d390
void __cdecl fcn_0044d390(int unused, char* s)
{
	int n;

	n = fcn_0064eeec(fcn_0064f026(0, g_662d18));
	*(int*) (s + 0xc) = n;
	*(int*) (s + 8) = 0;
	if (n > 0) {
		*(void**) (s + 0x10) = fcn_0041db70(n * 0xe0, g_67b608);
	}
}
