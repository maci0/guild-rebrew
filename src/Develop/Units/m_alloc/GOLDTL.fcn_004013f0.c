

int __cdecl fcn_004011f0(void* stream, void* dst);
void* __cdecl m_alloc(int, void*);
int __cdecl vfs_ReadData(char* buf, int size, int count, char* stream);

int __cdecl fcn_004013f0(void* a1, int* out)
{
	void* buf;
	void* stream;
	int size;

	stream = a1;
	fcn_004011f0(stream, &size);
	buf = m_alloc(size, (void*) 0x675040);
	*out = (int) buf;
	vfs_ReadData(buf, size, 1, stream);
	return size;
}
