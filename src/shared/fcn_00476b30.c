// FUNCTION: GOLD 0x00476b30
// SIZE: 40
// fcn_00476b30 — clear node table 0xf8f0a0..0xf8f120.

int __cdecl fcn_00476850(int);

void __cdecl fcn_00476b30(void)
{
	int p;
	for (p = 0xf8f0a0; p < 0xf8f120; p += 4) {
		if (*(int*) p != 0) {
			fcn_00476850(*(int*) p);
			*(int*) p = 0;
		}
	}
}
