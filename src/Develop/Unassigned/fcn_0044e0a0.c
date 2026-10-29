int __cdecl fcn_00401180(void* stream, void* dst);

/* ADDRESS: GOLDTL 0x0044e0a0 */
void __cdecl fcn_0044e0a0(void* stream, char* out)
{
	unsigned char b;

	fcn_00401180(stream, &b);
	out[0] = b & 1;
	out[1] = (b >> 1) & 1;
}
