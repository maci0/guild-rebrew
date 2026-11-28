extern char g_68b7a0[];
int __cdecl d2_FreeWindowSlot(int);
void __cdecl d2_DestroyForm(int);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x004cefe0 */
void __cdecl d2_DestroyHudForm(void)
{
	int h;
	h = *(int*) 0x60cb40;
	if (h != -1) {
		d2_FreeWindowSlot(h);
		*(int*) 0x60cb40 = 0xffffffff;
	}
}
#else
/* ADDRESS: GOLDTL 0x004d0050 */
/* ADDRESS: GOLDDE 0x004bd340 */
void __cdecl d2_DestroyHudForm(void)
{
	if (*(int*) &g_68b7a0 != -1) {
		d2_DestroyForm(*(int*) &g_68b7a0);
		*(int*) &g_68b7a0 = -1;
	}
}
#endif
