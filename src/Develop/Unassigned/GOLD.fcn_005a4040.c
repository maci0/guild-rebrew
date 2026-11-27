/* fcn_005a4040 — fcn_0052e1c0 once, then fcn_005309d0 until it returns 0. */

int __cdecl d2_ClearInteractionSlots(void);
int __cdecl main_RunFrameLoop(void *, int);

void __cdecl d2_UpdateBuildingInterior0x4d(void)
{
	int r;

	d2_ClearInteractionSlots();
	do {
		r = main_RunFrameLoop((void *)0x5a4040, 0x67fff);
	} while (r != 0);
}
