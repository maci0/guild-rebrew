char g_67b63c[22] = {
    0x64, 0x33, 0x5f, 0x69, 0x6f, 0x5f, 0x61, 0x3a, 0x41, 0x47, 0x49, 0x50, 0x6f, 0x6c, 0x79, 0x42,
    0x75, 0x66, 0x66, 0x65, 0x72, 0x00,
};
extern char g_67b63c[];

extern char g_662d18[];

char* __cdecl fcn_0064f026(char* s, const char* delim);
int __cdecl fcn_0064eeec(const char* s);
void* __cdecl m_alloc(int size, char* tag);

/* ADDRESS: GOLD 0x0044ed30 */
/* ADDRESS: GOLDTL 0x0044d5f0 */
void __cdecl fcn_0044d5f0(int unused, char* s)
{
	int n;

	n = fcn_0064eeec(fcn_0064f026(0, g_662d18));
	*(int*) (s + 0x14) = n;
	if (n > 0 && *(void**) (s + 0x20) == 0) {
		*(int*) (s + 0x18) = 0;
		*(int*) (s + 0x1c) = 0;
		*(void**) (s + 0x20) = m_alloc(0xe0000, g_67b63c);
	}
}
