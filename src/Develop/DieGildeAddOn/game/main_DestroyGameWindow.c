int (__stdcall* f1_5eb25c)(int);
int (__stdcall* f2_5eb218)(int, int);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x005316a0 */
void __cdecl main_DestroyGameWindow(void)
{
	((int (__stdcall*)(int)) *(void**) 0x5eb25c)(*(int*) 0x6f2588);
	((int (__stdcall*)(int, int)) *(void**) 0x5eb218)(0x624944, *(int*) 0x75e140);
}
#else
/* ADDRESS: GOLDTL 0x00538140 */
/* ADDRESS: GOLDDE 0x0051fa10 */
void __cdecl main_DestroyGameWindow(void)
{
	((int (__stdcall*)(int)) *(void**) 0x6622cc)(*(int*) 0x774940);
	((int (__stdcall*)(int, int)) *(void**) 0x662280)(0x6a37fc, *(int*) 0x7e1f80);
}
#endif
