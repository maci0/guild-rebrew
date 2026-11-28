// fcn_005768a0 — *a==0x1a && *(a+4) ? 1 : 0.

/* ADDRESS: GOLDTL 0x0057ee40 */
/* ADDRESS: GOLDDE 0x00564c10 */
int __cdecl d2_CheckTutorialStep0x1a(int* step)
{
	if (*step == 0x1a && *(step + 1) != 0) {
		return 1;
	}
	return 0;
}
