

extern char g_00f8f3a0[]; /* 0x00f8f3a0 */
extern char g_00f8f38c[]; /* 0x00f8f38c */

void __cdecl fcn_0046e700(int);

int __cdecl fcn_00472cd0(int index)
{
	char* entry;

	entry = g_00f8f3a0 + index * 0x3c4;
	if (*(int*) entry != 0) {
		fcn_0046e700(*(int*) (g_00f8f38c + index * 0x3c4));
		return 1;
	}
	return 0;
}
