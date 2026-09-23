// GLOBAL: GOLDTL 0x6624a0
extern unsigned int g_6624a0[];
// GLOBAL: GOLD 0x5eb380
extern unsigned int g_6624a0[];
// FUNCTION: GOLDTL 0x401000
// SIZE: 52
// FUNCTION: GOLD 0x00401000
// SIZE: 52
// Client twin of GOLD's fcn_00401000 (0x401000, 52 B): same crc32 over a
// 256-entry table, but the client's table sits at 0x6624a0 (GOLD's at
// 0x5eb380) and the loop shape that reproduces the client bytes is
// `while (n > 0)` with a walking pointer.

unsigned int __cdecl fcn_00401000(unsigned char* buf, unsigned int n)
{
	unsigned int crc;

	crc = 0xffffffffu;
	while (n > 0) {
		crc = g_6624a0[(crc & 0xff) ^ *buf] ^ (crc >> 8);
		buf++;
		n--;
	}
	return ~crc;
}
