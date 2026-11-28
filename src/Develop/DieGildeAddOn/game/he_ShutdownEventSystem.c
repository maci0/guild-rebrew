


void __cdecl he_FreeAllActions(void);
int __cdecl fcn_0055bc30(void);
int __cdecl fcn_005710f0(void);
int __cdecl fcn_005758e0(void);

/* ADDRESS: GOLDDE 0x0052bc00 */
int __cdecl he_ShutdownEventSystem(void)
{
	he_FreeAllActions();
	if (fcn_0055bc30() != 0) {
		return 1;
	}
	if (fcn_005710f0() != 0) {
		return 1;
	}
	return fcn_005758e0() != 0;
}
