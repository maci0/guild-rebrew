

void __cdecl sb_LoadSampleBank(int, int);

void __cdecl LoadSampleBank(int* p)
{
	sb_LoadSampleBank(*p, 1);
}
