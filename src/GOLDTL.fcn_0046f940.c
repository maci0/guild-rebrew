extern char* g_1015ea0;

int __cdecl fcn_0046b520(const char* s, int a);

// FUNCTION: GOLDTL 0x46f940
void __cdecl fcn_0046f940(int i, const char* s)
{
	const char* p;
	char* d;
	char c;

	p = s;
	d = *(char**) (g_1015ea0 + i * 0x2f4 + 0x88);
	do {
		c = *p++;
		*d++ = c;
	} while (c != 0);
	if (*(int*) (g_1015ea0 + i * 0x2f4 + 0x6c) == 0 && *(int*) (g_1015ea0 + i * 0x2f4 + 0x70) == 0) {
		*(int*) (g_1015ea0 + i * 0x2f4 + 0x18) = fcn_0046b520(s, *(int*) (g_1015ea0 + i * 0x2f4 + 0x84));
	}
}
