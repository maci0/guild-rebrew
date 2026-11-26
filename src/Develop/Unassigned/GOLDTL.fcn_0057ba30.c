


int __cdecl he_RegisterHandler(int, void*, void*);
void __cdecl fcn_0057ba50(void);
void __cdecl he_RunSpecialOffices(void);

int __cdecl he_RegisterAction0xa2Handler(void)
{
	return he_RegisterHandler(0xa2, (void*) fcn_0057ba50, (void*) he_RunSpecialOffices) != 0;
}
