extern char g_6b5de0[];
extern char g_7725a8[];


typedef void (__stdcall* fcn_0046b4f0_m)(void*, int, int, int, int, float, int);

void __cdecl d2_ClearBackdropResource(void);

/* ADDRESS: GOLDDE 0x0045eb70 */
void __cdecl d2_ClearScreen(void)
{
	void* obj;

	obj = *(void**) &g_6b5de0;
	((fcn_0046b4f0_m) ((int*) *(int*) obj)[0x90 / 4])(obj, 0, 0, 1, 0, 1.0f, 0);
	if (*(int*) &g_7725a8 != 0) {
		d2_ClearBackdropResource();
	}
}
