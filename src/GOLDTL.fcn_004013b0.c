// FUNCTION: GOLDTL 0x4013b0

void __cdecl fcn_004011f0(int, void*);
void* __cdecl m_AllocTracked(int, void*);
int __cdecl vfs_ReadData(void*, int, int, void*);

int __cdecl fcn_004013b0(volatile int a1, int* a2, void* a3)
{
	void* p;
	int stream;

	stream = a1;
	fcn_004011f0(stream, (int*) &a1);
	p = m_AllocTracked(a1, a3);
	*a2 = (int) p;
	vfs_ReadData(p, a1, 1, (void*) stream);
	return a1;
}
