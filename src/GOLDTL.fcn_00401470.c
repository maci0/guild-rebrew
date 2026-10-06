// FUNCTION: GOLDTL 0x00401470

void __cdecl fcn_004011f0(int f, void* x);
void __cdecl fcn_00430a80(int f, int off, int whence);
void __cdecl fcn_0041d9e0(const char* msg);
void* __cdecl fcn_0041db70(int size, const char* tag);
void __cdecl fcn_004306b0(void* buf, int size, int count, int f);

int __cdecl fcn_00401470(int f, int count, void** out, const char* tag)
{
	int size;
	int n;

	fcn_004011f0(f, &size);
	fcn_004011f0(f, &n);
	if (n != count) {
		fcn_00430a80(f, n * size, 1);
		*out = 0;
		fcn_0041d9e0("array count mismatch");
		return 0;
	}
	*out = fcn_0041db70(size * count, tag);
	fcn_004306b0(*out, count, size, f);
	return size;
}
