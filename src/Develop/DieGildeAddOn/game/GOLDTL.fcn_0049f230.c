int __cdecl amt_ExecGebaeudeBauen(char*, char*, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl cm_RequestSetEntityLevel(int, int);
void __cdecl gm_ModifyHealth(int, int);


/* ADDRESS: GOLDTL 0x0049f230 */
int __cdecl ai_RunChangeProfession(char* a, char* b, int c)
{
	if (amt_ExecGebaeudeBauen(a, b, c) != 0) {
		cm_RequestChangeBits(*(int*) (a + 4), 0x1c8, 4, 0x1000000, 0);
		cm_RequestSetEntityLevel(*(int*) (a + 4), *(int*) (b + 0x10));
		gm_ModifyHealth(*(int*) (a + 4), 8);
		return 0x34;
	}
	return 0;
}
