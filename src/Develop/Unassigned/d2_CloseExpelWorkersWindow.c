
// fcn_005da160 — fcn_004758e0([0x62dda0]); [0x62dda0] = -1.

int __cdecl d2_FreeWindowSlot(int);

void __cdecl d2_CloseExpelWorkersWindow(void)
{
	d2_FreeWindowSlot(*(int*) 0x62dda0);
	*(int*) 0x62dda0 = 0xffffffff;
}
