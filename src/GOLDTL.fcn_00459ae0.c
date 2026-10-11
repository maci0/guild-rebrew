extern int g_6b7fac;

void* __cdecl m_AllocTracked(int size, char* tag);
void __cdecl fcn_00459a10(char* p);
void __cdecl fcn_00459710(char* p, int a);

// FUNCTION: GOLDTL 0x459ae0
char* __cdecl fcn_00459ae0(int a, int b, int c)
{
	char* p;

	p = (char*) m_AllocTracked(0x390, (char*) 0x67bcd8);
	if (p != 0) {
		*(int*) (p + 8) = -1;
		*(int*) (p + 0x24) = 0;
		*(int*) (p + 0x18) = a;
		*(int*) (p + 0x28) = g_6b7fac;
		*(int*) (p + 0x2c) = 0;
		*(int*) (p + 0x1c) = b;
		*(int*) (p + 0x20) = c;
		fcn_00459a10(p);
		fcn_00459710(p, 1);
	}
	return p;
}
