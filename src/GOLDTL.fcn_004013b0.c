// FUNCTION: GOLDTL 0x4013b0

void __cdecl fcn_004011f0(int, void*);
void* __cdecl fcn_0041db70(int, void*);
int __cdecl vfs_ReadData(void*, int, int, void*);

int __cdecl fcn_004013b0(int a1, int* a2, void* a3)
{
	void* p;

	fcn_004011f0(a1, &a1);
	p = fcn_0041db70(a1, a3);
	*a2 = (int) p;
	vfs_ReadData(p, a1, 1, (void*) a1);
	return a1;
}
