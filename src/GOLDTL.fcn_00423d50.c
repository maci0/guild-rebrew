

extern char* g_6b7d68;
extern int g_6b7d6c;
extern char g_678fd0[];
void __cdecl fcn_00425810(void);
char* __cdecl m_alloc(int size, char* tag);
char* __cdecl fcn_0064d530(char* dst, const char* src, unsigned int n);

int __cdecl fcn_00423d50(char* s)
{
	int n;

	fcn_00425810();
	if (g_6b7d68 == 0 && s != 0) {
		g_6b7d68 = m_alloc(0x40, g_678fd0);
		if (g_6b7d68 != 0) {
			n = 0x40;
			__asm {
				mov edi, g_6b7d68
				mov ebx, n
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
			fcn_0064d530(g_6b7d68, s, 0x32);
			g_6b7d6c++;
			return 0;
		}
	}
	return -1;
}
