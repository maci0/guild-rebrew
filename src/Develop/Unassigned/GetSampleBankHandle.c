


int __cdecl sb_FindBankByName(int id);

/* ADDRESS: GOLDDE 0x0040fe60 */
int __cdecl GetSampleBankHandle(int* a)
{
	return sb_FindBankByName(*a);
}
