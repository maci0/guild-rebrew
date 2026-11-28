extern int d3_ActiveScene;

void __cdecl d3_InvalidateSubTreeFlags(char* p, int a);
void __cdecl d3_TraverseSceneObjects(int list, char* p, int mask, void(__cdecl* fn)(void));
void __cdecl d3_ClearAuxSlotState(void);

/* ADDRESS: GOLDTL 0x00438bd0 */
void __cdecl d3_SetNodeScale(char* p, int* v)
{
	d3_InvalidateSubTreeFlags(p, 1);
	d3_TraverseSceneObjects(d3_ActiveScene, p, 0xc0, d3_ClearAuxSlotState);
	*(int*) (p + 0x6c) = v[0];
	*(int*) (p + 0x70) = v[1];
	*(int*) (p + 0x74) = v[2];
}
