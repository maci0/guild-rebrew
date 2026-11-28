

void __cdecl gm_ModifyHealth(int, int);

/* ADDRESS: GOLDDE 0x005bd770 */
int __cdecl gm_ObjGrant2ActionPoints(char* p)
{
	gm_ModifyHealth(*(int*) (p + 4), 2);
	return 1;
}
