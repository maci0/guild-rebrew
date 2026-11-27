

int __cdecl fcn_004011f0(void* stream, void* dst);
void* __cdecl m_alloc(int, void*);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);

int __cdecl bio_rd_buffer(void* a1, int* outBuffer, void* a3)
{
	void* p;
	void* stream;
	int size;

	stream = a1;
	fcn_004011f0(stream, &size);
	p = m_alloc(size, a3);
	*outBuffer = (int) p;
	vfs_ReadData(p, size, 1, stream);
	return size;
}
