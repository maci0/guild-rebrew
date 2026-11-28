
// fcn_0040ffe0 — fcn_00426ba0(*arg).

int __cdecl sb_UnloadSampleBank(int);

int __cdecl ecmd_KillSampleBank(int* a)
{
	sb_UnloadSampleBank(*a);
	return 0;
}
