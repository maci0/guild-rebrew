

typedef void (__stdcall* f)(void*, int, int, int);

/* ADDRESS: GOLDDE 0x004663a0 */
void __cdecl d3_AcquireBackBuffer(void)
{
	void* obj;

	obj = *(void**) 0x6b5de0;
	(*(f) ((int*) *(int*) obj)[0x40 / 4])(obj, 0, 0, *(int*) 0x77250c + 0x24);
}
