

int __cdecl sb_ReleaseSampleBank(int);

int __cdecl KillSampleBank(int* p)
{
	sb_ReleaseSampleBank(*p);
	return 0;
}
