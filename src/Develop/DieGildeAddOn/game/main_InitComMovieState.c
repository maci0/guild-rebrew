__declspec(dllimport) long __stdcall CoInitialize(void*);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00422d60 */
int __cdecl main_InitComMovieState(void)
{
    CoInitialize(0);
    *(int*) 0x14613fc = 0x29a;
    *(short*) 0x14613f8 = 0;
    return 1;
}
#else
/* ADDRESS: GOLDTL 0x0041e620 */
/* ADDRESS: GOLDDE 0x0041c050 */
int __cdecl main_InitComMovieState(void)
{
	((void* (__stdcall*)(int)) *(void**) 0x662470)(0);
	*(int*) 0x14cc5bc = 0x29a;
	*(short*) 0x14cc5b8 = 0;
	return 1;
}
#endif
