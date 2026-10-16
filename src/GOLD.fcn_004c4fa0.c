void __cdecl fcn_004c4df0(int, int);
void __cdecl fcn_004c4330(char*);

/* ADDRESS: GOLD 0x004c4fa0 */
void __cdecl fcn_004c4fa0(int a)
{
	char buf[0x9c];

	buf[0] = 0x27;
	fcn_004c4df0(0x114, a);
	fcn_004c4330(buf);
}
