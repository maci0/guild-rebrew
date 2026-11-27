

extern char g_00f8f3a0[]; /* 0x00f8f3a0 */
extern char g_00f8f38c[]; /* 0x00f8f38c */

void __cdecl d2_DestroyGuiElement(int);

int __cdecl d2_CloseWindowGold(int index)
{
	char* entry;

	entry = g_00f8f3a0 + index * 0x3c4;
	if (*(int*) entry != 0) {
		d2_DestroyGuiElement(*(int*) (g_00f8f38c + index * 0x3c4));
		return 1;
	}
	return 0;
}
