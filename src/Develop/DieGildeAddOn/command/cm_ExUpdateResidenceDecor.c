


char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_UpdateResidenceOwnerDecor(int);

/* ADDRESS: GOLDDE 0x004b9bb0 */
int __cdecl cm_ExUpdateResidenceDecor(char* x, char* out)
{
	char* e;

	e = gm_LookupEntityRecordById(*(int*) (x + 0x10));
	if (e != 0 && *(int*) (e + 0x170) != 0)
		gm_UpdateResidenceOwnerDecor(*(int*) (e + 0x170));
	if (out != 0) {
		out[0] = 1;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
