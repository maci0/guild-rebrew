#include <string.h>

extern char* g_6b7d68;
extern int g_6b7d6c;

char* __cdecl fcn_00423ac0(char* s);
void* __cdecl fcn_004239b0(void);
char* __cdecl m_alloc(int size, char* tag);
char* __cdecl strncpy(char* dst, const char* src, unsigned int n);

/* ADDRESS: GOLDTL 0x00423e10 */
int __cdecl fcn_00423e10(char* s)
{
	char* list;
	char* buf;
	char* fp;
	int fn;

	if (g_6b7d68 == 0) {
		return -1;
	}
	if (fcn_00423ac0(s) != 0) {
		return -1;
	}
	list = (char*) fcn_004239b0();
	buf = m_alloc(0x40, (char*) 0x678fe0);
	if (list != 0) {
		*(char**) (list + 0x3c) = buf;
		if (buf == 0) {
			return -1;
		}
		{
			int n;
			char* p;

			n = 0x40;
			p = buf;
			__asm {
				mov edi, p
				mov ebx, n
				xor eax, eax
				lea ecx, [edi+edi*2]
				and ecx, 3
				sub ebx, ecx
				jle short L34
				rep stosb
				mov ecx, ebx
				and ebx, 3
				shr ecx, 2
				rep stosd
			L34:
				add ecx, ebx
				rep stosb
			}
		}
		strncpy(buf, s, 0x32);
		g_6b7d6c++;
		return 0;
	}
	if (buf == 0) {
		return -1;
	}
	fn = 0x40;
	fp = buf;
	__asm {
		mov edi, fp
		mov ebx, fn
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L44
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L44:
		add ecx, ebx
		rep stosb
	}
	strncpy(buf, s, 0x32);
	*(char**) (g_6b7d68 + 0x3c) = buf;
	g_6b7d6c++;
	return 0;
}
