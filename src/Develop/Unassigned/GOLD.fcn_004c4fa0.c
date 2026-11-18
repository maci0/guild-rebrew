void __cdecl fcn_004c4df0(int, void*);
int __cdecl fcn_004c4330(char*);

/* ADDRESS: GOLD 0x004c4fa0 */
int __cdecl fcn_004c4fa0(void* source)
{
	char buf[0x9c];

	buf[0] = 0x27;
	fcn_004c4df0(0x114, source);
	return fcn_004c4330(buf);
}
