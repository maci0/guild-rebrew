

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(int, int);

void __cdecl d2_RunIdleBuildingInterior0x4d(void)
{
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(0x5ae3c0, 0x67fff) != 0) {
	}
}
