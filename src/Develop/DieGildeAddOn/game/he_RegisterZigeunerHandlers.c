


int __cdecl he_RegisterHandler(int, void*, void*);
void __cdecl he_StartAction0x9d(void);
void __cdecl he_RunAction0x9d(void);
void __cdecl he_InitEvent09e(void);
void __cdecl he_UpdateEvent09e(void);
void __cdecl he_ScheduleZigeunerActionExpiry(void);
void __cdecl he_RunAction0x9f(void);
void __cdecl he_InitEvent0a0(void);
void __cdecl he_UpdateEvent0a0(void);
void __cdecl he_InitEvent0a1(void);
void __cdecl he_UpdateEvent0a1(void);
void __cdecl he_InitEvent0a3(void);
void __cdecl he_UpdateEvent0a3(void);
void __cdecl he_InitEvent0a4(void);
void __cdecl he_UpdateEvent0a4(void);
int __cdecl he_RegisterActionMeta(int, char*, int, int, int);

int __cdecl he_RegisterZigeunerHandlers(void)
{
	if (he_RegisterHandler(0x9d, (void*) he_StartAction0x9d, (void*) he_RunAction0x9d) != 0 ||
	    he_RegisterHandler(0x9e, (void*) he_InitEvent09e, (void*) he_UpdateEvent09e) != 0 ||
	    he_RegisterHandler(0x9f, (void*) he_ScheduleZigeunerActionExpiry, (void*) he_RunAction0x9f) != 0 ||
	    he_RegisterHandler(0xa0, (void*) he_InitEvent0a0, (void*) he_UpdateEvent0a0) != 0 ||
	    he_RegisterHandler(0xa1, (void*) he_InitEvent0a1, (void*) he_UpdateEvent0a1) != 0 ||
	    he_RegisterHandler(0xa3, (void*) he_InitEvent0a3, (void*) he_UpdateEvent0a3) != 0 ||
	    he_RegisterHandler(0xa4, (void*) he_InitEvent0a4, (void*) he_UpdateEvent0a4) != 0) {
		return 1;
	}
	he_RegisterActionMeta(0xa1, 0, 0, 0x50f, -1);
	return 0;
}
