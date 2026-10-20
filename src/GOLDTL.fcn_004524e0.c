extern int g_104049c;
extern char* g_1040958;
extern int g_67a370;
extern int g_6b7fac;

int __cdecl fcn_0045c5b0(char* name, int flags, int a3, int a4);
void __cdecl fcn_0045ce90(int h);
void* __cdecl m_alloc(unsigned int size, const char* tag);
void __cdecl fcn_00439e70(char* o);

/* ADDRESS: GOLDTL 0x004524e0 */
char* __cdecl fcn_004524e0(unsigned int a0, char* a1, int a2, float a3, int a4, int a5)
{
	char* s;
	char* r;
	int v2;
	int i;

	if (!(a3 > 0.0)) {
		return 0;
	}
	if (!(a0 > 0)) {
		return 0;
	}
	v2 = fcn_0045c5b0(a1, a2, 0, 0);
	if (v2 == 0) {
		return 0;
	}
	fcn_0045ce90(v2);
	s = m_alloc(0x31c, (char*) 0x67bc8c);
	*(int*) (s + 0xdc) = v2;
	*(int*) (s + 0xd8) = a0;
	*(int*) (s + 0xe4) = a4;
	*(int*) (s + 0xe0) = (v2 - g_104049c) / 0x70;
	*(int*) (s + 0x310) = a5;
	*(char**) (s + 0x28) = m_alloc(a0 * 0x54, (char*) 0x67bc78);
	*(char**) (s + 0x2c) = m_alloc(a0 * 4, (char*) 0x67bc64);
	*(char**) (s + 0x30) = m_alloc(a0 * 4, (char*) 0x67bc50);
	*(int*) (s + 0) = 0;
	*(int*) (s + 4) = 0;
	*(int*) (s + 8) = 0;
	*(int*) (s + 0xc) = 0;
	*(int*) (s + 0x10) = 0;
	*(int*) (s + 0x14) = 0;
	*(int*) (s + 0x18) = 0;
	*(int*) (s + 0x1c) = 0;
	*(int*) (s + 0x20) = 0;
	*(int*) (s + 0x24) = 0;
	for (i = 0; i < *(int*) (s + 0xd8); i++) {
		r = *(char**) (s + 0x28) + i * 0x54;
		*(int*) (r + 0x38) = 0;
		*(int*) (r + 0x3c) = 0;
		*(int*) (r + 0x40) = 0;
		*(int*) (r + 0) = 0;
		*(int*) (r + 4) = 0;
		*(int*) (r + 8) = 0;
		*(int*) (r + 0x30) = g_6b7fac;
		*(int*) (r + 0x48) = *(int*) (s + 0xe4);
		*(unsigned char*) (r + 0x51) &= 0xfe;
		*(unsigned char*) (r + 0x50) = 0;
		*(int*) (r + 0x4c) = -1;
	}
	*(unsigned char*) (s + 0x2ff) |= 2;
	fcn_00439e70(s + 0xe8);
	*(int*) (s + 0x2e4) = a4;
	*(int*) (s + 0x2f4) = g_67a370;
	*(char**) (s + 0x318) = g_1040958;
	*(char**) (s + 0x314) = (char*) 0x1040640;
	*(char**) (g_1040958 + 0x314) = s;
	g_1040958 = s;
	return s;
}
