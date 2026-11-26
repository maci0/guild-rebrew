

void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
int __cdecl fcn_004488e0(char* name, int a, int b);
void __cdecl d3_SetNodePosition(char* h, float* pos);
void __cdecl fcn_00455240(char* src, float* out);
void __cdecl d3_SetObjectRotation(char* h, float* v);

int __cdecl CreateObjectGroupAtDummy(char** name, char** a)
{
	float rot[3];
	float pos[4];
	int h;

	if (*a == 0) {
		return 0;
	}
	d3_TransformPoint(*a, *a + 0x4c, pos);
	h = fcn_004488e0(*name, 0, 0);
	d3_SetNodePosition((char*)h, pos);
	fcn_00455240(*a, rot);
	d3_SetObjectRotation((char*)h, rot);
	return h;
}
