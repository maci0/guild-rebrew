int __cdecl vfs_ReadByte(void* stream, void* dst);

/* ADDRESS: GOLDTL 0x0044e0a0 */
/* ADDRESS: GOLDDE 0x00443db0 */
void __cdecl d3_ReadFlInfoFlags(void* stream, char* out)
{
	unsigned char b;

	vfs_ReadByte(stream, &b);
	out[0] = b & 1;
	out[1] = (b >> 1) & 1;
}
