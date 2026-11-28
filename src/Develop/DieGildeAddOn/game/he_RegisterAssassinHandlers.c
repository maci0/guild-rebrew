


int __cdecl he_RegisterHandler(int, void (__cdecl*)(void), void (__cdecl*)(void));
void __cdecl he_StartAssassinAction(void);
void __cdecl he_RunAssassinAction(void);
void __cdecl he_StartAction0x9a(void);
void __cdecl fcn_00577720(void);
void __cdecl he_StartAction0x9b(void);
void __cdecl he_RunAction0x9b(void);

/* ADDRESS: GOLDDE 0x0055ca10 */
int __cdecl he_RegisterAssassinHandlers(void)
{
	if (he_RegisterHandler(0x99, he_StartAssassinAction, he_RunAssassinAction) || he_RegisterHandler(0x9a, he_StartAction0x9a, fcn_00577720) ||
	    he_RegisterHandler(0x9b, he_StartAction0x9b, he_RunAction0x9b)) {
		return 1;
	}
	return 0;
}
