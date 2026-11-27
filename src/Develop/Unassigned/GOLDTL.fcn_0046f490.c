

void __cdecl d2_CloseWindow(int);

void __cdecl d2_CloseAllWindows(void)
{
	int i;
	int a;

	i = 0;
	for (a = 0x10161d0; a < 0x102ce50; a += 0x3cc, i++) {
		if (*(int*) a != 0) {
			d2_CloseWindow(i);
		}
	}
}
