


int __cdecl he_RegisterHandler(int, void*, void*);
void __cdecl he_InitSpecialOffices(void);
void __cdecl he_RunSpecialOffices(void);

/* ADDRESS: GOLDDE 0x00561890 */
int __cdecl he_RegisterAction0xa2Handler(void)
{
	return he_RegisterHandler(0xa2, (void*) he_InitSpecialOffices, (void*) he_RunSpecialOffices) != 0;
}
