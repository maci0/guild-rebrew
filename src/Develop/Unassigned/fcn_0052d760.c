extern char* g_6b8014;

/* ADDRESS: GOLDTL 0x0052d760 */
void __cdecl fcn_0052d760(char* out)
{
	if (g_6b8014 == 0) {
		return;
	}
	*(int*) (out + 0x00) = *(int*) (g_6b8014 + 0x4c);
	*(int*) (out + 0x04) = *(int*) (g_6b8014 + 0x50);
	*(int*) (out + 0x08) = *(int*) (g_6b8014 + 0x54);
	*(int*) (out + 0x10) = *(int*) (g_6b8014 + 0x84);
	*(int*) (out + 0x14) = *(int*) (g_6b8014 + 0x88);
	*(int*) (out + 0x18) = *(int*) (g_6b8014 + 0x8c);
}
