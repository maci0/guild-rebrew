


int __cdecl he_RegisterHandler(int, void*, void*);
void __cdecl fcn_0057ba50(void);
void __cdecl fcn_0057baa0(void);

int __cdecl fcn_0057ba30(void)
{
	return he_RegisterHandler(0xa2, (void*) fcn_0057ba50, (void*) fcn_0057baa0) != 0;
}
