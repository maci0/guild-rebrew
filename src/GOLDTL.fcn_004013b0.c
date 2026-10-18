

int __cdecl fcn_004011f0(void* stream, void* dst);
void* __cdecl m_alloc(int, void*);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);

int __cdecl fcn_004013b0(void* volatile a1, int* a2, void* a3)
{
	void* p;
	void* stream;

	stream = a1;
	fcn_004011f0(stream, (int*) &a1);
	p = m_alloc((int) a1, a3);
	*a2 = (int) p;
	vfs_ReadData(p, (int) a1, 1, stream);
	return (int) a1;
}
