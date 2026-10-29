extern char* g_1015ea0;

/* ADDRESS: GOLDTL 0x00472900 */
void __cdecl fcn_00472900(int i, int v)
{
	char* e;

	e = g_1015ea0 + i * 0x2f4;
	*(int*) (e + 0x84) = v;
	switch (*(int*) (e + 0x20)) {
	case 0x40:
		*(int*) (0x10161cc + *(int*) (e + 0x88) * 0x3cc) = v;
		break;
	case 0x41:
		*(int*) (0x102d278 + *(int*) (e + 0x88) * 0x160) = v;
		break;
	}
}
