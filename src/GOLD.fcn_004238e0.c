void __cdecl fcn_0042ad00(void);
void __cdecl fcn_0042b970(int);

/* ADDRESS: GOLD 0x004238e0 */
void __cdecl fcn_004238e0(void)
{
	if (*(int *)0x6325c4) {
		*(int *)0x6325c0 = 1;
		fcn_0042ad00();
		fcn_0042b970(*(int *)0x6325c4);
		*(int *)0x6325c4 = 0;
	} else {
		*(int *)0x6325c0 = 1;
	}
	if (*(int *)0x6325c8) {
		fcn_0042b970(*(int *)0x6325c8);
		*(int *)0x6325c8 = 0;
	}
}
