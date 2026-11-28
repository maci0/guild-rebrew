

void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
int __cdecl d3_LoadObjectFile(char* name, int a, int b);
void __cdecl d3_SetNodePosition(char* h, float* pos);
void __cdecl d3_GetObjectEulerRotation(char* src, float* out);
void __cdecl d3_SetObjectRotation(char* h, float* v);

/* ADDRESS: GOLDDE 0x0040d6b0 */
int __cdecl CreateObjectGroupAtDummy(char** name, char** a)
{
	float rot[3];
	float pos[4];
	int h;

	if (*a == 0) {
		return 0;
	}
	d3_TransformPoint(*a, *a + 0x4c, pos);
	h = d3_LoadObjectFile(*name, 0, 0);
	d3_SetNodePosition((char*)h, pos);
	d3_GetObjectEulerRotation(*a, rot);
	d3_SetObjectRotation((char*)h, rot);
	return h;
}
