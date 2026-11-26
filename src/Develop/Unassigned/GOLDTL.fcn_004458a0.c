


void __cdecl fcn_00445760(int, int, int, void*, void*);
void __cdecl fcn_00438b40(char*, void*);
void __cdecl d3_SetObjectRotation(char*, void*);

void __cdecl d3_ApplyWorldTransformToObject(int object, int pos, int rotMatrix)
{
	char a[0xc];
	char b[0x10];

	fcn_00445760(object, pos, rotMatrix, b, a);
	fcn_00438b40((char*) object, b);
	d3_SetObjectRotation((char*) object, a);
}
