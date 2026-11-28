

typedef void (__stdcall* D3_PRESENT_FN)(void*, int, int, int, int);

/* ADDRESS: GOLDDE 0x00419950 */
void __cdecl d3_PresentFrame(void)
{
	void* obj;

	obj = *(void**) 0x6b5de0;
	((D3_PRESENT_FN) ((int*) *(int*) obj)[0xf])(obj, 0, 0, *(int*) 0x14ce730, 0);
}
