

void __cdecl evt_RegisterVariable(char*, void*, int);

void __cdecl RegisterWorldStateVariables(void)
{
	evt_RegisterVariable((char*) 0x677e28, (void*) 0x6b6f58, 1);
	evt_RegisterVariable((char*) 0x677e18, (void*) 0x6b6f5c, 1);
	evt_RegisterVariable((char*) 0x677e08, (void*) 0x6b6f60, 1);
}
