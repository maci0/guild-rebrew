

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(int, int);

/* ADDRESS: GOLDDE 0x00592ed0 */
void __cdecl d2_RunIdleBuildingInterior0x4d(void)
{
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((int) d2_RunIdleBuildingInterior0x4d, 0x67fff) != 0) {
	}
}
