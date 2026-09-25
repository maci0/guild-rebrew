// FUNCTION: GOLD 0x00472cd0
// SIZE: 52

extern char g_00f8f3a0[]; /* 0x00f8f3a0 */
extern char g_00f8f38c[]; /* 0x00f8f38c */

void __cdecl fcn_0046e700(int);

int __cdecl fcn_00472cd0(int a1)
{
	char* p;

	p = g_00f8f3a0 + a1 * 0x3c4;
	if (*(int*) p != 0) {
		fcn_0046e700(*(int*) (g_00f8f38c + a1 * 0x3c4));
		return 1;
	}
	return 0;
}
