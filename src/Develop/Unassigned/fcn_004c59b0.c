int __cdecl fcn_004c4df0(unsigned short n, void* src);
int __cdecl fcn_004c4330(void*);

/* ADDRESS: GOLDTL 0x004c59b0 */
void __cdecl fcn_004c59b0(void* source)
{
	char buf[0x9c];

	buf[0] = 0x28;
	fcn_004c4df0(0x114, source);
	fcn_004c4330(buf);
}
