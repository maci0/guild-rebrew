extern char lb_LocalClientId[];
char* __cdecl d3_LookupSceneEntry(int);

/* ADDRESS: GOLDTL 0x004ce1a0 */
/* ADDRESS: GOLDDE 0x004bb950 */
char* __cdecl d3_GetLocalSceneEntry(void)
{
	return d3_LookupSceneEntry(*(int*) &lb_LocalClientId);
}
