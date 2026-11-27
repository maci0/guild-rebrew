extern float g_662d40[3];



void __cdecl d3_TransformDirection(int, void*, void*);

void __cdecl d3_UpdateCannonAimMatrices(char* obj)
{
	d3_TransformDirection(*(int*) (obj + 0x8c), (void*) g_662d40, obj + 0x24);
	d3_TransformDirection(*(int*) (obj + 0x8c), (void*) (g_662d40 + 8), obj + 0x44);
	d3_TransformDirection(*(int*) (obj + 0x8c), (void*) (g_662d40 + 4), obj + 0x34);
}
