extern char* g_6b7fd8;
extern char* g_6b7fd0;
extern char* g_6b7fd4;
extern char g_679e54[];
extern char* g_679e2c;
extern char* g_679e30;
char* __cdecl m_AllocTracked(int size, char* tag);
char* __cdecl fcn_0064d530(char* dst, const char* src, unsigned int n);

// FUNCTION: GOLD 0x42ea90
// FUNCTION: GOLDTL 0x0042dfb0

int __cdecl fcn_0042dfb0(unsigned short count)
{
	char tmpl[0x84];
	int len;
	char* d;
	char* p;
	char* s;
	int len2;

	if (count == 0) {
		return -1;
	}
	if (g_6b7fd8 != 0) {
		return -2;
	}
	g_6b7fd8 = m_AllocTracked(count * 0x84, g_679e54);
	if (g_6b7fd8 == 0) {
		return -3;
	}
	g_6b7fd0 = g_6b7fd8;
	g_6b7fd4 = g_6b7fd8 + count * 0x84;
	len = 0x84;
	d = tmpl;
	__asm {
		mov edi, d
		mov ebx, len
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	fcn_0064d530(tmpl, g_679e2c, 0xd);
	fcn_0064d530(tmpl + 0x74, g_679e30, 0xd);
	for (p = g_6b7fd0; p < g_6b7fd4; p += 0x84) {
		len2 = 0x84;
		s = tmpl;
		__asm {
			mov edi, p
			mov esi, s
			mov ebx, len2
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L2
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L2:
			add ecx, ebx
			rep movsb
		}
	}
	return 0;
}
