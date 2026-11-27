

void __cdecl d2_ClearStatusTextSlots(void);
int __cdecl main_RunFrameLoop(int, int);

void __cdecl d2_RunIdleBuildingInterior0xbb(void)
{
	d2_ClearStatusTextSlots();
	while (main_RunFrameLoop(0x5ad360, 0x67fff) != 0) {
	}
}
