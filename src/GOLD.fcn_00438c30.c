/* ADDRESS: GOLD 0x00438c30 */
// fcn_00438c30 — if([a+0x1f8]==0 && [a+0x1f0]) walk [n+0x210]&1 == 0.

void __cdecl fcn_00438c30(char* a)
{
	char* n;
	if (*(int*) (a + 0x1f8) != 0) {
		return;
	}
	n = *(char**) (a + 0x1f0);
	while (n != 0 && (*(char*) (n + 0x210) & 1) == 0) {
		n = *(char**) (n + 0x1f0);
	}
}
