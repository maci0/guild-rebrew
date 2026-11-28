

void __cdecl evt_ImportCommand(int, int, int, int, int);

void __cdecl evt_RegisterSinusCommand(void)
{
	evt_ImportCommand(0x675bb4, 0x40c3b0, 7, 1, 7);
}
