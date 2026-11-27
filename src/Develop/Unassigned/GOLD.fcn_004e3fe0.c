
// fcn_004e3fe0 — fcn_0042ea10(0x5315f0, 1); for table: if(n && !([n+0x8c]&4)) fcn_00404c20(n, 1).

int __cdecl tb_SetCallbackPaused(int, int);
int __cdecl fcn_00404c20(void*, int);

void __cdecl gm_PauseGameSimulation(void)
{
	int p;
	tb_SetCallbackPaused(0x5315f0, 1);
	for (p = 0x1468ae0; p < 0x14696e0; p += 4) {
		int n;
		n = *(int*) p;
		if (n != 0 && (*(char*) (n + 0x8c) & 4) == 0) {
			fcn_00404c20((void*) n, 1);
		}
	}
}
