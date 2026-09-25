char* __cdecl fcn_0064f026(char* s, const char* delim);
int __cdecl fcn_0064eeec(const char* s);
void* __cdecl fcn_0041db70(int size, char* tag);

// FUNCTION: GOLDTL 0x44d5a0
// SIZE: 77
void __cdecl fcn_0044d5a0(int unused, char* s)
{
	int n;

	n = fcn_0064eeec(fcn_0064f026(0, (const char*) 0x662d18));
	*(int*) (s + 0x24) = n;
	if (n > 0 && *(void**) (s + 0x30) == 0) {
		*(int*) (s + 0x28) = 0;
		*(int*) (s + 0x2c) = 0;
		*(void**) (s + 0x30) = fcn_0041db70(0x60000, (char*) 0x67b624);
	}
}
