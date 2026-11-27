


int __cdecl sb_FindBankByName(int id);

int __cdecl GetSampleBankHandle(int* a)
{
	return sb_FindBankByName(*a);
}
