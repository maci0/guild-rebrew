/* fcn_005a50a0 — fcn_0052e1c0 once, then fcn_005309d0 until it returns 0. */

int __cdecl d2_ClearInteractionSlots(void);
int __cdecl main_RunFrameLoop(void *, int);

void __cdecl d2_UpdateBuildingInteriorLoop(void)
{
	int r;

	d2_ClearInteractionSlots();
	do {
		r = main_RunFrameLoop((void *)0x5a50a0, 0x67fff);
	} while (r != 0);
}
