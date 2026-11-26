


int __cdecl he_RegisterHandler(int, void*, void*);
void __cdecl he_StartAction0x9d(void);
void __cdecl he_RunAction0x9d(void);
void __cdecl he_InitEvent09e(void);
void __cdecl fcn_0057c7b0(void);
void __cdecl fcn_0057c860(void);
void __cdecl fcn_0057c8d0(void);
void __cdecl he_InitEvent0a0(void);
void __cdecl fcn_0057cbc0(void);
void __cdecl he_InitEvent0a1(void);
void __cdecl fcn_0057d0d0(void);
void __cdecl he_InitEvent0a3(void);
void __cdecl fcn_0057d9e0(void);
void __cdecl he_InitEvent0a4(void);
void __cdecl he_UpdateEvent0a4(void);
int __cdecl fcn_00530ab0(int, char*, int, int, int);

int __cdecl fcn_0057bbc0(void)
{
	if (he_RegisterHandler(0x9d, (void*) he_StartAction0x9d, (void*) he_RunAction0x9d) != 0 ||
	    he_RegisterHandler(0x9e, (void*) he_InitEvent09e, (void*) fcn_0057c7b0) != 0 ||
	    he_RegisterHandler(0x9f, (void*) fcn_0057c860, (void*) fcn_0057c8d0) != 0 ||
	    he_RegisterHandler(0xa0, (void*) he_InitEvent0a0, (void*) fcn_0057cbc0) != 0 ||
	    he_RegisterHandler(0xa1, (void*) he_InitEvent0a1, (void*) fcn_0057d0d0) != 0 ||
	    he_RegisterHandler(0xa3, (void*) he_InitEvent0a3, (void*) fcn_0057d9e0) != 0 ||
	    he_RegisterHandler(0xa4, (void*) he_InitEvent0a4, (void*) he_UpdateEvent0a4) != 0) {
		return 1;
	}
	fcn_00530ab0(0xa1, 0, 0, 0x50f, -1);
	return 0;
}
