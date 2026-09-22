// FUNCTION: GOLD 0x00476b00
// SIZE: 41
// fcn_00476b00 — for table: if(*p) fcn_00476890(*p, [0x6ed924]).

int __cdecl fcn_00476890(int, int);

void __cdecl fcn_00476b00(void)
{
	int p;
	for (p = 0xf8f0a0; p < 0xf8f120; p += 4) {
		if (*(int*) p != 0) {
			fcn_00476890(*(int*) p, *(int*) 0x6ed924);
		}
	}
}
