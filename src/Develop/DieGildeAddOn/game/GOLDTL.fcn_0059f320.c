

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(int, int);

void __cdecl d2_RunIdleBuildingInterior0xd6(void)
{
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(0x59f320, 0x67fff) != 0) {
	}
}
