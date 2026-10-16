/* fcn_005a50a0 — fcn_0052e1c0 once, then fcn_005309d0 until it returns 0. */

int __cdecl fcn_0052e1c0(void);
int __cdecl fcn_005309d0(void *, int);

void __cdecl fcn_005a50a0(void)
{
	int r;

	fcn_0052e1c0();
	do {
		r = fcn_005309d0((void *)0x5a50a0, 0x67fff);
	} while (r != 0);
}
