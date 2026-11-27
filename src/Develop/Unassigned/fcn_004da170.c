extern int g_772f2c;
void __cdecl cut_ResolveSimpleCombat(void*);
void __cdecl fcn_004d9f20(void*);

/* ADDRESS: GOLDTL 0x004da170 */
void __cdecl fcn_004da170(void* p)
{
	if (g_772f2c == 0) {
		cut_ResolveSimpleCombat(p);
		return;
	}
	fcn_004d9f20(p);
}
