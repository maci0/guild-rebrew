int __cdecl sb_PrepareVoice(int a, int b);

/* ADDRESS: GOLDTL 0x00411070 */
int __cdecl GetSampleHandle(int* a, int* b)
{
	return sb_PrepareVoice(*a, *b);
}
