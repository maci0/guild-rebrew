


void __cdecl d3_TransformWorldToParent(int, int, int, void*, void*);
void __cdecl d3_SetNodePosition(char*, void*);
void __cdecl d3_SetObjectRotation(char*, void*);

/* ADDRESS: GOLDDE 0x0043d630 */
void __cdecl d3_ApplyWorldTransformToObject(int object, int pos, int rotMatrix)
{
	char a[0xc];
	char b[0x10];

	d3_TransformWorldToParent(object, pos, rotMatrix, b, a);
	d3_SetNodePosition((char*) object, b);
	d3_SetObjectRotation((char*) object, a);
}
