
// fcn_004feb30 — for each non-zero byte in 0x7e3f40..0x7e4b10 (stride 0x2f4): fcn_004ff550(i, 0x770ae0).

int __cdecl fcn_004ff550(int, int);

void __cdecl fcn_004feb30(void)
{
	int i;
	int p;
	i = 0;
	for (p = 0x7e3f40; p < 0x7e4b10; p += 0x2f4) {
		if (*(char*) p != 0) {
			fcn_004ff550(i, 0x770ae0);
		}
		i++;
	}
}
