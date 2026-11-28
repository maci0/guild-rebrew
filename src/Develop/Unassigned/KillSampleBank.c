

int __cdecl sb_ReleaseSampleBank(int);

/* ADDRESS: GOLDDE 0x0040fcf0 */
int __cdecl KillSampleBank(int* p)
{
	sb_ReleaseSampleBank(*p);
	return 0;
}
