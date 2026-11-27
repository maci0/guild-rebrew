

typedef void (__stdcall* fcn_0046b4f0_m)(void*, int, int, int, int, float, int);

void __cdecl d2_ClearBackdropResource(void);

void __cdecl d2_ClearScreen(void)
{
	void* obj;

	obj = *(void**) 0x6b5de0;
	((fcn_0046b4f0_m) ((int*) *(int*) obj)[0x90 / 4])(obj, 0, 0, 1, 0, 1.0f, 0);
	if (*(int*) 0x7725a8 != 0) {
		d2_ClearBackdropResource();
	}
}
