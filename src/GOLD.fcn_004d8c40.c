// FUNCTION: GOLD 0x004d8c40
// fcn_004d8c40 — for table: if(*p) fcn_004e3250(*p).

int __cdecl fcn_004e3250(int);

void __cdecl fcn_004d8c40(void)
{
	int p;
	for (p = 0x92ca80; p < 0x92cac0; p += 4) {
		if (*(int*) p != 0) {
			fcn_004e3250(*(int*) p);
		}
	}
}
