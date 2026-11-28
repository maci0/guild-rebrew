

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(int, int);

/* ADDRESS: GOLDDE 0x00591e70 */
void __cdecl d2_RunIdleBuildingInterior0xbb(void)
{
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop((int) d2_RunIdleBuildingInterior0xbb, 0x67fff) != 0) {
	}
}
