
/* ADDRESS: GOLDTL 0x00423590 */
void __cdecl sb_SetVoiceCallback(int voice, int callback)
{
	if (*(int*) 0x6b7d7c != 0 && voice != 0) {
		*(int*) (voice + 0x2c) = callback;
	}
}
