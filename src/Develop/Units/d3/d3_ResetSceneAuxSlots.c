

void __cdecl d3_TraverseSceneObjects(int, int, int, int);

void __cdecl d3_ResetSceneAuxSlots(void)
{
	d3_TraverseSceneObjects(*(int*) 0x67a370, 0, 0xc0, 0x456b80);
}
