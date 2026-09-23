// FUNCTION: GOLD 0x00538010
// SIZE: 34
// fcn_00538010 — for table: if(*p) fcn_00426ba0(*p).

int __cdecl fcn_00426ba0(int);

void __cdecl fcn_00538010(void)
{
	int p;
	for (p = 0x75df20; p < 0x75e120; p += 4) {
		if (*(int*) p != 0) {
			fcn_00426ba0(*(int*) p);
		}
	}
}
