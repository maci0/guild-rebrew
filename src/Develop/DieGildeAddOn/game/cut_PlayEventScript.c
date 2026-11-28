extern int cut_SkipMode;

int __cdecl evt_LoadGfxScript(int);
void __cdecl fcn_00442830(void*);

/* ADDRESS: GOLDTL 0x004e4470 */
/* ADDRESS: GOLDDE 0x004d0e60 */
int __cdecl cut_PlayEventScript(int a)
{
	void* p;

	p = 0;
	if (cut_SkipMode == 0) {
		p = (void*) evt_LoadGfxScript(a);
		if (p != 0) {
			fcn_00442830(p);
			return *(int*) ((char*) p + 0x100);
		}
	}
	return 0;
}
