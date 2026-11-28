extern int cut_CombatResolved;
extern int cut_CombatResolved;
extern int cut_PlunderedAmount;
extern int cut_PlunderedAmount;

/* ADDRESS: GOLD 0x004d6930 */
/* ADDRESS: GOLDTL 0x004d7d30 */
/* ADDRESS: GOLDDE 0x004c4c80 */
void __cdecl cut_ResolveSimpleCombat(char* p)
{
	if (cut_CombatResolved != 0) {
		*(int*) (p + 0x354) = 0;
		*(int*) (p + 0x358) = cut_PlunderedAmount;
		return;
	}
	*(int*) (p + 0x354) = 1;
}
