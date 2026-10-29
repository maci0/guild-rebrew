
// fcn_0058f700 — do r = fcn_005309d0(0x58f700, 0x67fff); while (r != 0).

int __cdecl fcn_005309d0(void*, int);

void __cdecl fcn_0058f700(void)
{
	int r;
	do {
		r = fcn_005309d0((void*) 0x58f700, 0x67fff);
	} while (r != 0);
}
