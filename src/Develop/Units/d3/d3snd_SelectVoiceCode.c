
/* ADDRESS: GOLDTL 0x004c2db0 */
/* ADDRESS: GOLDDE 0x004b0860 */
int __cdecl d3snd_SelectVoiceCode(unsigned value, int mode)
{
	if (mode == 1) {
		return (value & 1) - 2;
	}
	return (int) (value % 3) - 5;
}
