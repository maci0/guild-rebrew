int __cdecl vfs_ReadByte(void* stream, void* dst);

/* ADDRESS: GOLDTL 0x0044e0a0 */
void __cdecl fcn_0044e0a0(void* stream, char* out)
{
	unsigned char b;

	vfs_ReadByte(stream, &b);
	out[0] = b & 1;
	out[1] = (b >> 1) & 1;
}
