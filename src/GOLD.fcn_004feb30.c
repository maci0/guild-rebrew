/* fcn_004feb30 — walk 0x7e3f40..0x7e4b10 (stride 0x2f4); stop on a zero byte. */

int __cdecl fcn_004ff550(int, int);

void __cdecl fcn_004feb30(void)
{
	int i;
	int p;

	i = 0;
	p = 0x7e3f40;
	do {
		if (*(char *)p == 0)
			break;
		fcn_004ff550(i, 0x770ae0);
		p += 0x2f4;
		i++;
	} while (p < 0x7e4b10);
}
