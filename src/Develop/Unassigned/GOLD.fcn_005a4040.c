/* fcn_005a4040 — fcn_0052e1c0 once, then fcn_005309d0 until it returns 0. */

int __cdecl fcn_0052e1c0(void);
int __cdecl main_RunFrameLoop(void *, int);

void __cdecl fcn_005a4040(void)
{
	int r;

	fcn_0052e1c0();
	do {
		r = main_RunFrameLoop((void *)0x5a4040, 0x67fff);
	} while (r != 0);
}
