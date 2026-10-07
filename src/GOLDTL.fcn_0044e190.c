int __cdecl vfs_ReadData(void*, int, int, void*);
int __cdecl fcn_0044d770(void* h);
void __cdecl fcn_004011f0(void* a, void* b);
void __cdecl fcn_0044d7e0(void* h, char* tab, int n, int a);

// FUNCTION: GOLDTL 0x44e190
void __cdecl fcn_0044e190(int magic, int a2)
{
	void* h;
	int v;

	h = (void*) magic;
	vfs_ReadData(&magic, 4, 1, h);
	if (fcn_0044d770(h) == 0x2e) {
		fcn_004011f0(h, &v);
		fcn_0044d7e0(h, (char*) 0x67b800, 7, a2);
	}
}
