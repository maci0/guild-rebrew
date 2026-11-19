

#include "Develop/DieGildeAddOn/game/game_data.h"
extern char g_678fd0[];
void __cdecl fcn_00425810(void);
char* __cdecl m_alloc(int size, char* tag);
char* __cdecl fcn_0064d530(char* dst, const char* src, unsigned int n);

int __cdecl sbs_CreateSB(char* s)
{
	int n;

	fcn_00425810();
	if (sbs_BankManager == 0 && s != 0) {
		sbs_BankManager = m_alloc(0x40, g_678fd0);
		if (sbs_BankManager != 0) {
			n = 0x40;
			__asm {
				mov edi, sbs_BankManager
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
			fcn_0064d530(sbs_BankManager, s, 0x32);
			g_6b7d6c++;
			return 0;
		}
	}
	return -1;
}
