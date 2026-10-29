int __cdecl fcn_004b4730(unsigned short*, int, int);
char* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);


/* ADDRESS: GOLDTL 0x004b4c10 */
int __cdecl fcn_004b4c10(unsigned short* e, int b, int c)
{
	int n;
	char* p;

	if (fcn_004b4730(e, b, c) == 0)
		return 0;
	n = 0;
	for (p = gm_StartFilteredEntitySearch(2, 4, *e, n, 7); p != 0; p = gm_FindNextFilteredEntity())
		n++;
	return n >= 3;
}
