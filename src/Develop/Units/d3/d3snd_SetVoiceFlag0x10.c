
// fcn_00426170 — if(b) a[5] |= 0x10; else a[5] &= ~0x10.

/* ADDRESS: GOLDTL 0x004225e0 */
/* ADDRESS: GOLDDE 0x0041f460 */
void __cdecl d3snd_SetVoiceFlag0x10(int* a, int b)
{
	if (b != 0) {
		a[5] |= 0x10;
	} else {
		a[5] &= ~0x10;
	}
}

