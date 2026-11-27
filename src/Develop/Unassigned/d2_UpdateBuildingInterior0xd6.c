/* fcn_00596140 — fcn_0052e1c0 once, then fcn_005309d0 until it returns 0. */

int __cdecl d2_ClearInteractionSlots(void);
int __cdecl main_RunFrameLoop(void *, int);

void __cdecl d2_UpdateBuildingInterior0xd6(void)
{
	int r;

	d2_ClearInteractionSlots();
	do {
		r = main_RunFrameLoop((void *)0x596140, 0x67fff);
	} while (r != 0);
}
