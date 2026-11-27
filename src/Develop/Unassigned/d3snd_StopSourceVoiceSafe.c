void __cdecl d3snd_StopSourceVoice(char* p);

/* ADDRESS: GOLD 0x004179d0 */
/* ADDRESS: GOLDTL 0x00418f90 */
void __cdecl d3snd_StopSourceVoiceSafe(char* p)
{
	if (p != 0)
		d3snd_StopSourceVoice(p);
}
