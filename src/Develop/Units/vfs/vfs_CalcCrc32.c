extern unsigned int vfs_Crc32Table[];
extern unsigned int vfs_Crc32Table[];

// Client twin of GOLD's fcn_00401000 (0x401000, 52 B): same crc32 over a
// 256-entry table, but the client's table sits at 0x6624a0 (GOLD's at
// 0x5eb380) and the loop shape that reproduces the client bytes is
// `while (n > 0)` with a walking pointer.

/* ADDRESS: GOLD 0x00401000 */
/* ADDRESS: GOLDTL 0x00401000 */
unsigned int __cdecl vfs_CalcCrc32(unsigned char* buf, unsigned int n)
{
	unsigned int crc;

	crc = 0xffffffffu;
	while (n > 0) {
		crc = vfs_Crc32Table[(crc & 0xff) ^ *buf] ^ (crc >> 8);
		buf++;
		n--;
	}
	return ~crc;
}
