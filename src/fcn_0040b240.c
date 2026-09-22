// FUNCTION: GOLD 0x0040b240
// SIZE: 40
// fcn_0040b240 — clear node table 0x1468ae0..0x14696e0.

int __cdecl fcn_004028a0(int);

void __cdecl fcn_0040b240(void)
{
	int p;
	for (p = 0x1468ae0; p < 0x14696e0; p += 4) {
		if (*(int*) p != 0) {
			fcn_004028a0(*(int*) p);
			*(int*) p = 0;
		}
	}
}
