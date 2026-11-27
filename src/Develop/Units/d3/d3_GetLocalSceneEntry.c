char* __cdecl d3_LookupSceneEntry(int);

/* ADDRESS: GOLDTL 0x004ce1a0 */
char* __cdecl d3_GetLocalSceneEntry(void)
{
	return d3_LookupSceneEntry(*(int*) 0x9badd0);
}
