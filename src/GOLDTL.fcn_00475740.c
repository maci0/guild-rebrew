extern char g_67d934[];

unsigned int __cdecl fcn_00475360(void*);
void* __cdecl fcn_0041db70(unsigned int, char*);
void __cdecl fcn_004754b0(void*, void*, int);

// FUNCTION: GOLDTL 0x475740

void* __cdecl fcn_00475740(void* src)
{
	unsigned int dim;
	void* p;

	dim = fcn_00475360(src);
	if (dim == 0)
		return 0;
	p = fcn_0041db70((dim >> 16) * (dim & 0xffff), g_67d934);
	fcn_004754b0(src, p, 1);
	return p;
}
