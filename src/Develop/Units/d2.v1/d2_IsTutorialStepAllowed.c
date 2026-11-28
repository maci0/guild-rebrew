
/* fcn_0057ecf0: return 0 if *a is 0x19, 0x1b or 0x29, otherwise 1. */

/* ADDRESS: GOLD 0x00576750 */
/* ADDRESS: GOLDTL 0x0057ecf0 */
/* ADDRESS: GOLDDE 0x00564ac0 */
int __cdecl d2_IsTutorialStepAllowed(int* step)
{
	if (*step == 0x19 || *step == 0x1b || *step == 0x29) {
		return 0;
	}
	return 1;
}

