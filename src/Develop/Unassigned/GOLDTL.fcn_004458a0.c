


void __cdecl fcn_00445760(int, int, int, void*, void*);
void __cdecl fcn_00438b40(char*, void*);
void __cdecl d3_SetObjectRotation(char*, void*);

void __cdecl fcn_004458a0(int object, int a2, int a3)
{
	char a[0xc];
	char b[0x10];

	fcn_00445760(object, a2, a3, b, a);
	fcn_00438b40((char*) object, b);
	d3_SetObjectRotation((char*) object, a);
}
