char* __cdecl fcn_0064f026(char* s, const char* delim);
int __cdecl fcn_0064eeec(const char* s);
void* __cdecl fcn_0041db70(int size, char* tag);

// FUNCTION: GOLDTL 0x44d5f0
// SIZE: 77
void __cdecl fcn_0044d5f0(int unused, char* s)
{
	int n;

	n = fcn_0064eeec(fcn_0064f026(0, (const char*) 0x662d18));
	*(int*) (s + 0x14) = n;
	if (n > 0 && *(void**) (s + 0x20) == 0) {
		*(int*) (s + 0x18) = 0;
		*(int*) (s + 0x1c) = 0;
		*(void**) (s + 0x20) = fcn_0041db70(0xe0000, (char*) 0x67b63c);
	}
}
