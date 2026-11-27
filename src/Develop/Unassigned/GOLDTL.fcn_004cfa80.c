

void __cdecl d2_CloseWindow(int);

void __cdecl d2_CloseAllEntityStatusPopups(void)
{
	int a;
	int v;

	for (a = 0x9ba2e0; a < 0x9ba360; a += 4) {
		v = *(int*) a;
		if (v != -1) {
			d2_CloseWindow(v);
			*(int*) a = -1;
		}
	}
}
