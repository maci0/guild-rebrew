#if defined(REBREW_GOLD)
extern char g_00f8f3a0[]; /* 0x00f8f3a0 */
extern char g_00f8f38c[]; /* 0x00f8f38c */

void __cdecl d2_DestroyGuiElement(int);

/* ADDRESS: GOLD 0x00472cd0 */
int __cdecl d2_CloseWindow(int index)
{
	char* entry;

	entry = g_00f8f3a0 + index * 0x3c4;
	if (*(int*) entry != 0) {
		d2_DestroyGuiElement(*(int*) (g_00f8f38c + index * 0x3c4));
		return 1;
	}
	return 0;
}
#else
extern char d2_WindowActiveView[];
extern char d2_WindowElementIdView[];


void __cdecl d2_DestroyElement(int);

/* ADDRESS: GOLDTL 0x0046f280 */
/* ADDRESS: GOLDDE 0x00462810 */
int __cdecl d2_CloseWindow(int index)
{
	char* p;

	p = d2_WindowActiveView + index * 0x3cc;
	if (*(int*) p != 0) {
		d2_DestroyElement(*(int*) (d2_WindowElementIdView + index * 0x3cc));
		return 1;
	}
	return 0;
}
#endif
