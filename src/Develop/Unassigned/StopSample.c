

int __cdecl sb_StopVoice(int, int);

/* ADDRESS: GOLDDE 0x0040fe40 */
int __cdecl StopSample(int* p)
{
	sb_StopVoice(*p, 0);
	return 0;
}
