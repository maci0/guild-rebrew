

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(int, int);

/* ADDRESS: GOLDDE 0x005841a0 */
void __cdecl d2_RunIdleBuildingInterior0xd6(void)
{
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((int) d2_RunIdleBuildingInterior0xd6, 0x67fff) != 0) {
	}
}
