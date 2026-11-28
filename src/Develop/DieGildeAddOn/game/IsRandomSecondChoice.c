

int __cdecl gm_RandomMod(int);

/* Inferred name; the native caller passes an unused event pointer. */
/* ADDRESS: GOLDDE 0x00482620 */
int __cdecl IsRandomSecondChoice(int* unused_event)
{
	return (short) gm_RandomMod(2) != 0;
}
