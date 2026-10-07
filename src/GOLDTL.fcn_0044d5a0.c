// GLOBAL: GOLDTL 0x67b624
extern char g_67b624[];
// GLOBAL: GOLD 0x5fc6b4
extern char g_67b624[];

extern char g_662d18[];

char* __cdecl fcn_0064f026(char* s, const char* delim);
int __cdecl fcn_0064eeec(const char* s);
void* __cdecl fcn_0041db70(int size, char* tag);

// FUNCTION: GOLD 0x0044ece0
// FUNCTION: GOLDTL 0x44d5a0
void __cdecl fcn_0044d5a0(int unused, char* s)
{
	int n;

	n = fcn_0064eeec(fcn_0064f026(0, g_662d18));
	*(int*) (s + 0x24) = n;
	if (n > 0 && *(void**) (s + 0x30) == 0) {
		*(int*) (s + 0x28) = 0;
		*(int*) (s + 0x2c) = 0;
		*(void**) (s + 0x30) = fcn_0041db70(0x60000, g_67b624);
	}
}
