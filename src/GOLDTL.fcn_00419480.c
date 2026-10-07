// FUNCTION: GOLD 0x00417ec0
// FUNCTION: GOLDTL 0x00419480

#include <math.h>

extern unsigned short g_6b5d18;
extern float* g_6b5d0c;
extern char* g_6b5d10;
extern char* g_6b5d14;
extern char g_67779c[];
void* __cdecl fcn_0041db70(int size, char* tag);
void __cdecl fcn_0041ddd0(void* p);

int __cdecl fcn_00419480(unsigned short n)
{
	int cnt;
	int len;
	int len2;
	float a;
	float step;
	int size;
	unsigned short i;

	if (n > 4) {
		g_6b5d18 = n;
		cnt = n;
		size = n * 4;
		g_6b5d0c = (float*) fcn_0041db70(size, g_67779c);
		if (g_6b5d0c != 0) {
			g_6b5d10 = (char*) fcn_0041db70(size, g_67779c);
			if (g_6b5d10 != 0) {
				len = size;
				__asm {
					mov edi, g_6b5d10
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
				g_6b5d14 = (char*) fcn_0041db70(size, g_67779c);
				if (g_6b5d14 != 0) {
					a = 0;
					step = 6.2831855f / (float) cnt;
					len2 = size;
					__asm {
						mov edi, g_6b5d14
						mov ebx, len2
						xor eax, eax
						lea ecx, [edi+edi*2]
						and ecx, 3
						sub ebx, ecx
						jle short L2
						rep stosb
						mov ecx, ebx
						and ebx, 3
						shr ecx, 2
						rep stosd
					L2:
						add ecx, ebx
						rep stosb
					}
					for (i = 0; i < n; i++) {
						g_6b5d0c[i] = (float) sin(a);
						a += step;
					}
					return 1;
				}
				fcn_0041ddd0(g_6b5d10);
				g_6b5d10 = 0;
				fcn_0041ddd0(g_6b5d0c);
				g_6b5d10 = 0;
				g_6b5d0c = 0;
				return 0;
			}
			fcn_0041ddd0(g_6b5d0c);
			g_6b5d0c = 0;
		}
	}
	return 0;
}
