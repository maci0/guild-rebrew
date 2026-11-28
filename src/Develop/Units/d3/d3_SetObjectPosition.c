


extern int d3_ActiveScene;

void __cdecl d3_InvalidateSubTreeFlags(char*, int);
void __cdecl d3_TraverseSceneObjects(int, char*, int, void*);
void __cdecl d3_ClearAuxSlotState(void);

void __cdecl d3_SetObjectPosition(char* o, int* v)
{
	d3_InvalidateSubTreeFlags(o, 1);
	d3_TraverseSceneObjects(d3_ActiveScene, o, 0xc0, d3_ClearAuxSlotState);
	*(int*) (o + 0x78) = v[0];
	*(int*) (o + 0x7c) = v[1];
	*(int*) (o + 0x80) = v[2];
}
